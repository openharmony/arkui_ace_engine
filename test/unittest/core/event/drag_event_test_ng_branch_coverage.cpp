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

#include "test/unittest/core/event/drag_event_test_ng.h"

#include "core/common/event_manager.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class DragEventBranchCoverageNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        testing::FLAGS_gmock_verbose = "error";
    }

    static void TearDownTestSuite() {}

    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }

    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }
};

struct DragEventActuatorContext {
    RefPtr<FrameNode> frameNode;
    RefPtr<EventHub> eventHub;
    RefPtr<GestureEventHub> gestureEventHub;
    RefPtr<DragEventActuator> actuator;
};

DragEventActuatorContext CreateDragEventActuatorContext(const std::string& tag, const RefPtr<Pattern>& pattern)
{
    DragEventActuatorContext context;
    context.frameNode = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), pattern, false);
    EXPECT_NE(context.frameNode, nullptr);
    context.eventHub = context.frameNode->GetEventHub<EventHub>();
    EXPECT_NE(context.eventHub, nullptr);
    context.eventHub->AttachHost(context.frameNode);
    context.gestureEventHub = context.frameNode->GetOrCreateGestureEventHub();
    EXPECT_NE(context.gestureEventHub, nullptr);
    context.actuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(context.gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    EXPECT_NE(context.actuator, nullptr);
    return context;
}

void PreparePipelineForDragEventTest(const RefPtr<MockPipelineContext>& pipeline)
{
    ASSERT_NE(pipeline, nullptr);
    if (!pipeline->GetTaskExecutor()) {
        pipeline->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>());
    }
    if (!pipeline->GetEventManager()) {
        pipeline->SetEventManager(AceType::MakeRefPtr<EventManager>());
    }
    if (!pipeline->GetDragDropManager()) {
        pipeline->dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();
    }
}

RefPtr<OverlayManager> CreateOverlayManagerForReset(const RefPtr<MockPipelineContext>& pipeline)
{
    auto rootNode = pipeline->GetRootElement();
    EXPECT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    EXPECT_NE(overlayManager, nullptr);
    pipeline->overlayManager_ = overlayManager;
    return overlayManager;
}
} // namespace

/**
 * @tc.name: DragEventActuatorRestartDragTaskGuardCoverage001
 * @tc.desc: Cover RestartDragTask when gesture hub or host frame node is missing.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventBranchCoverageNg, DragEventActuatorRestartDragTaskGuardCoverage001, TestSize.Level1)
{
    auto noHubActuator = AceType::MakeRefPtr<DragEventActuator>(
        WeakPtr<GestureEventHub>(), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(noHubActuator, nullptr);
    int32_t noHubStartCount = 0;
    noHubActuator->actionStart_ = [&noHubStartCount](GestureEvent& info) {
        ++noHubStartCount;
    };
    GestureEvent info;
    noHubActuator->RestartDragTask(info);
    EXPECT_EQ(noHubStartCount, 0);
    EXPECT_FALSE(noHubActuator->GetRestartDrag());

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto noHostActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(noHostActuator, nullptr);
    int32_t noHostStartCount = 0;
    noHostActuator->actionStart_ = [&noHostStartCount](GestureEvent& eventInfo) {
        ++noHostStartCount;
    };
    noHostActuator->RestartDragTask(info);
    EXPECT_EQ(noHostStartCount, 0);
    EXPECT_FALSE(noHostActuator->GetRestartDrag());
}

/**
 * @tc.name: DragEventActuatorRestartDragTaskGuardCoverage002
 * @tc.desc: Cover RestartDragTask when frame node context or event manager is missing.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventBranchCoverageNg, DragEventActuatorRestartDragTaskGuardCoverage002, TestSize.Level1)
{
    auto context = CreateDragEventActuatorContext(V2::TEXT_ETS_TAG, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(context.frameNode, nullptr);
    ASSERT_NE(context.actuator, nullptr);

    int32_t actionStartCount = 0;
    context.actuator->actionStart_ = [&actionStartCount](GestureEvent& info) {
        ++actionStartCount;
    };

    GestureEvent info;
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto originalContext = context.frameNode->context_;
    auto originalCurrentPipeline = MockPipelineContext::pipeline_;

    context.frameNode->context_ = nullptr;
    MockPipelineContext::pipeline_ = nullptr;
    context.actuator->RestartDragTask(info);
    EXPECT_EQ(actionStartCount, 1);
    EXPECT_TRUE(context.actuator->GetRestartDrag());

    MockPipelineContext::pipeline_ = originalCurrentPipeline;
    context.frameNode->context_ = AceType::RawPtr(pipeline);
    pipeline->SetEventManager(nullptr);
    context.actuator->RestartDragTask(info);
    EXPECT_EQ(actionStartCount, 2);
    EXPECT_TRUE(context.actuator->GetRestartDrag());

    pipeline->SetEventManager(AceType::MakeRefPtr<EventManager>());
    context.actuator->RestartDragTask(info);
    EXPECT_EQ(actionStartCount, 3);
    EXPECT_FALSE(context.actuator->GetRestartDrag());

    MockPipelineContext::pipeline_ = originalCurrentPipeline;
    context.frameNode->context_ = originalContext;
}

/**
 * @tc.name: DragEventActuatorCurrentNodeStatusSuitableForDraggingCoverage001
 * @tc.desc: Cover current node drag status guards for null node, forbidden drag and axis-originated input.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventBranchCoverageNg, DragEventActuatorCurrentNodeStatusSuitableForDraggingCoverage001, TestSize.Level1)
{
    auto context = CreateDragEventActuatorContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(context.frameNode, nullptr);
    ASSERT_NE(context.gestureEventHub, nullptr);
    ASSERT_NE(context.actuator, nullptr);

    TouchRestrict touchRestrict = { TouchRestrict::NONE };
    EXPECT_FALSE(context.actuator->IsCurrentNodeStatusSuitableForDragging(nullptr, touchRestrict));
    EXPECT_FALSE(DragDropFuncWrapper::IsCurrentNodeStatusSuitableForDragging(nullptr, touchRestrict));

    context.gestureEventHub->SetDragForbiddenForcely(true);
    EXPECT_FALSE(context.actuator->IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));
    EXPECT_FALSE(DragDropFuncWrapper::IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));

    context.gestureEventHub->SetDragForbiddenForcely(false);
    context.frameNode->draggable_ = false;
    context.frameNode->customerSet_ = true;
    EXPECT_FALSE(context.actuator->IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));
    EXPECT_FALSE(DragDropFuncWrapper::IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));

    context.frameNode->customerSet_ = false;
    touchRestrict.inputEventType = InputEventType::AXIS;
    EXPECT_FALSE(context.actuator->IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));
    EXPECT_FALSE(DragDropFuncWrapper::IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));

    touchRestrict.inputEventType = InputEventType::TOUCH_SCREEN;
    touchRestrict.touchEvent.convertInfo = { UIInputEventType::AXIS, UIInputEventType::MOUSE };
    EXPECT_FALSE(context.actuator->IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));
    EXPECT_FALSE(DragDropFuncWrapper::IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));
}

/**
 * @tc.name: DragEventActuatorCurrentNodeStatusSuitableForDraggingCoverage002
 * @tc.desc: Cover text-drag selection and parent drag-forbidden branches.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventBranchCoverageNg, DragEventActuatorCurrentNodeStatusSuitableForDraggingCoverage002, TestSize.Level1)
{
    auto context = CreateDragEventActuatorContext(V2::TEXT_ETS_TAG, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(context.frameNode, nullptr);
    ASSERT_NE(context.gestureEventHub, nullptr);
    ASSERT_NE(context.actuator, nullptr);

    auto textPattern = context.frameNode->GetPattern<TextBase>();
    ASSERT_NE(textPattern, nullptr);

    TouchRestrict touchRestrict = { TouchRestrict::NONE };
    context.gestureEventHub->SetTextDraggable(true);
    EXPECT_FALSE(context.actuator->IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));
    EXPECT_FALSE(DragDropFuncWrapper::IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));

    textPattern->textSelector_.baseOffset = 0;
    textPattern->textSelector_.destinationOffset = 1;
    EXPECT_TRUE(context.actuator->IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));
    EXPECT_TRUE(DragDropFuncWrapper::IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));

    auto parentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    auto parentEventHub = parentNode->GetEventHub<EventHub>();
    ASSERT_NE(parentEventHub, nullptr);
    parentEventHub->AttachHost(parentNode);
    auto parentGestureHub = parentNode->GetOrCreateGestureEventHub();
    ASSERT_NE(parentGestureHub, nullptr);
    parentGestureHub->SetDragForbiddenForcely(true);
    context.frameNode->SetParent(parentNode);

    EXPECT_FALSE(context.actuator->IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));
    EXPECT_FALSE(DragDropFuncWrapper::IsCurrentNodeStatusSuitableForDragging(context.frameNode, touchRestrict));
}

/**
 * @tc.name: DragEventActuatorGetFrameNodeCoverage001
 * @tc.desc: Cover GetFrameNode with missing gesture hub, missing host and valid host.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventBranchCoverageNg, DragEventActuatorGetFrameNodeCoverage001, TestSize.Level1)
{
    auto noHubActuator = AceType::MakeRefPtr<DragEventActuator>(
        WeakPtr<GestureEventHub>(), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(noHubActuator, nullptr);
    EXPECT_EQ(noHubActuator->GetFrameNode(), nullptr);

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto noHostActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(noHostActuator, nullptr);
    EXPECT_EQ(noHostActuator->GetFrameNode(), nullptr);

    auto context = CreateDragEventActuatorContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(context.actuator, nullptr);
    EXPECT_EQ(context.actuator->GetFrameNode(), context.frameNode);
}

/**
 * @tc.name: DragEventActuatorResetDragStatusCoverage001
 * @tc.desc: Cover ResetDragStatus by clearing preview pixel map, gather node and event column state.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventBranchCoverageNg, DragEventActuatorResetDragStatusCoverage001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    PreparePipelineForDragEventTest(pipeline);
    auto overlayManager = CreateOverlayManagerForReset(pipeline);
    ASSERT_NE(overlayManager, nullptr);

    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    {
        auto gatherNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<TextPattern>(), false);
        auto pixelMapNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
        auto eventColumnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
        ASSERT_NE(gatherNode, nullptr);
        ASSERT_NE(pixelMapNode, nullptr);
        ASSERT_NE(eventColumnNode, nullptr);

        gatherNode->MountToParent(rootNode);
        pixelMapNode->MountToParent(rootNode);
        eventColumnNode->MountToParent(rootNode);

        overlayManager->gatherNodeWeak_ = gatherNode;
        overlayManager->pixmapColumnNodeWeak_ = pixelMapNode;
        overlayManager->eventColumnNodeWeak_ = eventColumnNode;
        overlayManager->hasGatherNode_ = true;
        overlayManager->hasPixelMap_ = true;
        overlayManager->hasEvent_ = true;
    }

    DragEventActuator::ResetDragStatus();

    EXPECT_FALSE(overlayManager->hasGatherNode_);
    EXPECT_FALSE(overlayManager->hasPixelMap_);
    EXPECT_FALSE(overlayManager->hasEvent_);
    EXPECT_EQ(overlayManager->gatherNodeWeak_.Upgrade(), nullptr);
    EXPECT_EQ(overlayManager->pixmapColumnNodeWeak_.Upgrade(), nullptr);
    EXPECT_EQ(overlayManager->eventColumnNodeWeak_.Upgrade(), nullptr);
}
} // namespace OHOS::Ace::NG
