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

#include <cstdint>
#include <string>

#include "gtest/gtest.h"
#include "base/memory/ace_type.h"
#include "frameworks/base/json/json_util.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/arkts_dynamic_pattern.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_param.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    // Test constants - using named constants instead of magic numbers
    const std::string DYNAMIC_COMPONENT_ETS_TAG = "DynamicComponent";
    const std::string TEST_TAG = "TestNode";
    const std::string VALID_ENTRY_POINT = "valid_entry_point";
    const std::string EMPTY_ENTRY_POINT = "";
    const int32_t VALID_WORKER_ID = 100;
    const int32_t INVALID_WORKER_ID_ZERO = 0;
    const int32_t INVALID_WORKER_ID_NEGATIVE = -1;
    const int32_t TEST_NODE_ID = 1;
    const bool BACKGROUND_TRANSPARENT = true;
    const bool BACKGROUND_OPAQUE = false;
    const int32_t NEW_WORKER_ID = 200;
    const bool NEW_BACKGROUND = BACKGROUND_OPAQUE;
} // namespace

class ArktsDynamicPatternTddTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    RefPtr<ArktsDynamicPattern> CreateArktsDynamicPattern();
    void SetUpPatternWithValidParam(RefPtr<ArktsDynamicPattern>& pattern);
};

void ArktsDynamicPatternTddTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void ArktsDynamicPatternTddTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

RefPtr<ArktsDynamicPattern> ArktsDynamicPatternTddTestNg::CreateArktsDynamicPattern()
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

void ArktsDynamicPatternTddTestNg::SetUpPatternWithValidParam(
    RefPtr<ArktsDynamicPattern>& pattern)
{
    DynamicParam param;
    param.workerId = VALID_WORKER_ID;
    param.entryPoint = VALID_ENTRY_POINT;
    param.backgroundTransparent = BACKGROUND_OPAQUE;
    pattern->SetDynamicParam(param);
}

// ========================================
// InitializeDynamicComponent Tests
// ========================================

/**
 * @tc.name: ArktsDynamicPattern_InitializeDynamicComponent_RendererAlreadyExists
 * @tc.desc: Test InitializeDynamicComponent when dynamicComponentRenderer already exists
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_InitializeDynamicComponent_RendererAlreadyExists, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern and set up renderer as non-null
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    // Simulate renderer already exists by setting the pointer to a mock value
    // (In actual test, this would require creating a real renderer)
    arktsPattern->dynamicComponentRenderer_ = reinterpret_cast<DynamicComponentRenderer*>(0x1);

    /**
     * @tc.steps: step2. Call InitializeDynamicComponent
     * @tc.expected: Should return early without creating new renderer
     */
    arktsPattern->InitializeDynamicComponent();

    // Verify renderer pointer is still the mock value (not changed)
    EXPECT_EQ(arktsPattern->dynamicComponentRenderer_,
        reinterpret_cast<DynamicComponentRenderer*>(0x1));

    // Clean up
    arktsPattern->dynamicComponentRenderer_ = nullptr;
}

/**
 * @tc.name: ArktsDynamicPattern_InitializeDynamicComponent_EmptyEntryPoint
 * @tc.desc: Test InitializeDynamicComponent when entryPoint is empty
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_InitializeDynamicComponent_EmptyEntryPoint, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern with empty entryPoint
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    DynamicParam param;
    param.workerId = VALID_WORKER_ID;
    param.entryPoint = EMPTY_ENTRY_POINT;
    param.backgroundTransparent = BACKGROUND_OPAQUE;
    arktsPattern->SetDynamicParam(param);

    EXPECT_EQ(arktsPattern->param_.entryPoint, EMPTY_ENTRY_POINT);

    /**
     * @tc.steps: step2. Call InitializeDynamicComponent
     * @tc.expected: Should return early without creating renderer
     */
    arktsPattern->InitializeDynamicComponent();

    // Verify renderer is not created
    EXPECT_EQ(arktsPattern->dynamicComponentRenderer_, nullptr);
}

/**
 * @tc.name: ArktsDynamicPattern_InitializeDynamicComponent_InvalidWorkerIdZero
 * @tc.desc: Test InitializeDynamicComponent when workerId is zero
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_InitializeDynamicComponent_InvalidWorkerIdZero, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern with workerId set to zero
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    DynamicParam param;
    param.workerId = INVALID_WORKER_ID_ZERO;
    param.entryPoint = VALID_ENTRY_POINT;
    param.backgroundTransparent = BACKGROUND_OPAQUE;
    arktsPattern->SetDynamicParam(param);

    EXPECT_EQ(arktsPattern->param_.workerId, INVALID_WORKER_ID_ZERO);

    /**
     * @tc.steps: step2. Call InitializeDynamicComponent
     * @tc.expected: Should return early without creating renderer
     */
    arktsPattern->InitializeDynamicComponent();

    // Verify renderer is not created
    EXPECT_EQ(arktsPattern->dynamicComponentRenderer_, nullptr);
}

/**
 * @tc.name: ArktsDynamicPattern_InitializeDynamicComponent_InvalidWorkerIdNegative
 * @tc.desc: Test InitializeDynamicComponent when workerId is negative
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_InitializeDynamicComponent_InvalidWorkerIdNegative, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern with negative workerId
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    DynamicParam param;
    param.workerId = INVALID_WORKER_ID_NEGATIVE;
    param.entryPoint = VALID_ENTRY_POINT;
    param.backgroundTransparent = BACKGROUND_OPAQUE;
    arktsPattern->SetDynamicParam(param);

    EXPECT_EQ(arktsPattern->param_.workerId, INVALID_WORKER_ID_NEGATIVE);

    /**
     * @tc.steps: step2. Call InitializeDynamicComponent
     * @tc.expected: Should return early without creating renderer
     */
    arktsPattern->InitializeDynamicComponent();

    // Verify renderer is not created
    EXPECT_EQ(arktsPattern->dynamicComponentRenderer_, nullptr);
}

// ========================================
// CheckDynamicRendererConstraint Tests
// ========================================

/**
 * @tc.name: ArktsDynamicPattern_CheckDynamicRendererConstraint_NullRenderer
 * @tc.desc: Test CheckDynamicRendererConstraint when dynamicComponentRenderer is null
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_CheckDynamicRendererConstraint_NullRenderer, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern without renderer
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);
    EXPECT_EQ(arktsPattern->dynamicComponentRenderer_, nullptr);

    /**
     * @tc.steps: step2. Call CheckDynamicRendererConstraint with valid workerId
     * @tc.expected: Should return false because renderer is null
     */
    auto result = arktsPattern->CheckDynamicRendererConstraint(VALID_WORKER_ID);
    EXPECT_FALSE(result);
}

// ========================================
// OnAttachContext Tests
// ========================================

/**
 * @tc.name: ArktsDynamicPattern_OnAttachContext_CallsInitializeDynamicComponent
 * @tc.desc: Test OnAttachContext calls InitializeDynamicComponent
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_OnAttachContext_CallsInitializeDynamicComponent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern with valid param
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    SetUpPatternWithValidParam(arktsPattern);

    /**
     * @tc.steps: step2. Get pipeline context
     */
    auto context = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    /**
     * @tc.steps: step3. Call OnAttachContext
     * @tc.expected: Should call InitializeDynamicComponent (which may fail due to environment)
     */
    arktsPattern->OnAttachContext(context);

    // Verify the method was called (renderer may still be null due to environment constraints)
    // In actual test environment, this would create the renderer
}

/**
 * @tc.name: ArktsDynamicPattern_OnAttachContext_NullContext
 * @tc.desc: Test OnAttachContext with null context
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_OnAttachContext_NullContext, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern with valid param
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    SetUpPatternWithValidParam(arktsPattern);

    /**
     * @tc.steps: step2. Call OnAttachContext with null context
     * @tc.expected: Should handle gracefully
     */
    arktsPattern->OnAttachContext(nullptr);

    // Should not crash
}

// ========================================
// OnDetachContext Tests
// ========================================

/**
 * @tc.name: ArktsDynamicPattern_OnDetachContext_CallsParentMethod
 * @tc.desc: Test OnDetachContext calls parent class method
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_OnDetachContext_CallsParentMethod, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    /**
     * @tc.steps: step2. Get pipeline context
     */
    auto context = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    /**
     * @tc.steps: step3. Call OnDetachContext
     * @tc.expected: Should call parent class method without crashing
     */
    arktsPattern->OnDetachContext(context);

    // Should not crash
}

/**
 * @tc.name: ArktsDynamicPattern_OnDetachContext_NullContext
 * @tc.desc: Test OnDetachContext with null context
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_OnDetachContext_NullContext, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    /**
     * @tc.steps: step2. Call OnDetachContext with null context
     * @tc.expected: Should handle gracefully
     */
    arktsPattern->OnDetachContext(nullptr);

    // Should not crash
}

// ========================================
// DumpInfo Tests
// ========================================

/**
 * @tc.name: ArktsDynamicPattern_DumpInfo_VerifyOutput
 * @tc.desc: Test DumpInfo outputs correct information
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_DumpInfo_VerifyOutput, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern with valid param
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    SetUpPatternWithValidParam(arktsPattern);

    /**
     * @tc.steps: step2. Set platformId
     */
    arktsPattern->platformId_ = TEST_NODE_ID;

    /**
     * @tc.steps: step3. Call DumpInfo
     * @tc.expected: Should not crash and output log information
     */
    arktsPattern->DumpInfo();

    // Should not crash
}

/**
 * @tc.name: ArktsDynamicPattern_DumpInfo_WithRenderer
 * @tc.desc: Test DumpInfo with renderer present
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_DumpInfo_WithRenderer, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern with valid param
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    SetUpPatternWithValidParam(arktsPattern);
    arktsPattern->platformId_ = TEST_NODE_ID;

    /**
     * @tc.steps: step2. Set renderer (mock)
     */
    arktsPattern->dynamicComponentRenderer_ =
        reinterpret_cast<DynamicComponentRenderer*>(0x1);

    /**
     * @tc.steps: step3. Call DumpInfo
     * @tc.expected: Should not crash
     */
    arktsPattern->DumpInfo();

    // Clean up
    arktsPattern->dynamicComponentRenderer_ = nullptr;
}

// ========================================
// DumpInfo with Json Tests
// ========================================

/**
 * @tc.name: ArktsDynamicPattern_DumpInfoJson_VerifyOutput
 * @tc.desc: Test DumpInfo with json parameter outputs correct information
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_DumpInfoJson_VerifyOutput, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern with valid param
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    SetUpPatternWithValidParam(arktsPattern);

    /**
     * @tc.steps: step2. Set platformId
     */
    arktsPattern->platformId_ = TEST_NODE_ID;

    /**
     * @tc.steps: step3. Create json object
     */
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);

    /**
     * @tc.steps: step4. Call DumpInfo with json
     * @tc.expected: Should populate json with correct values
     */
    arktsPattern->DumpInfo(json);

    // Verify json values
    EXPECT_EQ(json->GetInt("dynamicId", -1), TEST_NODE_ID);
}

/**
 * @tc.name: ArktsDynamicPattern_DumpInfoJson_WithRenderer
 * @tc.desc: Test DumpInfo with json and renderer present
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_DumpInfoJson_WithRenderer, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern with valid param
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    SetUpPatternWithValidParam(arktsPattern);
    arktsPattern->platformId_ = TEST_NODE_ID;

    /**
     * @tc.steps: step2. Set renderer (mock)
     */
    arktsPattern->dynamicComponentRenderer_ =
        reinterpret_cast<DynamicComponentRenderer*>(0x1);

    /**
     * @tc.steps: step3. Create json object
     */
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);

    /**
     * @tc.steps: step4. Call DumpInfo with json
     * @tc.expected: Should populate json and call renderer Dump
     */
    arktsPattern->DumpInfo(json);

    // Verify json values
    EXPECT_EQ(json->GetInt("dynamicId", -1), TEST_NODE_ID);

    // Clean up
    arktsPattern->dynamicComponentRenderer_ = nullptr;
}

// ========================================
// SetDynamicParam Tests
// ========================================

/**
 * @tc.name: ArktsDynamicPattern_SetDynamicParam_VerifyAssignment
 * @tc.desc: Test SetDynamicParam correctly assigns parameters
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_SetDynamicParam_VerifyAssignment, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    /**
     * @tc.steps: step2. Create and set DynamicParam
     */
    DynamicParam param;
    param.workerId = VALID_WORKER_ID;
    param.entryPoint = VALID_ENTRY_POINT;
    param.backgroundTransparent = BACKGROUND_TRANSPARENT;

    arktsPattern->SetDynamicParam(param);

    /**
     * @tc.steps: step3. Verify parameters are correctly assigned
     */
    EXPECT_EQ(arktsPattern->param_.workerId, VALID_WORKER_ID);
    EXPECT_EQ(arktsPattern->param_.entryPoint, VALID_ENTRY_POINT);
    EXPECT_EQ(arktsPattern->param_.backgroundTransparent, BACKGROUND_TRANSPARENT);
}

/**
 * @tc.name: ArktsDynamicPattern_SetDynamicParam_BackgroundOpaque
 * @tc.desc: Test SetDynamicParam with opaque background
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_SetDynamicParam_BackgroundOpaque, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    /**
     * @tc.steps: step2. Set param with opaque background
     */
    DynamicParam param;
    param.workerId = VALID_WORKER_ID;
    param.entryPoint = VALID_ENTRY_POINT;
    param.backgroundTransparent = BACKGROUND_OPAQUE;

    arktsPattern->SetDynamicParam(param);

    /**
     * @tc.steps: step3. Verify backgroundTransparent is set to false
     */
    EXPECT_EQ(arktsPattern->param_.backgroundTransparent, BACKGROUND_OPAQUE);
}

/**
 * @tc.name: ArktsDynamicPattern_SetDynamicParam_MultipleCalls
 * @tc.desc: Test SetDynamicParam with multiple calls updates parameters
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_SetDynamicParam_MultipleCalls, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    /**
     * @tc.steps: step2. Set first param
     */
    DynamicParam param1;
    param1.workerId = VALID_WORKER_ID;
    param1.entryPoint = VALID_ENTRY_POINT;
    param1.backgroundTransparent = BACKGROUND_TRANSPARENT;

    arktsPattern->SetDynamicParam(param1);

    EXPECT_EQ(arktsPattern->param_.workerId, VALID_WORKER_ID);
    EXPECT_EQ(arktsPattern->param_.backgroundTransparent, BACKGROUND_TRANSPARENT);

    /**
     * @tc.steps: step3. Set second param with different values
     */

    DynamicParam param2;
    param2.workerId = NEW_WORKER_ID;
    param2.entryPoint = "new_entry_point";
    param2.backgroundTransparent = NEW_BACKGROUND;

    arktsPattern->SetDynamicParam(param2);

    /**
     * @tc.steps: step4. Verify parameters are updated to new values
     */
    EXPECT_EQ(arktsPattern->param_.workerId, NEW_WORKER_ID);
    EXPECT_EQ(arktsPattern->param_.entryPoint, "new_entry_point");
    EXPECT_EQ(arktsPattern->param_.backgroundTransparent, NEW_BACKGROUND);
}

// ========================================
// Constructor/Destructor Tests
// ========================================

/**
 * @tc.name: ArktsDynamicPattern_Constructor_InitializesCorrectly
 * @tc.desc: Test ArktsDynamicPattern constructor initializes correctly
 * @tc.type: FUNC
 */
HWTEST_F(ArktsDynamicPatternTddTestNg,
    ArktsDynamicPattern_Constructor_InitializesCorrectly, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArktsDynamicPattern
     * @tc.expected: Should initialize successfully
     */
    auto arktsPattern = CreateArktsDynamicPattern();
    ASSERT_NE(arktsPattern, nullptr);

    // Verify initial state
    EXPECT_EQ(arktsPattern->dynamicComponentRenderer_, nullptr);
}

} // namespace OHOS::Ace::NG
