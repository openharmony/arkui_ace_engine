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
#include "test/unittest/core/pipeline/pipeline_context_test_ng.h"
#include "base/ressched/ressched_report.h"
#include "core/components_ng/event/event_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace NG {
/**
 * @tc.name: PipelineContextTestNgTouchMonitor
 * @tc.desc: Test OnDumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNgTouchMonitor, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    std::vector<std::string> params;
    params.push_back("-touchmonitor");
    params.push_back("-b");
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
    auto ret = context_->OnDumpInfo(params);
    EXPECT_TRUE(ret);
    context_->eventManager_ = nullptr;
    ret = context_->OnDumpInfo(params);
    EXPECT_TRUE(ret);
}
/**
 * @tc.name: PipelineContextTestNg501
 * @tc.desc: Test ResSchedReportAxisEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg501, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    AxisEvent event;
    event.action = AxisAction::UPDATE;
    event.sourceTool = SourceTool::TOUCHPAD;
    event.horizontalAxis = 100;
    event.verticalAxis = 200;
    context_->ResSchedReportAxisEvent(event);
    EXPECT_EQ(ResSchedReport::GetInstance().curAxisEvent_.offset.GetX(), -event.horizontalAxis);
    EXPECT_EQ(ResSchedReport::GetInstance().curAxisEvent_.offset.GetY(), -event.verticalAxis);

    event.verticalAxis = 0;
    context_->ResSchedReportAxisEvent(event);
    EXPECT_EQ(ResSchedReport::GetInstance().lastAxisEvent_.offset.GetY(), -200);

    event.horizontalAxis = 0;
    context_->ResSchedReportAxisEvent(event);
    EXPECT_NE(ResSchedReport::GetInstance().lastAxisEvent_.offset.GetX(), event.horizontalAxis);
}

/**
 * @tc.name: PipelineContextTestNg502
 * @tc.desc: Test Dump All UINode Info.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg502, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
    /**
     * @tc.steps2: init a vector with some string params and
                call OnDumpInfo with every param array.
     * @tc.expected: The return value is same as the expectation.
     */
    std::vector<std::vector<std::string>> params = {
        { "-element", "-all" },
        { "-default", "-all" }};
    int turn = 0;
    for (; turn < params.size(); turn++) {
        EXPECT_TRUE(context_->OnDumpInfo(params[turn]));
    }
}
} // namespace NG
} // namespace OHOS::Ace
