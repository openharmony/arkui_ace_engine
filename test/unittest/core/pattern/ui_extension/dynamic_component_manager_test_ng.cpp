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
#include "adapter/ohos/entrance/ace_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_component_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const float POSITIVE_SIZE = 600.0f;
    const float NEGATIVE_SIZE = -1.0f;
} // namespace

class DynamicPatternManagerTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DynamicPatternManagerTestNg::SetUp() {}

void DynamicPatternManagerTestNg::TearDown() {}

void DynamicPatternManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}

void DynamicPatternManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DynamicPatternManagerTestNg001
 * @tc.desc: Test DynamicPattern TriggerOnAreaChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternManagerTestNg, DynamicPatternManagerTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test method TriggerOnAreaChangeCallback
     */
    auto context = PipelineContext::GetCurrentContext();
    EXPECT_NE(context, nullptr);
    auto stageManager = context->GetStageManager();
    EXPECT_NE(stageManager, nullptr);
    auto stageNode = stageManager->GetStageNode();
    EXPECT_NE(stageNode, nullptr);
    auto geometryNode = stageNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    EXPECT_FALSE(geometryNode->GetMarginFrameSize().IsPositive());
    auto frameNodeRef = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNodeRef, nullptr);
    FrameNode* frameNode = &(*frameNodeRef);
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNode, 1);

    geometryNode->frame_.rect_.SetWidth(POSITIVE_SIZE);
    geometryNode->frame_.rect_.SetHeight(POSITIVE_SIZE);
    EXPECT_TRUE(geometryNode->GetMarginFrameSize().IsPositive());
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNode, 1);

    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->HasOnAreaChanged());
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNode, 1);

    auto func = [](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->SetOnAreaChanged(std::move(func));
    ASSERT_TRUE(eventHub->HasOnAreaChanged());
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNode, 1);
}

/**
 * @tc.name: DynamicPatternManagerTestNg002
 * @tc.desc: Test DynamicPattern HandleDynamicRenderOnAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternManagerTestNg, DynamicPatternManagerTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test method TriggerOnAreaChangeCallback
     */
    auto frameNodeRef = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNodeRef, nullptr);
    FrameNode* frameNode = &(*frameNodeRef);
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNode, 1);

    /**
     * @tc.steps: step2. test method HandleDynamicRenderOnAreaChange
     */
    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->HasInnerOnAreaChanged());
    RectF rectF(5, 5, 1, 1);
    OffsetF offsetF(2.0, 3.0);
    OffsetF offsetF2(2.0, 3.0);
    frameNode->lastFrameRect_ = std::make_unique<RectF>();
    frameNode->lastParentOffsetToWindow_ = std::make_unique<OffsetF>(OffsetF(50.0f, 50.0f));
    frameNode->lastHostParentOffsetToWindow_ = std::make_shared<OffsetF>();
    DynamicComponentManager::HandleDynamicRenderOnAreaChange(frameNode, rectF, offsetF, offsetF2);

    auto func = [](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->onAreaChangedInnerCallbacks_[0] = std::move(func);
    ASSERT_TRUE(eventHub->HasInnerOnAreaChanged());

    DynamicComponentManager::HandleDynamicRenderOnAreaChange(frameNode, rectF, offsetF, offsetF2);
    ASSERT_FALSE(eventHub->HasOnAreaChanged());
    eventHub->SetOnAreaChanged(std::move(func));
    ASSERT_TRUE(eventHub->HasOnAreaChanged());
    DynamicComponentManager::HandleDynamicRenderOnAreaChange(frameNode, rectF, offsetF, offsetF2);
}

/**
 * @tc.name: DynamicPatternManagerTestNg003
 * @tc.desc: Test DynamicPattern TriggerOnAreaChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternManagerTestNg, DynamicPatternManagerTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test method TriggerOnAreaChangeCallback
     */
    auto context = PipelineContext::GetCurrentContext();
    EXPECT_NE(context, nullptr);
    auto stageManager = context->GetStageManager();
    EXPECT_NE(stageManager, nullptr);
    auto stageNode = stageManager->GetStageNode();
    EXPECT_NE(stageNode, nullptr);
    auto geometryNode = stageNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    EXPECT_TRUE(geometryNode->GetMarginFrameSize().IsPositive());
    auto frameNodeRef = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNodeRef, nullptr);
    FrameNode* frameNode = &(*frameNodeRef);
    geometryNode->frame_.rect_.SetWidth(NEGATIVE_SIZE);
    geometryNode->frame_.rect_.SetHeight(NEGATIVE_SIZE);
    EXPECT_FALSE(geometryNode->GetMarginFrameSize().IsPositive());
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto func = [](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    eventHub->SetOnAreaChanged(std::move(func));
    ASSERT_TRUE(eventHub->HasOnAreaChanged());
    frameNode->lastHostParentOffsetToWindow_ = std::make_shared<OffsetF>();
    ASSERT_NE(frameNode->GetLastHostParentOffsetToWindow(), nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    ASSERT_EQ(renderContext->GetPositionProperty(), nullptr);

    auto top = CalcDimension(1.0);
    auto bottom = CalcDimension(2.0);
    auto start = CalcDimension(3.0);
    auto end = CalcDimension(4.0);

    EdgesParam edges;
    edges.SetTop(top);
    edges.SetBottom(bottom);
    edges.start = start;
    edges.end = end;
    renderContext->UpdateOffsetEdges(edges);
    ASSERT_NE(renderContext->GetPositionProperty(), nullptr);
    DynamicComponentManager::TriggerOnAreaChangeCallback(frameNode, 1);
}
} // namespace OHOS::Ace::NG
