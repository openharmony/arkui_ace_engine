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

#include "test/unittest/core/event/drag_event/drag_event_common_test_ng.h"

#include "core/common/event_manager.h"
#include "core/components_ng/event/drag_drop_event.h"
#include "core/components_ng/gestures/recognizers/sequenced_recognizer.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_handler.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_TOUCH_ID = 7;
constexpr float TEST_GLOBAL_X = 33.0f;
constexpr float TEST_GLOBAL_Y = 44.0f;
constexpr float TEST_SCREEN_X = 55.0f;
constexpr float TEST_SCREEN_Y = 66.0f;
constexpr float TEST_DISPLAY_X = 77.0f;
constexpr float TEST_DISPLAY_Y = 88.0f;
constexpr float TEST_PRE_SCALE = 1.5f;

struct DragDropEventActuatorContext {
    RefPtr<FrameNode> frameNode;
    RefPtr<EventHub> eventHub;
    RefPtr<GestureEventHub> gestureEventHub;
    RefPtr<DragDropEventActuator> actuator;
};

void PreparePipelineForDragDropEventTest(const RefPtr<MockPipelineContext>& pipeline)
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
    if (!pipeline->GetOverlayManager()) {
        auto rootNode = pipeline->GetRootElement();
        ASSERT_NE(rootNode, nullptr);
        pipeline->overlayManager_ = AceType::MakeRefPtr<OverlayManager>(rootNode);
    }
}

DragDropEventActuatorContext CreateDragDropContext(const std::string& tag, const RefPtr<Pattern>& pattern,
    bool draggable = true)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    PreparePipelineForDragDropEventTest(pipeline);

    DragDropEventActuatorContext context;
    context.frameNode = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), pattern, false);
    EXPECT_NE(context.frameNode, nullptr);
    context.frameNode->draggable_ = draggable;
    context.frameNode->customerSet_ = false;
    context.eventHub = context.frameNode->GetEventHub<EventHub>();
    EXPECT_NE(context.eventHub, nullptr);
    context.eventHub->AttachHost(context.frameNode);
    context.gestureEventHub = context.frameNode->GetOrCreateGestureEventHub();
    EXPECT_NE(context.gestureEventHub, nullptr);
    context.actuator =
        AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(context.gestureEventHub)));
    EXPECT_NE(context.actuator, nullptr);
    return context;
}

TouchRestrict CreateTouchRestrict(SourceType sourceType = SourceType::TOUCH, int32_t touchId = TEST_TOUCH_ID)
{
    TouchRestrict touchRestrict = { TouchRestrict::CLICK };
    touchRestrict.sourceType = sourceType;
    touchRestrict.touchEvent.id = touchId;
    touchRestrict.touchEvent.type = TouchType::DOWN;
    touchRestrict.touchEvent.sourceType = sourceType;
    touchRestrict.touchEvent.x = TEST_GLOBAL_X;
    touchRestrict.touchEvent.y = TEST_GLOBAL_Y;
    touchRestrict.touchEvent.screenX = TEST_SCREEN_X;
    touchRestrict.touchEvent.screenY = TEST_SCREEN_Y;
    touchRestrict.touchEvent.globalDisplayX = TEST_DISPLAY_X;
    touchRestrict.touchEvent.globalDisplayY = TEST_DISPLAY_Y;
    return touchRestrict;
}

void CollectTouchTarget(DragDropEventActuatorContext& context, const TouchRestrict& touchRestrict,
    TouchTestResult& result)
{
    auto getEventTargetImpl = context.eventHub->CreateGetEventTargetImpl();
    ASSERT_NE(getEventTargetImpl, nullptr);
    ResponseLinkResult responseLinkResult;
    context.actuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, touchRestrict, getEventTargetImpl, result, responseLinkResult);
}

void MountGatherNode(const RefPtr<OverlayManager>& overlayManager)
{
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    auto gatherNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>(), false);
    ASSERT_NE(gatherNode, nullptr);
    gatherNode->MountToParent(rootNode);
    overlayManager->gatherNodeWeak_ = gatherNode;
    overlayManager->hasGatherNode_ = true;
}

void MountPixelMapAndEventColumnNodes(const RefPtr<OverlayManager>& overlayManager)
{
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    auto pixelMapNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    auto eventColumnNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(pixelMapNode, nullptr);
    ASSERT_NE(eventColumnNode, nullptr);
    pixelMapNode->MountToParent(rootNode);
    eventColumnNode->MountToParent(rootNode);
    overlayManager->pixmapColumnNodeWeak_ = pixelMapNode;
    overlayManager->eventColumnNodeWeak_ = eventColumnNode;
    overlayManager->hasPixelMap_ = true;
}

TouchEventInfo CreateTouchEventInfo(int32_t fingerId, TouchType touchType)
{
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo(fingerId);
    touchInfo.SetTouchType(touchType);
    touchInfo.SetGlobalLocation(Offset(TEST_GLOBAL_X, TEST_GLOBAL_Y));
    touchInfo.SetScreenLocation(Offset(TEST_SCREEN_X, TEST_SCREEN_Y));
    touchInfo.SetGlobalDisplayLocation(Offset(TEST_DISPLAY_X, TEST_DISPLAY_Y));
    info.AddTouchLocationInfo(std::move(touchInfo));
    return info;
}
} // namespace

class DragDropEventTestCoverageNg : public DragEventCommonTestNg {
public:
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
    }

    void SetUp() override
    {
        MockPipelineContext::SetUp();
        SystemProperties::dragDropFrameworkStatus_ = 1;
        auto pipeline = MockPipelineContext::GetCurrent();
        PreparePipelineForDragDropEventTest(pipeline);
    }

    void TearDown() override
    {
        SystemProperties::dragDropFrameworkStatus_ = 0;
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: DragDropEventActuatorOnCollectTouchTargetGuardCoverage001
 * @tc.desc: Cover OnCollectTouchTarget early returns for drag-forbidden, user-set and axis-originated cases.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropEventTestCoverageNg, DragDropEventActuatorOnCollectTouchTargetGuardCoverage001, TestSize.Level1)
{
    {
        auto context = CreateDragDropContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
        ASSERT_NE(context.gestureEventHub, nullptr);
        context.gestureEventHub->SetDragForbiddenForcely(true);
        TouchTestResult result;
        CollectTouchTarget(context, CreateTouchRestrict(), result);
        EXPECT_TRUE(result.empty());
        EXPECT_EQ(context.actuator->dragDropInitiatingHandler_->GetDragDropInitiatingStatus(),
            DragDropInitiatingStatus::IDLE);
        EXPECT_EQ(context.actuator->SequencedRecognizer_, nullptr);
    }

    {
        auto context = CreateDragDropContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>(), false);
        ASSERT_NE(context.frameNode, nullptr);
        context.frameNode->customerSet_ = true;
        TouchTestResult result;
        CollectTouchTarget(context, CreateTouchRestrict(), result);
        EXPECT_TRUE(result.empty());
        EXPECT_EQ(context.actuator->dragDropInitiatingHandler_->GetDragDropInitiatingStatus(),
            DragDropInitiatingStatus::IDLE);
        EXPECT_EQ(context.actuator->SequencedRecognizer_, nullptr);
    }

    {
        auto context = CreateDragDropContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
        auto touchRestrict = CreateTouchRestrict();
        touchRestrict.inputEventType = InputEventType::AXIS;
        TouchTestResult result;
        CollectTouchTarget(context, touchRestrict, result);
        EXPECT_TRUE(result.empty());
        EXPECT_EQ(context.actuator->dragDropInitiatingHandler_->GetDragDropInitiatingStatus(),
            DragDropInitiatingStatus::IDLE);
        EXPECT_EQ(context.actuator->SequencedRecognizer_, nullptr);
    }

    {
        auto context = CreateDragDropContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
        auto touchRestrict = CreateTouchRestrict();
        touchRestrict.touchEvent.convertInfo = { UIInputEventType::AXIS, UIInputEventType::MOUSE };
        TouchTestResult result;
        CollectTouchTarget(context, touchRestrict, result);
        EXPECT_TRUE(result.empty());
        EXPECT_EQ(context.actuator->dragDropInitiatingHandler_->GetDragDropInitiatingStatus(),
            DragDropInitiatingStatus::IDLE);
        EXPECT_EQ(context.actuator->SequencedRecognizer_, nullptr);
    }
}

/**
 * @tc.name: DragDropEventActuatorOnCollectTouchTargetSourceCoverage001
 * @tc.desc: Cover OnCollectTouchTarget source routing for mouse and touch.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropEventTestCoverageNg, DragDropEventActuatorOnCollectTouchTargetSourceCoverage001, TestSize.Level1)
{
    auto mouseContext = CreateDragDropContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
    TouchTestResult mouseResult;
    CollectTouchTarget(mouseContext, CreateTouchRestrict(SourceType::MOUSE), mouseResult);
    EXPECT_EQ(mouseResult.size(), 1UL);
    EXPECT_NE(mouseContext.actuator->panRecognizer_, nullptr);
    EXPECT_NE(mouseContext.actuator->SequencedRecognizer_, nullptr);
    EXPECT_EQ(mouseContext.actuator->previewLongPressRecognizer_, nullptr);
    EXPECT_EQ(mouseContext.actuator->dragDropInitiatingHandler_->GetDragDropInitiatingStatus(),
        DragDropInitiatingStatus::READY);

    auto touchContext = CreateDragDropContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
    TouchTestResult touchResult;
    CollectTouchTarget(touchContext, CreateTouchRestrict(SourceType::TOUCH), touchResult);
    EXPECT_EQ(touchResult.size(), 2UL);
    EXPECT_NE(touchContext.actuator->panRecognizer_, nullptr);
    EXPECT_NE(touchContext.actuator->longPressRecognizer_, nullptr);
    EXPECT_NE(touchContext.actuator->previewLongPressRecognizer_, nullptr);
    EXPECT_NE(touchContext.actuator->SequencedRecognizer_, nullptr);
    EXPECT_TRUE(touchContext.actuator->SequencedRecognizer_->isEventHandoverNeeded_);
    EXPECT_EQ(touchContext.actuator->dragDropInitiatingHandler_->GetDragDropInitiatingStatus(),
        DragDropInitiatingStatus::READY);
}

/**
 * @tc.name: DragDropEventActuatorOnCollectTouchTargetStylusCoverage001
 * @tc.desc: Cover OnCollectTouchTarget stylus path and verify the pan recognizer mouse distance.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropEventTestCoverageNg, DragDropEventActuatorOnCollectTouchTargetStylusCoverage001, TestSize.Level1)
{
    auto context = CreateDragDropContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
    auto touchRestrict = CreateTouchRestrict(SourceType::TOUCH);
    touchRestrict.touchEvent.isStylusMouseMode = true;
    TouchTestResult result;
    CollectTouchTarget(context, touchRestrict, result);
    EXPECT_EQ(result.size(), 2UL);
    ASSERT_NE(context.actuator->panRecognizer_, nullptr);
    auto expectedDistance = Dimension(10.0, DimensionUnit::VP).ConvertToPx();
    EXPECT_DOUBLE_EQ(context.actuator->panRecognizer_->mouseDistance_, expectedDistance);
}

/**
 * @tc.name: DragDropEventActuatorLongPressAndPendingCoverage001
 * @tc.desc: Cover long-press transitions, preview cancel cleanup and pending gather-node handling.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropEventTestCoverageNg, DragDropEventActuatorLongPressAndPendingCoverage001, TestSize.Level1)
{
    auto context = CreateDragDropContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
    TouchTestResult result;
    CollectTouchTarget(context, CreateTouchRestrict(SourceType::TOUCH), result);
    ASSERT_NE(context.actuator->dragDropInitiatingHandler_, nullptr);
    auto handler = context.actuator->dragDropInitiatingHandler_;
    auto machine = handler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    EXPECT_EQ(handler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::READY);

    GestureEvent gestureEvent;
    (*(context.actuator->longPressRecognizer_->onAction_))(gestureEvent);
    EXPECT_EQ(handler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::PRESS);

    (*(context.actuator->previewLongPressRecognizer_->onAction_))(gestureEvent);
    EXPECT_EQ(handler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::LIFTING);

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    MountPixelMapAndEventColumnNodes(overlayManager);
    (*(context.actuator->previewLongPressRecognizer_->onActionCancel_))(gestureEvent);
    EXPECT_FALSE(overlayManager->hasPixelMap_);
    EXPECT_EQ(overlayManager->pixmapColumnNodeWeak_.Upgrade(), nullptr);
    EXPECT_EQ(overlayManager->eventColumnNodeWeak_.Upgrade(), nullptr);

    machine->RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::READY));
    EXPECT_EQ(handler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::READY);
    MountGatherNode(overlayManager);
    auto& params = machine->GetDragDropInitiatingParams();
    params.hasGatherNode = true;
    (*(context.actuator->longPressRecognizer_->onPending_))(RefereeState::FAIL);
    EXPECT_TRUE(overlayManager->hasGatherNode_);

    (*(context.actuator->longPressRecognizer_->onPending_))(RefereeState::SUCCEED_BLOCKED);
    EXPECT_FALSE(overlayManager->hasGatherNode_);
    EXPECT_EQ(overlayManager->gatherNodeWeak_.Upgrade(), nullptr);
}

/**
 * @tc.name: DragDropEventActuatorPanCallbacksAndSequenceCoverage001
 * @tc.desc: Cover pan callback branches, sequence cancel and handler-null action-end reset.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropEventTestCoverageNg, DragDropEventActuatorPanCallbacksAndSequenceCoverage001, TestSize.Level1)
{
    auto context = CreateDragDropContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
    TouchTestResult result;
    CollectTouchTarget(context, CreateTouchRestrict(SourceType::TOUCH), result);
    ASSERT_NE(context.actuator->dragDropInitiatingHandler_, nullptr);
    EXPECT_EQ(context.actuator->dragDropInitiatingHandler_->GetDragDropInitiatingStatus(),
        DragDropInitiatingStatus::READY);

    GestureEvent gestureEvent;
    gestureEvent.SetPassThrough(false);
    auto panActionStart = *(context.actuator->panRecognizer_->onActionStart_);
    ASSERT_NE(panActionStart, nullptr);
    panActionStart(gestureEvent);
    EXPECT_EQ(context.actuator->dragDropInitiatingHandler_->GetDragDropInitiatingStatus(),
        DragDropInitiatingStatus::READY);

    gestureEvent.SetPassThrough(true);
    panActionStart = *(context.actuator->panRecognizer_->onActionStart_);
    ASSERT_NE(panActionStart, nullptr);
    panActionStart(gestureEvent);
    EXPECT_EQ(context.actuator->dragDropInitiatingHandler_->GetDragDropInitiatingStatus(),
        DragDropInitiatingStatus::READY);

    auto panActionUpdate = *(context.actuator->panRecognizer_->onActionUpdate_);
    ASSERT_NE(panActionUpdate, nullptr);
    panActionUpdate(gestureEvent);
    EXPECT_EQ(context.actuator->dragDropInitiatingHandler_->GetDragDropInitiatingStatus(),
        DragDropInitiatingStatus::READY);

    auto sequenceOnCancel = context.actuator->GetSequenceOnActionCancel();
    ASSERT_NE(sequenceOnCancel, nullptr);
    sequenceOnCancel(gestureEvent);
    EXPECT_EQ(context.actuator->dragDropInitiatingHandler_->GetDragDropInitiatingStatus(),
        DragDropInitiatingStatus::IDLE);

    result.clear();
    CollectTouchTarget(context, CreateTouchRestrict(SourceType::TOUCH), result);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    MountGatherNode(overlayManager);
    context.actuator->dragDropInitiatingHandler_->initiatingFlow_->GetDragDropInitiatingParams().hasGatherNode = true;
    ASSERT_NE(context.actuator->panRecognizer_->onReject_, nullptr);
    (*(context.actuator->panRecognizer_->onReject_))();
    EXPECT_FALSE(overlayManager->hasGatherNode_);
    EXPECT_EQ(overlayManager->gatherNodeWeak_.Upgrade(), nullptr);

    result.clear();
    CollectTouchTarget(context, CreateTouchRestrict(SourceType::TOUCH), result);
    MountPixelMapAndEventColumnNodes(overlayManager);
    auto panActionEnd = *(context.actuator->panRecognizer_->onActionEnd_);
    ASSERT_NE(panActionEnd, nullptr);
    context.actuator->dragDropInitiatingHandler_ = nullptr;
    panActionEnd(gestureEvent);
    EXPECT_FALSE(overlayManager->hasPixelMap_);
    EXPECT_EQ(overlayManager->pixmapColumnNodeWeak_.Upgrade(), nullptr);
}

/**
 * @tc.name: DragDropEventActuatorCopyEventAndHelperCoverage001
 * @tc.desc: Cover CopyEvent and helper accessors for shared handler state, text-drag guard and reset path.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropEventTestCoverageNg, DragDropEventActuatorCopyEventAndHelperCoverage001, TestSize.Level1)
{
    auto sourceContext = CreateDragDropContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
    auto targetContext = CreateDragDropContext(V2::TEXT_ETS_TAG, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(sourceContext.actuator, nullptr);
    ASSERT_NE(targetContext.actuator, nullptr);

    auto sourceHandler = sourceContext.actuator->dragDropInitiatingHandler_;
    ASSERT_NE(sourceHandler, nullptr);
    auto sourceMachine = sourceHandler->initiatingFlow_;
    ASSERT_NE(sourceMachine, nullptr);
    auto& sourceParams = sourceMachine->GetDragDropInitiatingParams();
    sourceParams.preScaleValue = TEST_PRE_SCALE;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    sourceParams.preScaledPixelMap = pixelMap;
    sourceParams.isNeedGather = true;

    targetContext.actuator->CopyEvent(sourceContext.actuator);
    EXPECT_EQ(targetContext.actuator->gestureEventHub_.Upgrade(), sourceContext.gestureEventHub);
    EXPECT_EQ(targetContext.actuator->dragDropInitiatingHandler_, sourceHandler);
    EXPECT_EQ(targetContext.actuator->GetFrameNode(), sourceContext.frameNode);
    EXPECT_NE(targetContext.actuator->panRecognizer_, nullptr);
    EXPECT_NE(targetContext.actuator->longPressRecognizer_, nullptr);
    EXPECT_NE(targetContext.actuator->previewLongPressRecognizer_, nullptr);

    float preScale = 0.0f;
    EXPECT_EQ(targetContext.actuator->GetPreScaledPixelMapForDragThroughTouch(preScale), pixelMap);
    EXPECT_FLOAT_EQ(preScale, TEST_PRE_SCALE);
    EXPECT_TRUE(targetContext.actuator->IsNeedGather());

    sourceContext.gestureEventHub->textDraggable_ = true;
    preScale = 0.0f;
    EXPECT_EQ(targetContext.actuator->GetPreScaledPixelMapForDragThroughTouch(preScale), nullptr);

    sourceContext.gestureEventHub->textDraggable_ = false;
    targetContext.actuator->ResetPreScaledPixelMapForDragThroughTouch();
    EXPECT_EQ(sourceParams.preScaledPixelMap, nullptr);
    EXPECT_FLOAT_EQ(sourceParams.preScaleValue, 1.0f);

    auto noHandlerContext = CreateDragDropContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
    noHandlerContext.actuator->dragDropInitiatingHandler_ = nullptr;
    targetContext.actuator->dragDropInitiatingHandler_ = nullptr;
    targetContext.actuator->CopyEvent(noHandlerContext.actuator);
    EXPECT_EQ(targetContext.actuator->dragDropInitiatingHandler_, nullptr);
}

/**
 * @tc.name: DragDropEventActuatorHandleTouchEventAndNotifyCoverage001
 * @tc.desc: Cover HandleTouchEvent and notify helpers for drag-start, drag-end, menu-show and window-transition.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropEventTestCoverageNg, DragDropEventActuatorHandleTouchEventAndNotifyCoverage001, TestSize.Level1)
{
    auto context = CreateDragDropContext(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
    TouchTestResult result;
    CollectTouchTarget(context, CreateTouchRestrict(SourceType::TOUCH, TEST_TOUCH_ID), result);
    ASSERT_NE(context.actuator->dragDropInitiatingHandler_, nullptr);
    auto handler = context.actuator->dragDropInitiatingHandler_;
    auto machine = handler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    EXPECT_EQ(handler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::READY);
    EXPECT_EQ(machine->GetDragDropInitiatingParams().idleFingerId, TEST_TOUCH_ID);

    TouchEventInfo emptyTouchInfo("onTouch");
    context.actuator->HandleTouchEvent(emptyTouchInfo, false);
    EXPECT_EQ(handler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::READY);

    auto upTouchInfo = CreateTouchEventInfo(TEST_TOUCH_ID, TouchType::UP);
    context.actuator->HandleTouchEvent(upTouchInfo, false);
    EXPECT_EQ(handler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::IDLE);

    result.clear();
    CollectTouchTarget(context, CreateTouchRestrict(SourceType::TOUCH, TEST_TOUCH_ID), result);
    context.actuator->NotifyDragStart();
    EXPECT_EQ(handler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::MOVING);
    context.actuator->NotifyDragEnd();
    EXPECT_EQ(handler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::IDLE);

    result.clear();
    CollectTouchTarget(context, CreateTouchRestrict(SourceType::TOUCH, TEST_TOUCH_ID), result);
    GestureEvent gestureEvent;
    (*(context.actuator->longPressRecognizer_->onAction_))(gestureEvent);
    EXPECT_EQ(handler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::PRESS);

    context.actuator->NotifyMenuShow(true);
    EXPECT_EQ(handler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::LIFTING);

    context.actuator->NotifyTransDragWindowToFwk();
    EXPECT_EQ(handler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::IDLE);
}
} // namespace OHOS::Ace::NG
