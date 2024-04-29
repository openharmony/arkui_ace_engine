/*
 * Copyright (c) 2024 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/base/view_abstract_model_ng.h"

#include "base/memory/referenced.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/common/ace_engine.h"

#undef private
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    ViewAbstractModelNG viewAbstractModelNG;
    RefPtr<MockTaskExecutor> MOCK_TASK_EXECUTOR;
}; // namespace

class ViewAbstractModelTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestCase();
};

void ViewAbstractModelTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}
void ViewAbstractModelTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ViewAbstractModelTestNg001
 * @tc.desc: Test the GetSheetContext of View_Abstract_model_ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build sheetStyle instanceId is empty.
     */
    SheetStyle style;
    auto testContext1 = viewAbstractModelNG.GetSheetContext(style);
    EXPECT_NE(testContext1, nullptr);

    /**
     * @tc.steps: step2. Build sheetStyle instanceId is 100001.
     */
    style.instanceId = 100001;
    /**
     * @tc.steps: step3. Build an AceEngine.
     */
    AceEngine& aceEngine = AceEngine::Get();

    /**
     * @tc.steps: step4. Add Container.
     * @tc.expected: Add Container success.
     */
    aceEngine.AddContainer(style.instanceId.value(), MockContainer::container_);
    EXPECT_NE(aceEngine.GetContainer(style.instanceId.value()), nullptr);
    /**
     * @tc.expected: context is not nullptr.
     */
    auto testContext2 = viewAbstractModelNG.GetSheetContext(style);
    EXPECT_NE(testContext2, nullptr);
}
} // namespace OHOS::Ace::NG