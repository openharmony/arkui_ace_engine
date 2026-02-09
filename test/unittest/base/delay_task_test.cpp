/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "base/utils/delay_task.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {}

class ArkUIDelayLogTaskTest : public testing::Test {};

/**
 * @tc.name: PostReductionTaskTest001
 * @tc.desc: Test PostReductionTask with immediate execution
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIDelayLogTaskTest, PostReductionTaskTest001, TestSize.Level1)
{
    TaskTimeRecord taskTimeRecord;
    taskTimeRecord.taskName = "taskTest";
    uint32_t delayTime = 0;
    auto logTask = []() {
        // Task logic
    };
    ArkUIDelayLogTask::PostReductionTask(logTask, taskTimeRecord, delayTime);
    EXPECT_TRUE(taskTimeRecord.lastTaskTime > 0);
}
} // namespace OHOS::Ace