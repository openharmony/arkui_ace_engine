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

#include <optional>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/base/mock_event_report.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/manager/drag_drop/drag_drop_behavior_reporter/drag_drop_behavior_reporter.h"

#include "base/log/event_report.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct DragReportData {
    CrossingEnd isCrossing = CrossingEnd::NOT_CROSSING;
    DragStartResult startResult = DragStartResult::UNKNOW;
    DragStopResult stopResult = DragStopResult::UNKNOW;
    int32_t summaryNum = -1;
    DragReporterPharse dragBehavior;
    std::string summaryType = "";
    std::set<std::string> allowDropType = {""};
    DragReportData(CrossingEnd isCrossing, DragStartResult startResult, DragStopResult stopResult, int32_t summaryNum,
        DragReporterPharse dragBehavior)
        : isCrossing(isCrossing), startResult(startResult), stopResult(stopResult), summaryNum(summaryNum),
          dragBehavior(dragBehavior) {}
};

const std::vector<DragStartResult> dragStartResult = {
    DragStartResult::DRAG_START_SUCCESS,
    DragStartResult::APP_REFUSE_DRAG,
    DragStartResult::DRAG_START_SUCCESS,
    DragStartResult::APP_REFUSE_DRAG,
    DragStartResult::DRAGFWK_START_FAIL,
    DragStartResult::SET_DATA_FAIL,
    DragStartResult::REPEAT_DRAG_FAIL,
    DragStartResult::SNAPSHOT_FAIL,
    DragStartResult::TEXT_NOT_SELECT,
};

const std::vector<DragStopResult> dragStopResult = {
    DragStopResult::DRAG_SOTP_SUCCESS,
    DragStopResult::APP_REFUSE_DATA,
    DragStopResult::APP_RECEIVE_FAIL,
    DragStopResult::APP_DATA_UNSUPPORT,
    DragStopResult::USER_STOP_DRAG,
    DragStopResult::GET_UDKEY_FAIL,
    DragStopResult::GET_UDMF_FAIL,
    DragStopResult::DRAGFWK_STOP_FAIL,
};

const std::vector<CrossingEnd> crossingEnd = {
    CrossingEnd::NOT_CROSSING,
    CrossingEnd::IS_CROSSING,
};

class DragReporterTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void SetDragStartReportData(const DragReportData& dragReportData);
};

void DragReporterTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragReporterTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DragReporterTestNg::SetDragStartReportData(const DragReportData& dragReportData)
{
    DragDropBehaviorReporter::GetInstance().UpdateDragStartResult(dragReportData.startResult);
    DragDropBehaviorReporter::GetInstance().UpdateDragStopResult(dragReportData.stopResult);
    DragDropBehaviorReporter::GetInstance().UpdateRecordSize(dragReportData.summaryNum);
    DragDropBehaviorReporter::GetInstance().UpdateSummaryType(dragReportData.summaryType);
    DragDropBehaviorReporter::GetInstance().UpdateIsCrossing(dragReportData.isCrossing);
    DragDropBehaviorReporter::GetInstance().UpdateAllowDropType(dragReportData.allowDropType);
}

/**
 * @tc.name: DragReporterTest001
 * @tc.desc: Test drag report
 * @tc.type: FUNC
 * @tc.author: catpoison
 */
HWTEST_F(DragReporterTestNg, DragReporterTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test drag start report.
     */
    for (const auto& isCrossing : crossingEnd) {
        for (const auto& startResult : dragStartResult) {
            for (const auto& stopResult : dragStopResult) {
                DragReportData dragReportCase = DragReportData(isCrossing,
                    startResult, stopResult, 1, DragReporterPharse::DRAG_START);
                MockContainer::SetUp();
                auto container = MockContainer::Current();
                container->pipelineContext_ = NG::MockPipelineContext::GetCurrent();
                auto containerId = MockContainer::CurrentId();
                DragReporterTestNg::SetDragStartReportData(dragReportCase);
                auto mockTaskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
                MockPipelineContext::GetCurrentContext()->taskExecutor_ = mockTaskExecutor;
                DragDropBehaviorReporter::GetInstance().Submit(dragReportCase.dragBehavior, containerId);
                DragInfo dragReportInfo = MockEventReport::dragInfo_;
                EXPECT_EQ(dragReportInfo.result, static_cast<int32_t>(dragReportCase.startResult));
                EXPECT_EQ(dragReportInfo.summaryNum, static_cast<int32_t>(dragReportCase.summaryNum));
                EXPECT_EQ(dragReportInfo.summaryType, dragReportCase.summaryType);
                EXPECT_EQ(dragReportInfo.isCrossing, static_cast<int32_t>(dragReportCase.isCrossing));
                MockContainer::TearDown();
            }
        }
    }

    /**
     * @tc.steps: step1. test drag stop report.
     */
    for (const auto& isCrossing : crossingEnd) {
        for (const auto& startResult : dragStartResult) {
            for (const auto& stopResult : dragStopResult) {
                DragReportData dragReportCase = DragReportData(isCrossing,
                    startResult, stopResult, 1, DragReporterPharse::DRAG_STOP);
                MockContainer::SetUp();
                auto container = MockContainer::Current();
                container->pipelineContext_ = NG::MockPipelineContext::GetCurrent();
                auto containerId = MockContainer::CurrentId();
                DragReporterTestNg::SetDragStartReportData(dragReportCase);
                auto mockTaskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
                MockPipelineContext::GetCurrentContext()->taskExecutor_ = mockTaskExecutor;
                DragDropBehaviorReporter::GetInstance().Submit(dragReportCase.dragBehavior, containerId);
                DragInfo dragReportInfo = MockEventReport::dragInfo_;
                EXPECT_EQ(dragReportInfo.result, static_cast<int32_t>(dragReportCase.stopResult));
                EXPECT_EQ(dragReportInfo.summaryNum, static_cast<int32_t>(dragReportCase.summaryNum));
                EXPECT_EQ(dragReportInfo.summaryType, dragReportCase.summaryType);
                EXPECT_EQ(dragReportInfo.isCrossing, static_cast<int32_t>(dragReportCase.isCrossing));
                MockContainer::TearDown();
            }
        }
    }
}
} // namespace OHOS::Ace::NG
