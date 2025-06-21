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
#include "string"

#include "frameworks/base/perfmonitor/perf_monitor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
constexpr int32_t SUB_HEALTH_DURATION = 1;
} // namespace

class PerfMonitorTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: PerfMonitorTest001
 * @tc.desc: SetSubHealthInfo
 * @tc.type: FUNC
 */
HWTEST_F(PerfMonitorTest, PerfMonitorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get currentId from initial env
     * @tc.expected: CurrentId equals the value in initial env
     */
    std::string info = "testSubHealthInfo";
    std::string reson = "testSubHealthReason";
    int32_t duration = SUB_HEALTH_DURATION;
    EXPECT_NE(PerfMonitor::GetPerfMonitor(), nullptr);
    PerfMonitor::GetPerfMonitor()->SetSubHealthInfo(info, reson, duration);
}

} // namespace OHOS::Ace
