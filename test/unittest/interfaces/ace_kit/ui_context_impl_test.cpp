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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#define private public
#include "interfaces/inner_api/ace_kit/src/view/ui_context_impl.h"
#undef private
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/interfaces/ipc_single/iremote_object.h"
#include "ui/base/ace_type.h"

#include "base/memory/ace_type.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/pipeline_ng/pipeline_context.h"

#include <thread>
#include <chrono>

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Kit;

namespace OHOS::Ace::Kit {

class UIContextImplTest : public testing::Test {
protected:
    void SetUp() override
    {
        NG::MockPipelineContext::SetUp();
        auto mockPipeline = NG::MockPipelineContext::GetCurrent();
        uiContext_ = AceType::MakeRefPtr<UIContextImpl>(mockPipeline->Get());
    }
    void TearDown() override
    {
        uiContext_ = nullptr;
        NG::MockPipelineContext::TearDown();
    }

protected:
    RefPtr<UIContextImpl> uiContext_;
};

/**
 * @tc.name: ApiVersionTest001
 * @tc.desc: Test GetApiTargetVersion with standard version
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, ApiVersionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a data table to traverse with a for loop
     * @tc.expected: step1. std::vector should be created
     */
    const std::vector<std::pair<int32_t, int32_t>> apiVersionCase = {
        {8, 8},
        {1005, 5},
        {0, 0},
        {-10, -10},
        {1000, 0},
        {1001, 1},
        {10, 10},
    };
    for (const auto& [target, retrieved] : apiVersionCase) {
        /**
         * @tc.steps: step2. Set API target version
         * @tc.expected: step2. API version should be retrieved
         */
        OHOS::Ace::AceApplicationInfo::GetInstance().SetApiTargetVersion(target);
        /**
         * @tc.steps: step3. Retrieve the API version from UIContextImpl
         */
        int32_t api = uiContext_->GetApiTargetVersion();
        /**
         * @tc.expected: step3. Should return the exact negative value without modification
         */
        EXPECT_EQ(api, retrieved);
    }
}

/**
 * @tc.name: VersionComparisonTest001
 * @tc.desc: Test version comparison at API limit (1000) for equality and next value
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, VersionComparisonTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set API target version to the boundary value 1000
     */
    OHOS::Ace::AceApplicationInfo::GetInstance().SetApiTargetVersion(1000);

    /**
     * @tc.steps: step2. Verify comparison with version 0
     * @tc.expected: step2. Should return true (1000 % 1000 = 0 >= 0)
     */
    EXPECT_TRUE(uiContext_->GreatOrEqualTargetAPIVersion(0));

    /**
     * @tc.steps: step3. Verify comparison with version 1
     * @tc.expected: step3. Should return false (0 < 1)
     */
    EXPECT_FALSE(uiContext_->GreatOrEqualTargetAPIVersion(1));
}

/**
 * @tc.name: VersionComparisonTest002
 * @tc.desc: Test version comparison when target version is higher than required
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, VersionComparisonTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set API target version to 15
     */
    OHOS::Ace::AceApplicationInfo::GetInstance().SetApiTargetVersion(15);

    /**
     * @tc.steps: step2. Verify comparison with version 10
     * @tc.expected: step2. Should return true (15 >= 10)
     */
    EXPECT_TRUE(uiContext_->GreatOrEqualTargetAPIVersion(10));
}

/**
 * @tc.name: VersionComparisonTest003
 * @tc.desc: Test version comparison when target version is lower than required
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, VersionComparisonTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set API target version to 8
     */
    OHOS::Ace::AceApplicationInfo::GetInstance().SetApiTargetVersion(8);

    /**
     * @tc.steps: step2. Verify comparison with version 10
     * @tc.expected: step2. Should return false (8 < 10)
     */
    EXPECT_FALSE(uiContext_->GreatOrEqualTargetAPIVersion(10));
}

/**
 * @tc.name: VersionComparisonTest004
 * @tc.desc: Test version comparison with modulo version calculation
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, VersionComparisonTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set API target version to 1008 (1000 + 8)
     */
    OHOS::Ace::AceApplicationInfo::GetInstance().SetApiTargetVersion(1008);

    /**
     * @tc.steps: step2. Verify comparison with version 8
     * @tc.expected: step2. Should return true (1008 % 1000 = 8 >= 8)
     */
    EXPECT_TRUE(uiContext_->GreatOrEqualTargetAPIVersion(8));

    /**
     * @tc.steps: step3. Verify comparison with version 9
     * @tc.expected: step3. Should return false (8 < 9)
     */
    EXPECT_FALSE(uiContext_->GreatOrEqualTargetAPIVersion(9));
}

/**
 * @tc.name: VersionComparisonTest005
 * @tc.desc: Test version comparison with boundary values
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, VersionComparisonTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set API target version to 5
     */
    OHOS::Ace::AceApplicationInfo::GetInstance().SetApiTargetVersion(5);

    /**
     * @tc.steps: step2. Verify comparison with same version 5
     * @tc.expected: step2. Should return true (5 >= 5)
     */
    EXPECT_TRUE(uiContext_->GreatOrEqualTargetAPIVersion(5));

    /**
     * @tc.steps: step3. Verify comparison with lower version 4
     * @tc.expected: step3. Should return true (5 >= 4)
     */
    EXPECT_TRUE(uiContext_->GreatOrEqualTargetAPIVersion(4));

    /**
     * @tc.steps: step4. Verify comparison with higher version 6
     * @tc.expected: step4. Should return false (5 < 6)
     */
    EXPECT_FALSE(uiContext_->GreatOrEqualTargetAPIVersion(6));
}

/**
 * @tc.name: VersionComparisonTest006
 * @tc.desc: Test version comparison with large version difference
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, VersionComparisonTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set API target version to 2000
     */
    OHOS::Ace::AceApplicationInfo::GetInstance().SetApiTargetVersion(2000);

    /**
     * @tc.steps: step2. Verify comparison with version 0
     * @tc.expected: step2. Should return true (2000 % 1000 = 0 >= 0)
     */
    EXPECT_TRUE(uiContext_->GreatOrEqualTargetAPIVersion(0));

    /**
     * @tc.steps: step3. Verify comparison with version 1
     * @tc.expected: step3. Should return false (0 < 1)
     */
    EXPECT_FALSE(uiContext_->GreatOrEqualTargetAPIVersion(1));
}
/**
 * @tc.name: VersionComparisonTest007
 * @tc.desc: Test GreatOrEqualTargetAPIVersion with null context
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, VersionComparisonTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create UIContextImpl with null pipeline context
     */
    UIContextImpl nullContext(nullptr);

    /**
     * @tc.steps: step2. Set API target version to 8
     */
    OHOS::Ace::AceApplicationInfo::GetInstance().SetApiTargetVersion(8);

    /**
     * @tc.steps: step3. Check version comparisons
     * @tc.expected: step3. Should handle null context gracefully
     */
    bool ge8 = nullContext.GreatOrEqualTargetAPIVersion(8);
    bool ge9 = nullContext.GreatOrEqualTargetAPIVersion(9);
    EXPECT_TRUE(ge8);
    EXPECT_FALSE(ge9);
}

/**
 * @tc.name: RequestFrameTest001
 * @tc.desc: Test RequestFrame with valid context
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, RequestFrameTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call RequestFrame on valid context
     * @tc.expected: step1. Should complete without errors
     */
    uiContext_->RequestFrame();
    SUCCEED();
}

/**
 * @tc.name: RequestFrameTest002
 * @tc.desc: Test RequestFrame with null context
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, RequestFrameTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create UIContextImpl with null pipeline context
     */
    UIContextImpl uiContext_null(nullptr);

    /**
     * @tc.steps: step2. Call RequestFrame on null context
     * @tc.expected: step2. Should complete without crashing
     */
    uiContext_null.RequestFrame();

    SUCCEED();
}

/**
 * @tc.name: RunScopeUIDelayedTask001
 * @tc.desc: Test adding a delayed task to the UI task list
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, RunScopeUIDelayedTask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize a flag to track task execution status and set param varibles for call
     */
    const std::string taskName = "taskName";
    uint32_t delayTime = 1U;

    /**
     * @tc.steps: step2. Add a delayed task to the UI task list (name="taskName", delayTime=1500ms)
     */
    uiContext_->RunScopeUIDelayedTask([&]() {}, taskName, delayTime);
    
    /**
     * @tc.expected: step2. Task should be added without errors or crashes
     */
    std::this_thread::sleep_for(std::chrono::seconds(1));
    SUCCEED();
}

/**
 * @tc.name: RunScopeUIDelayedTask002
 * @tc.desc: Test excute a delayed UI task
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, RunScopeUIDelayedTask002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize a flag to track task execution status and set param varibles for call
     */
    const std::string taskName = "taskName";

    /**
     * @tc.steps: step2. Add a delayed task to the UI task list (name="taskName", delayTime=1500ms)
     *              Then check immediately flag should be not modified.
     */
    uiContext_->RunScopeUIDelayedTask([&]() { }, taskName, 1U);

    /**
     * @tc.expected: step3. Wait for moment until task executed then check the flag, should be modified at final.
     */
    std::this_thread::sleep_for(std::chrono::seconds(1));
    SUCCEED();
}

/**
 * @tc.name: AddAfterLayoutTaskTest001
 * @tc.desc: Test adding a layout task to the implicit animation task list
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, AddAfterLayoutTaskTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize a flag to track task execution status
     */
    bool taskExecuted = false;

    /**
     * @tc.steps: step2. Add a task to the implicit animation task list (isFlushInImplicitAnimationTask=true)
     */
    uiContext_->AddAfterLayoutTask([&]() { taskExecuted = true; }, true);

    /**
     * @tc.expected: step2. Task should be added without errors or crashes
     */
    SUCCEED();
}

/**
 * @tc.name: AddAfterLayoutTaskTest002
 * @tc.desc: Test adding a layout task to the normal task list
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, AddAfterLayoutTaskTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize a flag to track task execution status
     */
    bool taskExecuted = false;

    /**
     * @tc.steps: step2. Add a task to the normal task list (isFlushInImplicitAnimationTask=false)
     */
    uiContext_->AddAfterLayoutTask([&]() { taskExecuted = true; }, false);

    /**
     * @tc.expected: step2. Task should be added without errors or crashes
     */
    SUCCEED();
}

/**
 * @tc.name: RegisterArkUIObjectLifecycleCallback001
 * @tc.desc: Test register arkui object lifecycle callback to the normal task list
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, RegisterArkUIObjectLifecycleCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize a flag to track task execution status
     */
    bool taskExecuted = false;

    /**
     * @tc.steps: step2. Add a task to the normal task list
     */
    uiContext_->RegisterArkUIObjectLifecycleCallback([&taskExecuted](void*) { taskExecuted = true; });
    ASSERT_NE(uiContext_->context_, nullptr);
    uiContext_->context_->FireArkUIObjectLifecycleCallback(nullptr);

    /**
     * @tc.expected: step3. Task should be added without errors or crashes
     */
    EXPECT_TRUE(taskExecuted);
}

/**
 * @tc.name: UnregisterArkUIObjectLifecycleCallback001
 * @tc.desc: Test unregister arkui object lifecycle callback to the normal task list
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, UnregisterArkUIObjectLifecycleCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize a flag to track task execution status
     */
    bool taskExecuted = false;

    /**
     * @tc.steps: step2. Add a task to the normal task list
     */
    uiContext_->RegisterArkUIObjectLifecycleCallback([&taskExecuted](void*) { taskExecuted = true; });
    uiContext_->UnregisterArkUIObjectLifecycleCallback();
    ASSERT_NE(uiContext_->context_, nullptr);
    uiContext_->context_->FireArkUIObjectLifecycleCallback(nullptr);

    /**
     * @tc.expected: step3. Task should be added without errors or crashes
     */
    EXPECT_FALSE(taskExecuted);
}

/**
 * @tc.name: GetTokenTest
 * @tc.desc: Test get token to the normal task list
 * @tc.type: FUNC
 */
HWTEST_F(UIContextImplTest, GetTokenTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get token from uiContext
     */
    auto token = uiContext_->GetToken();

    ASSERT_EQ(token, nullptr);
    /**
     * @tc.expected: step2. Task should be added without errors or crashes
     */
    SUCCEED();
}

} // namespace OHOS::Ace::Kit
