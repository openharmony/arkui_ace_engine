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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "base/log/dump_log.h"
#include "frameworks/core/accessibility/utils/accessibility_manager_utils.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
} // namespace


class AccessibilityManagerUtilsTest  : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityManagerUtilsTest ::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityManagerUtilsTest ::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: AddBlockedEvent001
 * @tc.desc: Get Content of frameNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTest, AddBlockedEvent001, TestSize.Level1)
{
    AccessibilityEventBlockerInAction blockerInAction;
    int64_t testId = 1;
    AccessibilityEventType testEvent = AccessibilityEventType::CLICK;
    blockerInAction.AddBlockedEvent(testId, testEvent);
    EXPECT_EQ(blockerInAction.currentActionId_, testId);
    // add another id will fail
    blockerInAction.AddBlockedEvent(testId + 1, testEvent);
    EXPECT_EQ(blockerInAction.currentActionId_, testId);
}

/**
 * @tc.name: SetBlockedEvents001
 * @tc.desc: Get Content of frameNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerUtilsTest, SetBlockedEvents001, TestSize.Level1)
{
    AccessibilityEventBlockerInAction blockerInAction;
    int64_t testId = 1;
    std::vector<AccessibilityEventType> events = {
        AccessibilityEventType::CLICK,
        AccessibilityEventType::LONG_PRESS
    };
    blockerInAction.SetBlockedEvents(testId, events);
    EXPECT_EQ(blockerInAction.currentActionId_, testId);
    EXPECT_EQ(blockerInAction.blockedEvents_.size(), events.size());
    blockerInAction.SetBlockedEvents(testId + 1, events);
    // add another id will fail
    EXPECT_EQ(blockerInAction.currentActionId_, testId);
    EXPECT_EQ(blockerInAction.blockedEvents_.size(), events.size());
}
} // namespace OHOS::Ace::NG