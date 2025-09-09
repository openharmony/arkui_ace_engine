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

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_advanced_register.h"
#include "core/components_ng/pattern/stage/force_split/parallel_page_pattern.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_pattern.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_manager.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ParallelBaseTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: ViewAdvancedRegisterTest001
 * @tc.desc: Testing object creating function of ViewAdvancedRegister.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelBaseTestNg, ViewAdvancedRegisterTest001, TestSize.Level1)
{
    DeviceType preDeviceType_ = SystemProperties::deviceType_;
    SystemProperties::deviceType_ = DeviceType::TABLET;
    /**
     * @tc.steps: step1. Create ViewAdvancedRegister instance.
     * @tc.expected: Success to create ViewAdvancedRegister instance.
     */
    auto viewAdvancedRegister = ViewAdvancedRegister::GetInstance();
    ASSERT_NE(viewAdvancedRegister, nullptr);

    /**
     * @tc.steps: step2. Create ParallelPagePattern.
     * @tc.expected: Success to create ParallelPagePattern.
     */
    auto info = AceType::MakeRefPtr<PageInfo>();
    ASSERT_NE(info, nullptr);
    auto pagePattern = AceType::DynamicCast<ParallelPagePattern>(viewAdvancedRegister->CreatePagePattern(info));
    ASSERT_NE(pagePattern, nullptr);

    /**
     * @tc.steps: step3. Create ParallelStagePattern.
     * @tc.expected: Success to create ParallelStagePattern.
     */
    auto stagePattern =
        AceType::DynamicCast<ParallelStagePattern>(viewAdvancedRegister->GeneratePattern(V2::STAGE_ETS_TAG));
    ASSERT_NE(stagePattern, nullptr);

    /**
     * @tc.steps: step4. Create ParallelStageManager.
     * @tc.expected: Success to create ParallelStageManager.
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 1, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    auto stageManager =
        AceType::DynamicCast<ParallelStageManager>(viewAdvancedRegister->GenerateStageManager(stageNode));
    ASSERT_NE(stageManager, nullptr);
    SystemProperties::deviceType_ = preDeviceType_;
}
} // namespace OHOS::Ace::NG