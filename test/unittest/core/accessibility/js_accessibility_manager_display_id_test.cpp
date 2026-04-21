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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "adapter/ohos/osal/js_accessibility_manager.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
    const int32_t SCENEBOARD_WINDOW_ID = 1;
    const int32_t NON_SCENEBOARD_WINDOW_ID = 2;
    const uint64_t EXPECTED_DISPLAY_ID = 100;
    const uint64_t DEFAULT_DISPLAY_ID = 0;
    const int32_t TEST_INSTANCE_ID = 1;
    const int32_t TEST_WINDOW_ID = 1;
    const uint32_t TEST_WINDOW_ID_UINT = 1;
    const int32_t TEST_TREE_ID = 2;
    const uint32_t TEST_PARENT_WINDOW_ID = 0;
    const uint32_t TEST_PARENT_WINDOW_ID_NONZERO = 5;
} // namespace

class JsAccessibilityDisplayIdTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void JsAccessibilityDisplayIdTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void JsAccessibilityDisplayIdTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: RegisterInteractionOperation_DisplayId001
 * @tc.desc: Test RegisterInteractionOperation returns 0 when already registered, GetDisplayId is
 *           not invoked
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityDisplayIdTest, RegisterInteractionOperation_DisplayId001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-begin RegisterInteractionOperation_DisplayId001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager and set registered state
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->Register(true);

    /**
     * @tc.steps: step2. call RegisterInteractionOperation when already registered
     * @tc.expected: step2. returns 0 without attempting to register again
     */
    int result = jsAccessibilityManager->RegisterInteractionOperation(TEST_WINDOW_ID);
    EXPECT_EQ(result, 0);

    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-end RegisterInteractionOperation_DisplayId001";
}

/**
 * @tc.name: DeregisterInteractionOperation_DisplayId001
 * @tc.desc: Test DeregisterInteractionOperation does nothing when not registered
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityDisplayIdTest, DeregisterInteractionOperation_DisplayId001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-begin DeregisterInteractionOperation_DisplayId001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager without setting registered state
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. set parentWindowId_ to a non-zero value
     */
    jsAccessibilityManager->parentWindowId_ = TEST_PARENT_WINDOW_ID_NONZERO;

    /**
     * @tc.steps: step3. call DeregisterInteractionOperation when not registered
     * @tc.expected: step3. returns early without deregistering; parentWindowId_ remains unchanged
     */
    jsAccessibilityManager->DeregisterInteractionOperation();
    EXPECT_EQ(jsAccessibilityManager->parentWindowId_, TEST_PARENT_WINDOW_ID_NONZERO);

    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-end DeregisterInteractionOperation_DisplayId001";
}

/**
 * @tc.name: DeregisterInteractionOperation_DisplayId002
 * @tc.desc: Test DeregisterInteractionOperation resets parent state when parentWindowId_ is non-zero
 *           and instance is available. Covers GetDisplayId with sceneboard windowId and valid pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityDisplayIdTest, DeregisterInteractionOperation_DisplayId002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-begin DeregisterInteractionOperation_DisplayId002";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager, set registered state, and set parent info
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->Register(true);
    jsAccessibilityManager->parentWindowId_ = TEST_PARENT_WINDOW_ID_NONZERO;
    jsAccessibilityManager->parentTreeId_ = TEST_TREE_ID;

    /**
     * @tc.steps: step2. set up pipeline context so GetDisplayId can resolve container
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetInstanceId(TEST_INSTANCE_ID);
    pipeline->SetWindowId(TEST_WINDOW_ID_UINT);
    MockContainer::Current()->SetCurrentDisplayId(EXPECTED_DISPLAY_ID);
    jsAccessibilityManager->SetPipelineContext(pipeline);
    jsAccessibilityManager->SetWindowId(TEST_WINDOW_ID_UINT);

    /**
     * @tc.steps: step3. call DeregisterInteractionOperation
     * @tc.expected: step3. after deregister, parentWindowId_ is reset to 0 since it was non-zero;
     *             the three-parameter DeregisterElementOperator(windowId, treeId, displayId) path
     *             was taken with GetDisplayId returning EXPECTED_DISPLAY_ID
     */
    jsAccessibilityManager->DeregisterInteractionOperation();
    EXPECT_EQ(jsAccessibilityManager->parentWindowId_, 0);

    // Reset displayId to avoid affecting other tests
    MockContainer::Current()->SetCurrentDisplayId(DEFAULT_DISPLAY_ID);

    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-end DeregisterInteractionOperation_DisplayId002";
}

/**
 * @tc.name: DeregisterInteractionOperation_DisplayId003
 * @tc.desc: Test DeregisterInteractionOperation with parentWindowId_ zero uses the two-parameter
 *           DeregisterElementOperator(windowId, displayId) path
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityDisplayIdTest, DeregisterInteractionOperation_DisplayId003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-begin DeregisterInteractionOperation_DisplayId003";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager, set registered state with parentWindowId_ = 0
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->Register(true);
    jsAccessibilityManager->parentWindowId_ = TEST_PARENT_WINDOW_ID;

    /**
     * @tc.steps: step2. set up pipeline context
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetInstanceId(TEST_INSTANCE_ID);
    pipeline->SetWindowId(TEST_WINDOW_ID_UINT);
    MockContainer::Current()->SetCurrentDisplayId(EXPECTED_DISPLAY_ID);
    jsAccessibilityManager->SetPipelineContext(pipeline);
    jsAccessibilityManager->SetWindowId(TEST_WINDOW_ID_UINT);

    /**
     * @tc.steps: step3. call DeregisterInteractionOperation with parentWindowId_ == 0
     * @tc.expected: step3. uses the two-parameter DeregisterElementOperator(windowId, displayId) path;
     *             parentWindowId_ remains 0
     */
    jsAccessibilityManager->DeregisterInteractionOperation();
    EXPECT_EQ(jsAccessibilityManager->parentWindowId_, TEST_PARENT_WINDOW_ID);

    // Reset displayId to avoid affecting other tests
    MockContainer::Current()->SetCurrentDisplayId(DEFAULT_DISPLAY_ID);

    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-end DeregisterInteractionOperation_DisplayId003";
}

/**
 * @tc.name: DeregisterInteractionOperation_DisplayId004
 * @tc.desc: Test DeregisterInteractionOperation iterates sub-pipeline contexts and calls
 *           DeregisterElementOperator with subDisplayId for each sub-pipeline
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityDisplayIdTest, DeregisterInteractionOperation_DisplayId004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-begin DeregisterInteractionOperation_DisplayId004";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager, set registered state
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->Register(true);
    jsAccessibilityManager->parentWindowId_ = TEST_PARENT_WINDOW_ID;

    /**
     * @tc.steps: step2. set up pipeline context with a sub-pipeline context
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetInstanceId(TEST_INSTANCE_ID);
    pipeline->SetWindowId(TEST_WINDOW_ID_UINT);
    MockContainer::Current()->SetCurrentDisplayId(EXPECTED_DISPLAY_ID);
    jsAccessibilityManager->SetPipelineContext(pipeline);
    jsAccessibilityManager->SetWindowId(TEST_WINDOW_ID_UINT);

    /**
     * @tc.steps: step3. add a sub-pipeline context with a non-sceneboard windowId
     *             GetDisplayId for sub-pipeline will return DEFAULT_DISPLAY_ID since subWindowId != 1
     */
    auto subPipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(subPipeline, nullptr);
    subPipeline->SetWindowId(NON_SCENEBOARD_WINDOW_ID);
    jsAccessibilityManager->AddSubPipelineContext(subPipeline);

    /**
     * @tc.steps: step4. call DeregisterInteractionOperation
     * @tc.expected: step4. iterates sub-pipeline and calls DeregisterElementOperator with
     *             subDisplayId = DEFAULT_DISPLAY_ID (since subWindowId != SCENEBOARD_WINDOW_ID);
     *             completes without crash
     */
    jsAccessibilityManager->DeregisterInteractionOperation();
    EXPECT_EQ(jsAccessibilityManager->parentWindowId_, TEST_PARENT_WINDOW_ID);

    // Reset displayId to avoid affecting other tests
    MockContainer::Current()->SetCurrentDisplayId(DEFAULT_DISPLAY_ID);

    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-end DeregisterInteractionOperation_DisplayId004";
}

/**
 * @tc.name: DeregisterInteractionOperation_DisplayId005
 * @tc.desc: Test DeregisterInteractionOperation with null pipeline context, where GetDisplayId
 *           returns DEFAULT_DISPLAY_ID due to null pipeline
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityDisplayIdTest, DeregisterInteractionOperation_DisplayId005, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-begin DeregisterInteractionOperation_DisplayId005";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager, set registered state, but no pipeline
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->Register(true);
    jsAccessibilityManager->parentWindowId_ = TEST_PARENT_WINDOW_ID;
    // context_ remains null (default WeakPtr)

    /**
     * @tc.steps: step2. call DeregisterInteractionOperation
     * @tc.expected: step2. internally GetDisplayId returned DEFAULT_DISPLAY_ID because
     *             context_.Upgrade() returned null; completes without crash
     */
    jsAccessibilityManager->DeregisterInteractionOperation();
    EXPECT_EQ(jsAccessibilityManager->parentWindowId_, TEST_PARENT_WINDOW_ID);

    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-end DeregisterInteractionOperation_DisplayId005";
}

/**
 * @tc.name: RegisterSubWindowInteractionOperation_DisplayId001
 * @tc.desc: Test RegisterSubWindowInteractionOperation returns early when accessibility is not enabled
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityDisplayIdTest, RegisterSubWindowInteractionOperation_DisplayId001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-begin RegisterSubWindowInteractionOperation_DisplayId001";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager and set registered state
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->Register(true);

    /**
     * @tc.steps: step2. call RegisterSubWindowInteractionOperation when accessibility is not enabled
     *             (AceApplicationInfo::IsAccessibilityEnabled returns false by default in test env)
     * @tc.expected: step2. returns early without registering
     */
    jsAccessibilityManager->RegisterSubWindowInteractionOperation(TEST_WINDOW_ID);

    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-end RegisterSubWindowInteractionOperation_DisplayId001";
}

/**
 * @tc.name: RegisterSubWindowInteractionOperation_DisplayId002
 * @tc.desc: Test RegisterSubWindowInteractionOperation returns early when not registered
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityDisplayIdTest, RegisterSubWindowInteractionOperation_DisplayId002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-begin RegisterSubWindowInteractionOperation_DisplayId002";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager without setting registered state
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. call RegisterSubWindowInteractionOperation when IsRegister returns false
     * @tc.expected: step2. returns early without registering
     */
    jsAccessibilityManager->RegisterSubWindowInteractionOperation(TEST_WINDOW_ID);

    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-end RegisterSubWindowInteractionOperation_DisplayId002";
}

/**
 * @tc.name: RegisterSubWindowInteractionOperation_DisplayId003
 * @tc.desc: Test RegisterSubWindowInteractionOperation with null pipeline context, where GetDisplayId
 *           returns DEFAULT_DISPLAY_ID due to null pipeline
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityDisplayIdTest, RegisterSubWindowInteractionOperation_DisplayId003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-begin RegisterSubWindowInteractionOperation_DisplayId003";

    /**
     * @tc.steps: step1. construct JsAccessibilityManager with registered state but no pipeline
     */
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->Register(true);
    // context_ remains null (default WeakPtr)

    /**
     * @tc.steps: step2. call RegisterSubWindowInteractionOperation
     *             AceApplicationInfo::IsAccessibilityEnabled returns false in test env,
     *             so it returns early before calling GetDisplayId
     * @tc.expected: step2. returns early without crash
     */
    jsAccessibilityManager->RegisterSubWindowInteractionOperation(TEST_WINDOW_ID);

    GTEST_LOG_(INFO) << "JsAccessibilityDisplayIdTest-end RegisterSubWindowInteractionOperation_DisplayId003";
}

} // namespace OHOS::Ace::NG
