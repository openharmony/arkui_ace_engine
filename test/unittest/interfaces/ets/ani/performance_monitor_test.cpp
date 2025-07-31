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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "ani_test.h"
#include "frameworks/base/perfmonitor/perf_monitor.h"
#include "performanceMonitor.cpp"
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
    ani_enum_item startInputType(-2);
    ani_string note("APP_START_BEGIN");
    Begin(env, scene, startInputType, note);
    PerfMonitor* perf = PerfMonitor::GetPerfMonitor();
    ASSERT_NE(perf, nullptr);
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

/**
 * @tc.name: RecordInputEventTimeTest002
 * @tc.desc: Test RecordInputEventTime
 * @tc.type: FUNC
 */
HWTEST_F(PerformanceMonitorTest, RecordInputEventTimeTest002, TestSize.Level1)
{
    ani_env *env = new ani_env;
    ASSERT_NE(env, nullptr);
    ani_string scene("LAUNCHER_APP_LAUNCH_FROM_ICON");
    ani_enum_item startInputType(2);
    ani_string note("APP_START_BEGIN");
    ani_enum_item type(-1);
    ani_enum_item sourceType(0);
    ani_double time(60);
    Begin(env, scene, startInputType, note);
    ASSERT_NE(PerfMonitor::GetPerfMonitor(), nullptr);
    RecordInputEventTime(env, type, sourceType, time);
    ASSERT_EQ(PerfMonitor::GetPerfMonitor()->mInputTime[LAST_DOWN], 60);
    End(env, scene);
    ASSERT_EQ(PerfMonitor::GetPerfMonitor()->mRecords.count(scene), 0);
}

/**
 * @tc.name: RecordInputEventTimeTest003
 * @tc.desc: Test RecordInputEventTime
 * @tc.type: FUNC
 */
HWTEST_F(PerformanceMonitorTest, RecordInputEventTimeTest003, TestSize.Level1)
{
    ani_env *env = new ani_env;
    ASSERT_NE(env, nullptr);
    ani_string scene("LAUNCHER_APP_LAUNCH_FROM_ICON");
    ani_enum_item startInputType(2);
    ani_string note("APP_START_BEGIN");
    ani_enum_item type(-1);
    ani_enum_item sourceType(0);
    ani_double time(60);
    Begin(env, scene, startInputType, note);
    ASSERT_NE(PerfMonitor::GetPerfMonitor(), nullptr);
    RecordInputEventTime(env, type, sourceType, time);
    ASSERT_EQ(PerfMonitor::GetPerfMonitor()->mInputTime[LAST_DOWN], 60);
    End(env, scene);
    ASSERT_EQ(PerfMonitor::GetPerfMonitor()->mRecords.count(scene), 0);
}

/**
 * @tc.name: RecordInputEventTimeTest004
 * @tc.desc: Test RecordInputEventTime
 * @tc.type: FUNC
 */
HWTEST_F(PerformanceMonitorTest, RecordInputEventTimeTest004, TestSize.Level1)
{
    ani_env *env = new ani_env;
    ASSERT_NE(env, nullptr);
    ani_string scene("LAUNCHER_APP_LAUNCH_FROM_ICON");
    ani_enum_item startInputType(2);
    ani_string note("APP_START_BEGIN");
    ani_enum_item type(1);
    ani_enum_item sourceType(-1);
    ani_double time(60);
    Begin(env, scene, startInputType, note);
    ASSERT_NE(PerfMonitor::GetPerfMonitor(), nullptr);
    RecordInputEventTime(env, type, sourceType, time);
    ASSERT_EQ(PerfMonitor::GetPerfMonitor()->mInputTime[LAST_DOWN], 60);
    End(env, scene);
    ASSERT_EQ(PerfMonitor::GetPerfMonitor()->mRecords.count(scene), 0);
}

/**
 * @tc.name: RecordInputEventTimeTest005
 * @tc.desc: Test RecordInputEventTime
 * @tc.type: FUNC
 */
HWTEST_F(PerformanceMonitorTest, RecordInputEventTimeTest005, TestSize.Level1)
{
    ani_env *env = new ani_env;
    ASSERT_NE(env, nullptr);
    ani_string scene("LAUNCHER_APP_LAUNCH_FROM_ICON");
    ani_enum_item startInputType(2);
    ani_string note("APP_START_BEGIN");
    ani_enum_item type(1);
    ani_enum_item sourceType(1);
    ani_double time(-1);
    Begin(env, scene, startInputType, note);
    ASSERT_NE(PerfMonitor::GetPerfMonitor(), nullptr);
    RecordInputEventTime(env, type, sourceType, time);
    ASSERT_NE(PerfMonitor::GetPerfMonitor()->mInputTime[LAST_DOWN], 0);
    End(env, scene);
    ASSERT_EQ(PerfMonitor::GetPerfMonitor()->mRecords.count(scene), 0);
}

/**
 * @tc.name: ANI_ConstructorTest001
 * @tc.desc: Test ANI_Constructor
 * @tc.type: FUNC
 */
HWTEST_F(PerformanceMonitorTest, ANI_ConstructorTest001, TestSize.Level1)
{
    ani_vm vm;
    uint32_t result = 0;
    ani_status sta = ANI_Constructor(&vm, &result);
    ASSERT_EQ(result, ANI_VERSION_1);
    ASSERT_EQ(sta, ANI_OK);
}

/**
 * @tc.name: ANI_ConstructorTest002
 * @tc.desc: Test ANI_Constructor
 * @tc.type: FUNC
 */
HWTEST_F(PerformanceMonitorTest, ANI_ConstructorTest002, TestSize.Level0) {
    ani_vm vm;
    uint32_t result;
    EXPECT_EQ(vm.GetEnv(ANI_VERSION_1, nullptr), ANI_OK);

    ani_env env;
    ani_status sta = env.FindNamespace("@ohos.arkui.performanceMonitor.performanceMonitor", nullptr);
    EXPECT_EQ(sta, ANI_OK);

    ani_status status = ANI_Constructor(&vm, &result);
    EXPECT_EQ(status, ANI_OK);
    EXPECT_EQ(result, ANI_VERSION_1);
}

/**
 * @tc.name: ANI_ConstructorTest003
 * @tc.desc: Test ANI_Constructor
 * @tc.type: FUNC
 */
HWTEST_F(PerformanceMonitorTest, ANI_ConstructorTest003, TestSize.Level0) {
    ani_vm vm;
    uint32_t result;
    ani_status sta = vm.GetEnv(ANI_VERSION_1, nullptr);
    EXPECT_EQ(sta, ANI_OK);

    ani_status status = ANI_Constructor(&vm, &result);
    EXPECT_EQ(status, ANI_OK);
}

/**
 * @tc.name: ANI_ConstructorTest004
 * @tc.desc: Test ANI_Constructor
 * @tc.type: FUNC
 */
HWTEST_F(PerformanceMonitorTest, ANI_ConstructorTest004, TestSize.Level0) {
    ani_vm vm;
    uint32_t result;
    ani_status sta = vm.GetEnv(ANI_VERSION_1, nullptr);
    EXPECT_EQ(sta, ANI_OK);

    ani_env env;
    sta = env.FindNamespace("@ohos.arkui.performanceMonitor.performanceMonitor", nullptr);
    EXPECT_EQ(sta, ANI_OK);

    ani_status status = ANI_Constructor(&vm, &result);
    EXPECT_EQ(status, ANI_OK);
}

/**
 * @tc.name: ANI_ConstructorTest005
 * @tc.desc: Test ANI_Constructor
 * @tc.type: FUNC
 */
HWTEST_F(PerformanceMonitorTest, ANI_ConstructorTest005, TestSize.Level0) {
    ani_vm vm;
    uint32_t result;
    ani_status sta = vm.GetEnv(ANI_VERSION_1, nullptr);
    EXPECT_EQ(sta, ANI_OK);

    ani_env env;
    sta = env.FindNamespace("@ohos.arkui.performanceMonitor.performanceMonitor", nullptr);
    EXPECT_EQ(sta, ANI_OK);

    ani_namespace ns = 1;
    std::array methods = {
        ani_native_function {"begin", nullptr, reinterpret_cast<void *>(Begin)},
    };
    sta = env.Namespace_BindNativeFunctions(ns, methods.data(), methods.size());
    EXPECT_EQ(sta, ANI_OK);

    ani_status status = ANI_Constructor(&vm, &result);
    EXPECT_EQ(status, ANI_OK);
}
} // namespace OHOS::Ace
