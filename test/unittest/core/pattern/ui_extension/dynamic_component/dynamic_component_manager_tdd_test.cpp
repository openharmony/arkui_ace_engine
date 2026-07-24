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
#include "adapter/ohos/entrance/ace_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_component_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    // Test constants - using named constants instead of magic numbers
    const float POSITIVE_SIZE = 600.0f;
    const float NEGATIVE_SIZE = -1.0f;
    const float ZERO_SIZE = 0.0f;
    const float RECT_X = 5.0f;
    const float RECT_Y = 5.0f;
    const float RECT_WIDTH = 100.0f;
    const float RECT_HEIGHT = 100.0f;
    const float OFFSET_X = 10.0f;
    const float OFFSET_Y = 20.0f;
    const float PARENT_OFFSET_X = 50.0f;
    const float PARENT_OFFSET_Y = 50.0f;
    const float HOST_OFFSET_X = 2.0f;
    const float HOST_OFFSET_Y = 3.0f;
    const int32_t TEST_NODE_ID = 1;
    const uint64_t NANO_TIMESTAMP = 1000;
    const std::string TEST_TAG = "TestNode";
} // namespace

class DynamicComponentManagerTddTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestCase();
    static void TearDownTestCase();
    RefPtr<FrameNode> CreateTestFrameNode();
    void SetupFrameNodeWithLastOffsets(RefPtr<FrameNode>& frameNode);
};

void DynamicComponentManagerTddTestNg::SetUp() {}

void DynamicComponentManagerTddTestNg::TearDown() {}

void DynamicComponentManagerTddTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}

void DynamicComponentManagerTddTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> DynamicComponentManagerTddTestNg::CreateTestFrameNode()
{
    auto frameNode =
        FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);
    return frameNode;
}

void DynamicComponentManagerTddTestNg::SetupFrameNodeWithLastOffsets(RefPtr<FrameNode>& frameNode)
{
    frameNode->lastFrameRect_ = std::make_unique<RectF>();
    frameNode->lastParentOffsetToWindow_ =
        std::make_unique<OffsetF>(OffsetF(PARENT_OFFSET_X, PARENT_OFFSET_Y));
    frameNode->lastHostParentOffsetToWindow_ = std::make_shared<OffsetF>();
}

// ========================================
// TriggerOnAreaChangeCallback Tests
// ========================================

/**
 * @tc.name: DynamicComponentManager_TriggerOnAreaChangeCallback_StageSizeNotPositive
 * @tc.desc: Test TriggerOnAreaChangeCallback when stage marginFrameSize is not positive (first load case)
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_TriggerOnAreaChangeCallback_StageSizeNotPositive, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get context and stage manager
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto stageManager = context->GetStageManager();
    ASSERT_NE(stageManager, nullptr);
    auto stageNode = stageManager->GetStageNode();
    ASSERT_NE(stageNode, nullptr);

    /**
     * @tc.steps: step2. Set stage marginFrameSize to non-positive
     */
    auto geometryNode = stageNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->frame_.rect_.SetWidth(NEGATIVE_SIZE);
    geometryNode->frame_.rect_.SetHeight(NEGATIVE_SIZE);
    EXPECT_FALSE(geometryNode->GetMarginFrameSize().IsPositive());

    /**
     * @tc.steps: step3. Create frame node and call TriggerOnAreaChangeCallback
     * @tc.expected: Should return early without processing
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);

    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNodePtr, NANO_TIMESTAMP);

    // Should return early, no crash expected
}

/**
 * @tc.name: DynamicComponentManager_TriggerOnAreaChangeCallback_StageSizePositive
 * @tc.desc: Test TriggerOnAreaChangeCallback when stage marginFrameSize is positive
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_TriggerOnAreaChangeCallback_StageSizePositive, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get context and set stage marginFrameSize to positive
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto stageManager = context->GetStageManager();
    ASSERT_NE(stageManager, nullptr);
    auto stageNode = stageManager->GetStageNode();
    ASSERT_NE(stageNode, nullptr);
    auto geometryNode = stageNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->frame_.rect_.SetWidth(POSITIVE_SIZE);
    geometryNode->frame_.rect_.SetHeight(POSITIVE_SIZE);
    EXPECT_TRUE(geometryNode->GetMarginFrameSize().IsPositive());

    /**
     * @tc.steps: step2. Create frame node
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);

    /**
     * @tc.steps: step3. Call TriggerOnAreaChangeCallback without callbacks
     * @tc.expected: Should handle gracefully
     */
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNodePtr, NANO_TIMESTAMP);
}

/**
 * @tc.name: DynamicComponentManager_TriggerOnAreaChangeCallback_NoOnAreaChanged
 * @tc.desc: Test TriggerOnAreaChangeCallback when HasOnAreaChanged returns false
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_TriggerOnAreaChangeCallback_NoOnAreaChanged, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get context and set up stage with positive size
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto stageManager = context->GetStageManager();
    ASSERT_NE(stageManager, nullptr);
    auto stageNode = stageManager->GetStageNode();
    ASSERT_NE(stageNode, nullptr);
    auto geometryNode = stageNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->frame_.rect_.SetWidth(POSITIVE_SIZE);
    geometryNode->frame_.rect_.SetHeight(POSITIVE_SIZE);

    /**
     * @tc.steps: step2. Create frame node and verify no callbacks
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->HasOnAreaChanged());

    /**
     * @tc.steps: step3. Call TriggerOnAreaChangeCallback
     * @tc.expected: Should handle without firing callbacks
     */
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNodePtr, NANO_TIMESTAMP);
}

/**
 * @tc.name: DynamicComponentManager_TriggerOnAreaChangeCallback_WithOnAreaChanged
 * @tc.desc: Test TriggerOnAreaChangeCallback when HasOnAreaChanged returns true
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_TriggerOnAreaChangeCallback_WithOnAreaChanged, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get context and set up stage with positive size
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto stageManager = context->GetStageManager();
    ASSERT_NE(stageManager, nullptr);
    auto stageNode = stageManager->GetStageNode();
    ASSERT_NE(stageNode, nullptr);
    auto geometryNode = stageNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->frame_.rect_.SetWidth(POSITIVE_SIZE);
    geometryNode->frame_.rect_.SetHeight(POSITIVE_SIZE);

    /**
     * @tc.steps: step2. Create frame node with OnAreaChanged callback
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto callback = [](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->SetOnAreaChanged(std::move(callback));
    ASSERT_TRUE(eventHub->HasOnAreaChanged());

    /**
     * @tc.steps: step3. Call TriggerOnAreaChangeCallback
     * @tc.expected: Should fire the callback
     */
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNodePtr, NANO_TIMESTAMP);
}

/**
 * @tc.name: DynamicComponentManager_TriggerOnAreaChangeCallback_WithInnerOnAreaChanged
 * @tc.desc: Test TriggerOnAreaChangeCallback when HasInnerOnAreaChanged returns true
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_TriggerOnAreaChangeCallback_WithInnerOnAreaChanged, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get context and set up stage
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto stageManager = context->GetStageManager();
    ASSERT_NE(stageManager, nullptr);
    auto stageNode = stageManager->GetStageNode();
    ASSERT_NE(stageNode, nullptr);
    auto geometryNode = stageNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->frame_.rect_.SetWidth(POSITIVE_SIZE);
    geometryNode->frame_.rect_.SetHeight(POSITIVE_SIZE);

    /**
     * @tc.steps: step2. Create frame node with inner callback
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto innerCallback = [](const RectF& oldRect,
        const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->onAreaChangedInnerCallbacks_[0] = std::move(innerCallback);
    ASSERT_TRUE(eventHub->HasInnerOnAreaChanged());

    /**
     * @tc.steps: step3. Call TriggerOnAreaChangeCallback
     * @tc.expected: Should handle inner callbacks
     */
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNodePtr, NANO_TIMESTAMP);
}

/**
 * @tc.name: DynamicComponentManager_TriggerOnAreaChangeCallback_RectChanged
 * @tc.desc: Test TriggerOnAreaChangeCallback when current rect differs from last rect
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_TriggerOnAreaChangeCallback_RectChanged, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get context and set up stage
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto stageManager = context->GetStageManager();
    ASSERT_NE(stageManager, nullptr);
    auto stageNode = stageManager->GetStageNode();
    ASSERT_NE(stageNode, nullptr);
    auto geometryNode = stageNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->frame_.rect_.SetWidth(POSITIVE_SIZE);
    geometryNode->frame_.rect_.SetHeight(POSITIVE_SIZE);

    /**
     * @tc.steps: step2. Create frame node with callback and different rect
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto callback = [](const RectF& oldRect,
        const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->SetOnAreaChanged(std::move(callback));
    ASSERT_TRUE(eventHub->HasOnAreaChanged());

    // Set geometry to create different rect
    auto geoNode = frameNode->GetGeometryNode();
    ASSERT_NE(geoNode, nullptr);
    geoNode->frame_.rect_.SetRect(RECT_X, RECT_Y, RECT_WIDTH, RECT_HEIGHT);

    /**
     * @tc.steps: step3. Call TriggerOnAreaChangeCallback
     * @tc.expected: Should call HandleDynamicRenderOnAreaChange due to rect change
     */
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNodePtr, NANO_TIMESTAMP);
}

/**
 * @tc.name: DynamicComponentManager_TriggerOnAreaChangeCallback_RectUnchanged
 * @tc.desc: Test TriggerOnAreaChangeCallback when current rect equals last rect
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_TriggerOnAreaChangeCallback_RectUnchanged, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get context and set up stage
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto stageManager = context->GetStageManager();
    ASSERT_NE(stageManager, nullptr);
    auto stageNode = stageManager->GetStageNode();
    ASSERT_NE(stageNode, nullptr);
    auto geometryNode = stageNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->frame_.rect_.SetWidth(POSITIVE_SIZE);
    geometryNode->frame_.rect_.SetHeight(POSITIVE_SIZE);

    /**
     * @tc.steps: step2. Create frame node with callback and same rect
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto callback = [](const RectF& oldRect,
        const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->SetOnAreaChanged(std::move(callback));
    ASSERT_TRUE(eventHub->HasOnAreaChanged());

    // Set same rect as lastFrameRect
    auto geoNode = frameNode->GetGeometryNode();
    ASSERT_NE(geoNode, nullptr);
    RectF sameRect(RECT_X, RECT_Y, RECT_WIDTH, RECT_HEIGHT);
    geoNode->frame_.rect_ = sameRect;
    frameNode->lastFrameRect_ = std::make_unique<RectF>(sameRect);

    /**
     * @tc.steps: step3. Call TriggerOnAreaChangeCallback
     * @tc.expected: Should not call HandleDynamicRenderOnAreaChange as rect unchanged
     */
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNodePtr, NANO_TIMESTAMP);
}

// ========================================
// HandleDynamicRenderOnAreaChange Tests
// ========================================

/**
 * @tc.name: DynamicComponentManager_HandleDynamicRenderOnAreaChange_NoInnerCallback
 * @tc.desc: Test HandleDynamicRenderOnAreaChange when HasInnerOnAreaChanged returns false
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_HandleDynamicRenderOnAreaChange_NoInnerCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->HasInnerOnAreaChanged());

    /**
     * @tc.steps: step2. Create test rects and offsets
     */
    RectF currFrameRect(RECT_X, RECT_Y, RECT_WIDTH, RECT_HEIGHT);
    OffsetF currParentOffset(OFFSET_X, OFFSET_Y);
    OffsetF currHostParentOffset(HOST_OFFSET_X, HOST_OFFSET_Y);

    /**
     * @tc.steps: step3. Call HandleDynamicRenderOnAreaChange
     * @tc.expected: Should not fire inner callback
     */
    DynamicComponentManager::HandleDynamicRenderOnAreaChange(
        frameNodePtr, currFrameRect, currParentOffset, currHostParentOffset);
}

/**
 * @tc.name: DynamicComponentManager_HandleDynamicRenderOnAreaChange_WithInnerCallback
 * @tc.desc: Test HandleDynamicRenderOnAreaChange when HasInnerOnAreaChanged returns true
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_HandleDynamicRenderOnAreaChange_WithInnerCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node with inner callback
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto innerCallback = [](const RectF& oldRect,
        const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->onAreaChangedInnerCallbacks_[0] = std::move(innerCallback);
    ASSERT_TRUE(eventHub->HasInnerOnAreaChanged());

    /**
     * @tc.steps: step2. Create test rects and offsets
     */
    RectF currFrameRect(RECT_X, RECT_Y, RECT_WIDTH, RECT_HEIGHT);
    OffsetF currParentOffset(OFFSET_X, OFFSET_Y);
    OffsetF currHostParentOffset(HOST_OFFSET_X, HOST_OFFSET_Y);

    /**
     * @tc.steps: step3. Call HandleDynamicRenderOnAreaChange
     * @tc.expected: Should fire inner callback
     */
    DynamicComponentManager::HandleDynamicRenderOnAreaChange(
        frameNodePtr, currFrameRect, currParentOffset, currHostParentOffset);
}

/**
 * @tc.name: DynamicComponentManager_HandleDynamicRenderOnAreaChange_NoOnAreaChanged
 * @tc.desc: Test HandleDynamicRenderOnAreaChange when HasOnAreaChanged returns false
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_HandleDynamicRenderOnAreaChange_NoOnAreaChanged, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->HasOnAreaChanged());

    /**
     * @tc.steps: step2. Create test rects and offsets
     */
    RectF currFrameRect(RECT_X, RECT_Y, RECT_WIDTH, RECT_HEIGHT);
    OffsetF currParentOffset(OFFSET_X, OFFSET_Y);
    OffsetF currHostParentOffset(HOST_OFFSET_X, HOST_OFFSET_Y);

    /**
     * @tc.steps: step3. Call HandleDynamicRenderOnAreaChange
     * @tc.expected: Should not fire OnAreaChanged callback
     */
    DynamicComponentManager::HandleDynamicRenderOnAreaChange(
        frameNodePtr, currFrameRect, currParentOffset, currHostParentOffset);
}

/**
 * @tc.name: DynamicComponentManager_HandleDynamicRenderOnAreaChange_WithOnAreaChanged
 * @tc.desc: Test HandleDynamicRenderOnAreaChange when HasOnAreaChanged returns true
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_HandleDynamicRenderOnAreaChange_WithOnAreaChanged, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node with OnAreaChanged callback
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto callback = [](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->SetOnAreaChanged(std::move(callback));
    ASSERT_TRUE(eventHub->HasOnAreaChanged());

    /**
     * @tc.steps: step2. Create test rects and offsets
     */
    RectF currFrameRect(RECT_X, RECT_Y, RECT_WIDTH, RECT_HEIGHT);
    OffsetF currParentOffset(OFFSET_X, OFFSET_Y);
    OffsetF currHostParentOffset(HOST_OFFSET_X, HOST_OFFSET_Y);

    /**
     * @tc.steps: step3. Call HandleDynamicRenderOnAreaChange
     * @tc.expected: Should fire OnAreaChanged callback
     */
    DynamicComponentManager::HandleDynamicRenderOnAreaChange(
        frameNodePtr, currFrameRect, currParentOffset, currHostParentOffset);
}

/**
 * @tc.name: DynamicComponentManager_HandleDynamicRenderOnAreaChange_BothCallbacks
 * @tc.desc: Test HandleDynamicRenderOnAreaChange with both inner and outer callbacks
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_HandleDynamicRenderOnAreaChange_BothCallbacks, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node with both callbacks
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    // Add inner callback
    auto innerCallback = [](const RectF& oldRect,
        const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->onAreaChangedInnerCallbacks_[0] = std::move(innerCallback);
    ASSERT_TRUE(eventHub->HasInnerOnAreaChanged());

    // Add outer callback
    auto outerCallback = [](const RectF& oldRect,
        const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->SetOnAreaChanged(std::move(outerCallback));
    ASSERT_TRUE(eventHub->HasOnAreaChanged());

    /**
     * @tc.steps: step2. Create test rects and offsets
     */
    RectF currFrameRect(RECT_X, RECT_Y, RECT_WIDTH, RECT_HEIGHT);
    OffsetF currParentOffset(OFFSET_X, OFFSET_Y);
    OffsetF currHostParentOffset(HOST_OFFSET_X, HOST_OFFSET_Y);

    /**
     * @tc.steps: step3. Call HandleDynamicRenderOnAreaChange
     * @tc.expected: Should fire both callbacks
     */
    DynamicComponentManager::HandleDynamicRenderOnAreaChange(
        frameNodePtr, currFrameRect, currParentOffset, currHostParentOffset);
}

/**
 * @tc.name: DynamicComponentManager_HandleDynamicRenderOnAreaChange_VerifyStateUpdate
 * @tc.desc: Test HandleDynamicRenderOnAreaChange correctly updates frameNode state
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_HandleDynamicRenderOnAreaChange_VerifyStateUpdate, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node with callbacks
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto innerCallback = [](const RectF& oldRect,
        const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->onAreaChangedInnerCallbacks_[0] = std::move(innerCallback);
    ASSERT_TRUE(eventHub->HasInnerOnAreaChanged());

    auto callback = [](const RectF& oldRect,
        const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->SetOnAreaChanged(std::move(callback));
    ASSERT_TRUE(eventHub->HasOnAreaChanged());

    /**
     * @tc.steps: step2. Create test rects and offsets
     */
    RectF currFrameRect(RECT_X, RECT_Y, RECT_WIDTH, RECT_HEIGHT);
    OffsetF currParentOffset(OFFSET_X, OFFSET_Y);
    OffsetF currHostParentOffset(HOST_OFFSET_X, HOST_OFFSET_Y);

    /**
     * @tc.steps: step3. Call HandleDynamicRenderOnAreaChange
     */
    DynamicComponentManager::HandleDynamicRenderOnAreaChange(
        frameNodePtr, currFrameRect, currParentOffset, currHostParentOffset);

    /**
     * @tc.steps: step4. Verify frameNode state is updated
     */
    EXPECT_EQ(frameNode->GetLastFrameRect(), currFrameRect);
    EXPECT_EQ(frameNode->GetLastParentOffsetToWindow(), currParentOffset);
    EXPECT_EQ(frameNode->GetLastHostParentOffsetToWindow(), currHostParentOffset);
}

// ========================================
// Edge Cases and Boundary Tests
// ========================================

/**
 * @tc.name: DynamicComponentManager_TriggerOnAreaChangeCallback_NullFrameNode
 * @tc.desc: Test TriggerOnAreaChangeCallback handles null frameNode gracefully
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_TriggerOnAreaChangeCallback_NullFrameNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call TriggerOnAreaChangeCallback with null frameNode
     * @tc.expected: Should handle gracefully without crash
     */
    DynamicComponentManager::TriggerOnAreaChangeCallback(nullptr, NANO_TIMESTAMP);
}

/**
 * @tc.name: DynamicComponentManager_TriggerOnAreaChangeCallback_ZeroTimestamp
 * @tc.desc: Test TriggerOnAreaChangeCallback with zero nanoTimestamp
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_TriggerOnAreaChangeCallback_ZeroTimestamp, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get context and set up stage
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto stageManager = context->GetStageManager();
    ASSERT_NE(stageManager, nullptr);
    auto stageNode = stageManager->GetStageNode();
    ASSERT_NE(stageNode, nullptr);
    auto geometryNode = stageNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->frame_.rect_.SetWidth(POSITIVE_SIZE);
    geometryNode->frame_.rect_.SetHeight(POSITIVE_SIZE);

    /**
     * @tc.steps: step2. Create frame node
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto callback = [](const RectF& oldRect,
        const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->SetOnAreaChanged(std::move(callback));

    /**
     * @tc.steps: step3. Call TriggerOnAreaChangeCallback with zero timestamp
     */
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNodePtr, 0);
}

/**
 * @tc.name: DynamicComponentManager_HandleDynamicRenderOnAreaChange_ZeroRect
 * @tc.desc: Test HandleDynamicRenderOnAreaChange with zero-sized rect
 * @tc.type: FUNC
 */
HWTEST_F(DynamicComponentManagerTddTestNg,
    DynamicComponentManager_HandleDynamicRenderOnAreaChange_ZeroRect, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node with callbacks
     */
    auto frameNode = CreateTestFrameNode();
    ASSERT_NE(frameNode, nullptr);
    FrameNode* frameNodePtr = &(*frameNode);
    SetupFrameNodeWithLastOffsets(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto innerCallback = [](const RectF& oldRect,
        const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->onAreaChangedInnerCallbacks_[0] = std::move(innerCallback);

    auto callback = [](const RectF& oldRect,
        const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->SetOnAreaChanged(std::move(callback));

    /**
     * @tc.steps: step2. Create zero-sized rect
     */
    RectF zeroRect(ZERO_SIZE, ZERO_SIZE, ZERO_SIZE, ZERO_SIZE);
    OffsetF zeroOffset(ZERO_SIZE, ZERO_SIZE);

    /**
     * @tc.steps: step3. Call HandleDynamicRenderOnAreaChange
     */
    DynamicComponentManager::HandleDynamicRenderOnAreaChange(
        frameNodePtr, zeroRect, zeroOffset, zeroOffset);
}

} // namespace OHOS::Ace::NG
