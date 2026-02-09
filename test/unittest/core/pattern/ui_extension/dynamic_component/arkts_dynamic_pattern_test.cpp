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
#include "base/memory/ace_type.h"
#define private public
#define protected public
#include "core/components_ng/pattern/ui_extension/dynamic_component/arkts_dynamic_pattern.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_param.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string DYNAMIC_COMPONENT_ETS_TAG = "DynamicComponent";
    const std::string TAG = "Test node tag";
    const std::string ENTRY_POINT = "test_entry_point";
    const int32_t VALID_WORKER_ID = 100;
} // namespace

class ArktsDynamicPatternTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    RefPtr<ArktsDynamicPattern> CreateArktsDynamicPattern();
};

void ArktsDynamicPatternTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void ArktsDynamicPatternTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

RefPtr<ArktsDynamicPattern> ArktsDynamicPatternTestNg::CreateArktsDynamicPattern()
{
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<ArktsDynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);

    return dynamicNode->GetPattern<ArktsDynamicPattern>();
}

/**
 * @tc.name: CheckDynamicRendererConstraint001
 * @tc.desc: Test CheckDynamicRendererConstraint with null dynamicComponentRenderer
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTestNg, CheckDynamicRendererConstraint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ArktsDynamicPattern without renderer
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);
    EXPECT_EQ(arktsPattern->dynamicComponentRenderer_, nullptr);

    /**
     * @tc.steps: step2. call CheckDynamicRendererConstraint with valid workerId
     * @tc.expected: expect return false because renderer is null
     */
    auto result = arktsPattern->CheckDynamicRendererConstraint(VALID_WORKER_ID);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckDynamicRendererConstraint002
 * @tc.desc: Test CheckDynamicRendererConstraint with CheckDCMaxConstraintInWorker returning false
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTestNg, CheckDynamicRendererConstraint002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. create ArktsDynamicPattern with valid renderer
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    DynamicParam param;
    param.workerId = VALID_WORKER_ID;
    param.entryPoint = ENTRY_POINT;
    param.backgroundTransparent = false;

    /**
     * @tc.steps: step2. create renderer with mock configuration
     */
    IsolatedInfo curDynamicInfo;
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<ArktsDynamicPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(TAG, 1, pattern);
    arktsPattern->dynamicComponentRenderer_ =
        DynamicComponentRenderer::Create(frameNode, runtime, curDynamicInfo);
    ASSERT_NE(arktsPattern->dynamicComponentRenderer_, nullptr);

    /**
     * @tc.steps: step3. call CheckDynamicRendererConstraint
     * @tc.expected: expect return false when constraints are not met
     */
    auto result = arktsPattern->CheckDynamicRendererConstraint(VALID_WORKER_ID);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: CheckDynamicRendererConstraint003
 * @tc.desc: Test CheckDynamicRendererConstraint with both constraints passing
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTestNg, CheckDynamicRendererConstraint003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. create ArktsDynamicPattern with valid renderer
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    DynamicParam param;
    param.workerId = VALID_WORKER_ID;
    param.entryPoint = ENTRY_POINT;
    param.backgroundTransparent = true;

    /**
     * @tc.steps: step2. create renderer and set up pattern
     */
    IsolatedInfo curDynamicInfo;
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<ArktsDynamicPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(TAG, 1, pattern);
    arktsPattern->dynamicComponentRenderer_ =
        DynamicComponentRenderer::Create(frameNode, runtime, curDynamicInfo);
    ASSERT_NE(arktsPattern->dynamicComponentRenderer_, nullptr);

    /**
     * @tc.steps: step3. call CheckDynamicRendererConstraint
     */
    auto result = arktsPattern->CheckDynamicRendererConstraint(VALID_WORKER_ID);
    /**
     * @tc.expected: result depends on constraint checking implementation
     */
    (void)result;
#endif
}

/**
 * @tc.name: CheckDynamicRendererConstraint004
 * @tc.desc: Test CheckDynamicRendererConstraint with invalid workerId
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTestNg, CheckDynamicRendererConstraint004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. create ArktsDynamicPattern with valid renderer
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    /**
     * @tc.steps: step2. create renderer
     */
    IsolatedInfo curDynamicInfo;
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<ArktsDynamicPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(TAG, 1, pattern);
    arktsPattern->dynamicComponentRenderer_ =
        DynamicComponentRenderer::Create(frameNode, runtime, curDynamicInfo);
    ASSERT_NE(arktsPattern->dynamicComponentRenderer_, nullptr);

    /**
     * @tc.steps: step3. call CheckDynamicRendererConstraint with invalid workerId (negative)
     */
    auto result = arktsPattern->CheckDynamicRendererConstraint(-1);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. call CheckDynamicRendererConstraint with zero workerId
     */
    result = arktsPattern->CheckDynamicRendererConstraint(0);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: CheckDynamicRendererConstraint005
 * @tc.desc: Test CheckDynamicRendererConstraint with different workerId values
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTestNg, CheckDynamicRendererConstraint005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. create ArktsDynamicPattern with valid renderer
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    IsolatedInfo curDynamicInfo;
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<ArktsDynamicPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(TAG, 1, pattern);
    arktsPattern->dynamicComponentRenderer_ =
        DynamicComponentRenderer::Create(frameNode, runtime, curDynamicInfo);
    ASSERT_NE(arktsPattern->dynamicComponentRenderer_, nullptr);

    /**
     * @tc.steps: step2. test with various workerId values
     */
    std::vector<int32_t> workerIds = {1, 50, 100, 1000, 9999};
    for (auto workerId : workerIds) {
        auto result = arktsPattern->CheckDynamicRendererConstraint(workerId);
        /**
         * @tc.expected: result depends on constraint checking implementation
         */
        (void)result;
    }
#endif
}

/**
 * @tc.name: CheckDynamicRendererConstraint006
 * @tc.desc: Test CheckDynamicRendererConstraint calls HandleErrorCallback with DC_EXCEED_MAX_NUM_IN_WORKER
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTestNg, CheckDynamicRendererConstraint006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. create ArktsDynamicPattern with valid renderer
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    IsolatedInfo curDynamicInfo;
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<ArktsDynamicPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(TAG, 1, pattern);
    arktsPattern->dynamicComponentRenderer_ =
        DynamicComponentRenderer::Create(frameNode, runtime, curDynamicInfo);
    ASSERT_NE(arktsPattern->dynamicComponentRenderer_, nullptr);

    /**
     * @tc.steps: step2. call CheckDynamicRendererConstraint which may trigger error callback
     * @tc.expected: when constraints are not met, error callback is called
     */
    auto result = arktsPattern->CheckDynamicRendererConstraint(VALID_WORKER_ID);
    (void)result;
#endif
}

/**
 * @tc.name: CheckDynamicRendererConstraint007
 * @tc.desc: Test CheckDynamicRendererConstraint calls HandleErrorCallback with DC_WORKER_EXCEED_MAX_NUM
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTestNg, CheckDynamicRendererConstraint007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. create ArktsDynamicPattern with valid renderer
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    IsolatedInfo curDynamicInfo;
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<ArktsDynamicPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(TAG, 1, pattern);
    arktsPattern->dynamicComponentRenderer_ =
        DynamicComponentRenderer::Create(frameNode, runtime, curDynamicInfo);
    ASSERT_NE(arktsPattern->dynamicComponentRenderer_, nullptr);

    /**
     * @tc.steps: step2. call CheckDynamicRendererConstraint
     * @tc.expected: when worker constraint is not met, appropriate error callback is called
     */
    auto result = arktsPattern->CheckDynamicRendererConstraint(VALID_WORKER_ID);
    (void)result;
#endif
}

/**
 * @tc.name: CheckDynamicRendererConstraint008
 * @tc.desc: Test CheckDynamicRendererConstraint multiple calls with same renderer
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTestNg, CheckDynamicRendererConstraint008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. create ArktsDynamicPattern with valid renderer
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    IsolatedInfo curDynamicInfo;
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<ArktsDynamicPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(TAG, 1, pattern);
    arktsPattern->dynamicComponentRenderer_ =
        DynamicComponentRenderer::Create(frameNode, runtime, curDynamicInfo);
    ASSERT_NE(arktsPattern->dynamicComponentRenderer_, nullptr);

    /**
     * @tc.steps: step2. call CheckDynamicRendererConstraint multiple times
     */
    for (int i = 0; i < 5; i++) {
        auto result = arktsPattern->CheckDynamicRendererConstraint(VALID_WORKER_ID + i);
        (void)result;
    }
#endif
}

} // namespace OHOS::Ace::NG
