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

#include "test/unittest/core/manager/drag_drop/drag_drop_initiating_test_ng.h"
#define private public
#define protected public

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_handler.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_base.h"
#include "core/event/touch_event.h"
#include "core/gestures/drag_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_OPACITY = 0.95f;
constexpr float DEFAULT_SCALE = 2.0f;
}

void DragDropInitiatingStateBaseTestNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragDropInitiatingStateBaseTestNG::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

struct HandleTextDragStartTestCase {
    SourceType type = SourceType::MOUSE;
    bool isSelected = false;
    bool textDraggable = false;
    bool expectResult = false;
};

const std::vector<HandleTextDragStartTestCase> HANDLE_TEXT_DRAG_START_TEST_CASES = {
    { SourceType::TOUCH, false, false, false },
    { SourceType::TOUCH, true, false, true },
    { SourceType::TOUCH, false, false, false },
    { SourceType::TOUCH, false, true, false },
    { SourceType::MOUSE, false, true, false },
    { SourceType::MOUSE, true, true, true }
};

RefPtr<DragDropEventActuator> CreateDragDropEventActuator()
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    CHECK_NULL_RETURN(gestureEventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SEARCH_Field_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dragDropEventActuator =
        AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
    CHECK_NULL_RETURN(dragDropEventActuator, nullptr);
    auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
    CHECK_NULL_RETURN(handler, nullptr);
    auto machine = handler->initiatingFlow_;
    CHECK_NULL_RETURN(machine, nullptr);
    machine->InitializeState();
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);
    return dragDropEventActuator;
}

RefPtr<DragDropInitiatingStateBase> GetDragDropState(RefPtr<DragDropEventActuator> actuator,
    DragDropInitiatingStatus state)
{
    CHECK_NULL_RETURN(actuator, nullptr);
    auto handler = actuator->dragDropInitiatingHandler_;
    CHECK_NULL_RETURN(handler, nullptr);
    auto machine = handler->initiatingFlow_;
    CHECK_NULL_RETURN(machine, nullptr);
    return machine->dragDropInitiatingState_[static_cast<int32_t>(state)];
}

/**
 * @tc.name: DragDropInitiatingStateBaseTestNG001
 * @tc.desc: Test PrepareFinalPixelMapForDragThroughTouch function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateBaseTestNG, DragDropInitiatingStateBaseTestNG001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragDropEventActuator.
     */
    auto actuator = CreateDragDropEventActuator();
    ASSERT_NE(actuator, nullptr);

    /**
     * @tc.steps: step2. get DragDropInitiatingStateBase.
     */
    auto state = GetDragDropState(actuator, DragDropInitiatingStatus::IDLE);
    ASSERT_NE(state, nullptr);
    auto stateIdle = AceType::DynamicCast<DragDropInitiatingStateBase>(state);
    ASSERT_NE(stateIdle, nullptr);
    auto machine = stateIdle->GetStateMachine();
    ASSERT_NE(machine, nullptr);

    /**
     * @tc.steps: step3. trigger PrepareFinalPixelMapForDragThroughTouch.
     */
    stateIdle->PrepareFinalPixelMapForDragThroughTouch(nullptr, false);
    auto params = machine->GetDragDropInitiatingParams();
    EXPECT_FALSE(params.isThumbnailCallbackTriggered);

    stateIdle->PrepareFinalPixelMapForDragThroughTouch(nullptr, true);
    params = machine->GetDragDropInitiatingParams();
    EXPECT_TRUE(params.isThumbnailCallbackTriggered);
}

/**
 * @tc.name: DragDropInitiatingStateBaseTestNG002
 * @tc.desc: Test HidePixelMap function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateBaseTestNG, DragDropInitiatingStateBaseTestNG002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragDropEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SEARCH_Field_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dragDropEventActuator =
        AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
    ASSERT_NE(dragDropEventActuator, nullptr);
    auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
    ASSERT_NE(handler, nullptr);
    auto machine = handler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    machine->InitializeState();
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);
    /**
     * @tc.steps: step2. get DragDropInitiatingStateBase.
     */
    auto state = GetDragDropState(dragDropEventActuator, DragDropInitiatingStatus::IDLE);
    ASSERT_NE(state, nullptr);
    auto stateIdle = AceType::DynamicCast<DragDropInitiatingStateBase>(state);
    ASSERT_NE(stateIdle, nullptr);

    /**
     * @tc.steps: step3. set multi drag and default animation.
     */
    auto& params = machine->GetDragDropInitiatingParams();
    params.hasGatherNode = true;
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    dragPreviewOption.defaultAnimationBeforeLifting = true;
    frameNode->SetDragPreviewOptions(dragPreviewOption);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);

    /**
     * @tc.steps: step4. trigger HidePixelMap.
     */
    stateIdle->HidePixelMap(false, 0, 0, false);
    layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto type = layoutProperty->GetVisibilityValue(VisibleType::INVISIBLE);
    EXPECT_EQ(type, VisibleType::VISIBLE);
}

/**
 * @tc.name: DragDropInitiatingStateBaseTestNG003
 * @tc.desc: Test UpdateDragPreviewOptionFromModifier function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateBaseTestNG, DragDropInitiatingStateBaseTestNG003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragDropEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SEARCH_Field_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dragDropEventActuator =
        AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
    ASSERT_NE(dragDropEventActuator, nullptr);
    auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
    ASSERT_NE(handler, nullptr);
    auto machine = handler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    machine->InitializeState();
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);

    /**
     * @tc.steps: step2. get DragDropInitiatingStateBase.
     */
    auto state = GetDragDropState(dragDropEventActuator, DragDropInitiatingStatus::IDLE);
    ASSERT_NE(state, nullptr);
    auto stateIdle = AceType::DynamicCast<DragDropInitiatingStateBase>(state);
    ASSERT_NE(stateIdle, nullptr);

    /**
     * @tc.steps: step3. set onApply.
     */
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    dragPreviewOption.onApply = [](WeakPtr<NG::FrameNode> frameNodes) {
    };
    frameNode->SetDragPreviewOptions(dragPreviewOption);

    /**
     * @tc.steps: step4. trigger UpdateDragPreviewOptionFromModifier.
     */
    stateIdle->UpdateDragPreviewOptionFromModifier();
    dragPreviewOption = frameNode->GetDragPreviewOption();
    EXPECT_EQ(dragPreviewOption.options.opacity, DEFAULT_OPACITY);
}

/**
 * @tc.name: DragDropInitiatingStateBaseTestNG004
 * @tc.desc: Test CheckStatusForPanActionBegin function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateBaseTestNG, DragDropInitiatingStateBaseTestNG004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragDropEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SEARCH_Field_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dragDropEventActuator =
        AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
    ASSERT_NE(dragDropEventActuator, nullptr);
    auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
    ASSERT_NE(handler, nullptr);
    auto machine = handler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    machine->InitializeState();
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);

    /**
     * @tc.steps: step2. get DragDropInitiatingStateBase.
     */
    auto state = GetDragDropState(dragDropEventActuator, DragDropInitiatingStatus::IDLE);
    ASSERT_NE(state, nullptr);
    auto stateIdle = AceType::DynamicCast<DragDropInitiatingStateBase>(state);
    ASSERT_NE(stateIdle, nullptr);

    /**
     * @tc.steps: step3. update IsDragNodeNeedClean and draggable.
     */
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->SetIsDragNodeNeedClean(false);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->textDraggable_ = true;
    gestureHub->isTextDraggable_ = false;

    /**
     * @tc.steps: step4. trigger CheckStatusForPanActionBegin.
     */
    GestureEvent info;
    auto result = stateIdle->CheckStatusForPanActionBegin(frameNode, info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DragDropInitiatingStateBaseTestNG005
 * @tc.desc: Test SetTextPixelMap function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateBaseTestNG, DragDropInitiatingStateBaseTestNG005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragDropEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SEARCH_Field_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dragDropEventActuator =
        AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
    ASSERT_NE(dragDropEventActuator, nullptr);
    auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
    ASSERT_NE(handler, nullptr);
    auto machine = handler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    machine->InitializeState();
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);

    /**
     * @tc.steps: step2. get DragDropInitiatingStateBase.
     */
    auto state = GetDragDropState(dragDropEventActuator, DragDropInitiatingStatus::IDLE);
    ASSERT_NE(state, nullptr);
    auto stateIdle = AceType::DynamicCast<DragDropInitiatingStateBase>(state);
    ASSERT_NE(stateIdle, nullptr);
    auto& params = machine->GetDragDropInitiatingParams();

    /**
     * @tc.steps: step3. trigger SetTextPixelMap.
     */
    auto textPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ASSERT_NE(textPixelMap, nullptr);
    params.preScaledPixelMap = textPixelMap;
    stateIdle->SetTextPixelMap();
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_NE(gestureHub->pixelMap_, textPixelMap);
    EXPECT_NE(params.preScaledPixelMap, nullptr);

    stateIdle->SetTextPixelMap();
    EXPECT_NE(gestureHub->pixelMap_, textPixelMap);
}

/**
 * @tc.name: DragDropInitiatingStateBaseTestNG006
 * @tc.desc: Test HideTextAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateBaseTestNG, DragDropInitiatingStateBaseTestNG006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragDropEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SEARCH_Field_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dragDropEventActuator =
        AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
    ASSERT_NE(dragDropEventActuator, nullptr);
    auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
    ASSERT_NE(handler, nullptr);
    auto machine = handler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    machine->InitializeState();
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);

    /**
     * @tc.steps: step2. get DragDropInitiatingStateBase.
     */
    auto state = GetDragDropState(dragDropEventActuator, DragDropInitiatingStatus::IDLE);
    ASSERT_NE(state, nullptr);
    auto stateIdle = AceType::DynamicCast<DragDropInitiatingStateBase>(state);
    ASSERT_NE(stateIdle, nullptr);
    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    context->UpdateTransformScale(VectorF(DEFAULT_SCALE, DEFAULT_SCALE));

    /**
     * @tc.steps: step3. trigger HideTextAnimation.
     */
    stateIdle->HideTextAnimation(false, 0.0f, 0.0f);
    auto scale = context->GetTransformScaleValue({ 1.0f, 1.0f });
    EXPECT_EQ(scale.x, DEFAULT_SCALE);
    EXPECT_EQ(scale.y, DEFAULT_SCALE);

    frameNode->draggable_ = true;
    stateIdle->HideTextAnimation(false, 0.0f, 0.0f);
    scale = context->GetTransformScaleValue({ 1.0f, 1.0f });
    EXPECT_EQ(scale.x, DEFAULT_SCALE);
    EXPECT_EQ(scale.y, DEFAULT_SCALE);

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    auto dragNode = AceType::MakeRefPtr<FrameNode>(V2::SEARCH_Field_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(dragNode, nullptr);
    manager->pixmapColumnNodeWeak_ = dragNode;
    stateIdle->HideTextAnimation(false, 0.0f, 0.0f);
    scale = context->GetTransformScaleValue({ 1.0f, 1.0f });
    EXPECT_EQ(scale.x, 2.0f);
    EXPECT_EQ(scale.y, 2.0f);
}

/**
 * @tc.name: DragDropInitiatingStateBaseTestNG007
 * @tc.desc: Test HandleTextDragCallback function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateBaseTestNG, DragDropInitiatingStateBaseTestNG007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragDropEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SEARCH_Field_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dragDropEventActuator =
        AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
    ASSERT_NE(dragDropEventActuator, nullptr);
    auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
    ASSERT_NE(handler, nullptr);
    auto machine = handler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    machine->InitializeState();
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);

    /**
     * @tc.steps: step2. get DragDropInitiatingStateBase.
     */
    auto state = GetDragDropState(dragDropEventActuator, DragDropInitiatingStatus::IDLE);
    ASSERT_NE(state, nullptr);
    auto stateIdle = AceType::DynamicCast<DragDropInitiatingStateBase>(state);
    ASSERT_NE(stateIdle, nullptr);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->pixelMap_ = AceType::MakeRefPtr<MockPixelMap>();
    gestureHub->isTextDraggable_ = false;

    /**
     * @tc.steps: step3. trigger HandleTextDragCallback.
     */
    stateIdle->HandleTextDragCallback();
    EXPECT_EQ(gestureHub->pixelMap_, nullptr);
}

/**
 * @tc.name: DragDropInitiatingStateBaseTestNG008
 * @tc.desc: Test HandleTextDragStart function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateBaseTestNG, DragDropInitiatingStateBaseTestNG008, TestSize.Level1)
{
    for (const auto& testCase : HANDLE_TEXT_DRAG_START_TEST_CASES) {
        /**
         * @tc.steps: step1. create DragDropEventActuator.
         */
        auto eventHub = AceType::MakeRefPtr<EventHub>();
        ASSERT_NE(eventHub, nullptr);
        auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
        ASSERT_NE(gestureEventHub, nullptr);
        auto frameNode =
            AceType::MakeRefPtr<FrameNode>(V2::SEARCH_Field_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        ASSERT_NE(frameNode, nullptr);
        eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
        auto dragDropEventActuator =
            AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
        ASSERT_NE(dragDropEventActuator, nullptr);
        auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
        ASSERT_NE(handler, nullptr);
        auto machine = handler->initiatingFlow_;
        ASSERT_NE(machine, nullptr);
        machine->InitializeState();
        machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);
 
        /**
         * @tc.steps: step2. get DragDropInitiatingStateBase.
         */
        auto state = GetDragDropState(dragDropEventActuator, DragDropInitiatingStatus::IDLE);
        ASSERT_NE(state, nullptr);
        auto stateIdle = AceType::DynamicCast<DragDropInitiatingStateBase>(state);
        ASSERT_NE(stateIdle, nullptr);
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        ASSERT_NE(gestureHub, nullptr);
        gestureHub->isTextDraggable_ = true;
        auto pattern = frameNode->GetPattern<TextBase>();
        ASSERT_NE(pattern, nullptr);
        GestureEvent info;
        info.SetSourceDevice(testCase.type);
        if (testCase.isSelected) {
            pattern->textSelector_.Update(3, 4);
        }
        gestureHub->textDraggable_ = testCase.textDraggable;

        /**
         * @tc.steps: step3. get DragDropInitiatingStateBase.
         */
        stateIdle->HandleTextDragStart(frameNode, info);
        EXPECT_EQ(gestureHub->isTextDraggable_, testCase.expectResult);
    }
}
} // namespace OHOS::Ace::NG