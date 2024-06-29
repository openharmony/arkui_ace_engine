/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: DragEventActuatorRestartDragTaskTest001
 * @tc.desc: Test RestartDragTask function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorRestartDragTaskTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Execute RestartDragTask when actionStart_ is null.
     */
    auto info = GestureEvent();
    dragEventActuator->RestartDragTask(info);
    ASSERT_EQ(dragEventActuator->actionStart_, nullptr);

    /**
     * @tc.steps: step3. Execute RestartDragTask when actionStart_ is not null.
     */
    
    int unknownPropertyValue = UNKNOWN;
    dragEventActuator->actionStart_ = [&unknownPropertyValue](GestureEvent& gestureInfo) mutable {
        unknownPropertyValue++;
    };
    dragEventActuator->RestartDragTask(info);
    ASSERT_NE(unknownPropertyValue, UNKNOWN);
}

/**
 * @tc.name: DragEventActuatorDragingStatusTest001
 * @tc.desc: Test IsGlobalStatusSuitableForDragging and IsCurrentCodeStatusSuitableForDragging function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorDragingStatusTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Execute IsGlobalStatusSuitableForDragging.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->ResetDragging(DragDropMgrState::DRAGGING);
    auto globalStatus = dragEventActuator->IsGlobalStatusSuitableForDragging();
    ASSERT_EQ(globalStatus, false);

    /**
     * @tc.steps: step3. Execute IsCurrentNodeStatusSuitableForDragging.
     */
    TouchRestrict dragTouchRestrict = { TouchRestrict::CLICK };
    dragTouchRestrict.inputEventType = InputEventType::AXIS;
    auto nodeStatus = dragEventActuator->IsCurrentNodeStatusSuitableForDragging(framenode, dragTouchRestrict);
    ASSERT_EQ(nodeStatus, false);
}

/**
 * @tc.name: DragEventActuatorSetDragDampStartPointInfoTest001
 * @tc.desc: Test SetDragDampStartPointInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorSetDragDampStartPointInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke SetDragDampStartPointInfo.
     * @tc.expected: cover SetDragDampStartPointInfo.
     */
    GestureEvent info = GestureEvent();
    dragEventActuator->SetDragDampStartPointInfo(info.GetGlobalPoint(), info.GetPointerId());
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    ASSERT_EQ(dragDropManager->currentPointerId_, info.GetPointerId());
}

/**
 * @tc.name: DragEventActuatorHandleDragDampingMoveTest001
 * @tc.desc: Test HandleDragDampingMove function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorHandleDragDampingMoveTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke DragDampingMove with DragDropMgrState::IDLE and same Pointer.
     * @tc.expected: cover DragDampingMove.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    TouchEventInfo info(TOUCH_EVENT_INFO_TYPE);
    auto point = Point(info.GetTouches().front().GetGlobalLocation().GetX(),
                       info.GetTouches().front().GetGlobalLocation().GetY());
    dragDropManager->SetDraggingPointer(info.GetTouches().front().GetFingerId());
    dragDropManager->ResetDragging(DragDropMgrState::IDLE);
    dragEventActuator->HandleDragDampingMove(point, info.GetTouches().front().GetFingerId());
    ASSERT_FALSE(dragDropManager->IsAboutToPreview());
    ASSERT_FALSE(dragDropManager->IsDragging());
    EXPECT_FALSE(!dragDropManager->IsSameDraggingPointer(info.GetTouches().front().GetFingerId()));

    /**
     * @tc.steps: step3. Invoke DragDampingMove with DragDropMgrState::DRAGGING and same Pointer.
     * @tc.expected: cover DragDampingMove.
     */
    dragDropManager->ResetDragging(DragDropMgrState::DRAGGING);
    dragEventActuator->HandleDragDampingMove(point, info.GetTouches().front().GetFingerId());
    EXPECT_FALSE(dragDropManager->IsAboutToPreview());
    EXPECT_TRUE(dragDropManager->IsDragging());
    EXPECT_FALSE(!dragDropManager->IsSameDraggingPointer(info.GetTouches().front().GetFingerId()));

    /**
     * @tc.steps: step4. Invoke DragDampingMove with DragDropMgrState::ABOUT_TO_PREVIEW and same Pointer.
     * @tc.expected: cover DragDampingMove.
     */
    dragDropManager->ResetDragging(DragDropMgrState::ABOUT_TO_PREVIEW);
    dragEventActuator->HandleDragDampingMove(point, info.GetTouches().front().GetFingerId());
    EXPECT_TRUE(dragDropManager->IsAboutToPreview());
    EXPECT_FALSE(dragDropManager->IsDragging());
    EXPECT_FALSE(!dragDropManager->IsSameDraggingPointer(info.GetTouches().front().GetFingerId()));

    /**
     * @tc.steps: step5. Invoke DragDampingMove.
     * @tc.expected: cover DragDampingMove.
     */
    dragDropManager->ResetDragging(DragDropMgrState::IDLE);
    point.SetX(10.0);
    point.SetY(10.0);
    dragEventActuator->HandleDragDampingMove(point, info.GetTouches().front().GetFingerId());
    auto startPoint = dragDropManager->GetDragDampStartPoint();
    auto delta = Point(point.GetX(), point.GetY()) - startPoint;
    auto distance = SystemProperties::GetDragStartPanDistanceThreshold();
    EXPECT_TRUE(delta.GetDistance() > Dimension(distance, DimensionUnit::VP).ConvertToPx());

    point.SetX(1.0);
    point.SetY(1.0);
    dragEventActuator->HandleDragDampingMove(point, info.GetTouches().front().GetFingerId());
    startPoint = dragDropManager->GetDragDampStartPoint();
    delta = Point(point.GetX(), point.GetY()) - startPoint;
    distance = SystemProperties::GetDragStartPanDistanceThreshold();
    EXPECT_TRUE(delta.GetDistance() < Dimension(distance, DimensionUnit::VP).ConvertToPx());
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest001
 * @tc.desc: Test UpdatePreviewAttr function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke UpdatePreviewAttr.
     * @tc.expected: cover UpdatePreviewAttr with TextDraggable true.
     */
    auto frameTag = frameNode->GetTag();
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureHub, nullptr);
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imageNode, nullptr);
    gestureHub->SetTextDraggable(true);
    dragEventActuator->UpdatePreviewAttr(frameNode, imageNode);
    EXPECT_TRUE(gestureHub->IsTextCategoryComponent(frameTag));
    EXPECT_TRUE(gestureHub->GetTextDraggable());
}

/**
 * @tc.name: DragEventActuatorSetPixelMapTest001
 * @tc.desc: Test SetPixelMap function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorSetPixelMapTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke SetHasPixelMap.
     * @tc.desc: GetHasPixelMap true.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto manager = pipelineContext->GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    manager->SetHasPixelMap(true);
    dragEventActuator->SetPixelMap(dragEventActuator);
    ASSERT_TRUE(manager->GetHasPixelMap());
}

/**
 * @tc.name: DragEventActuatorBrulStyleToEffectionTest001
 * @tc.desc: Test BrulStyleToEffection function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorBrulStyleToEffectionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke BrulStyleToEffection.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
    auto imageContext = imageNode->GetRenderContext();
    ASSERT_NE(imageContext, nullptr);
    auto blurstyletmp = imageContext->GetBackBlurStyle();
    blurstyletmp->colorMode = ThemeColorMode::DARK;
    dragEventActuator->BrulStyleToEffection(blurstyletmp);
    ASSERT_NE(blurstyletmp->colorMode, ThemeColorMode::SYSTEM);
}

/**
 * @tc.name: DragEventActuatorHidePixelMapTest001
 * @tc.desc: Test HidePixelMap function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorHidePixelMapTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke HidePixelMap.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto manager = pipelineContext->GetOverlayManager();
    EXPECT_NE(manager, nullptr);
    dragEventActuator->HidePixelMap(true, 0, 0, false);
    EXPECT_FALSE(manager->hasPixelMap_);
}

/**
 * @tc.name: DragEventActuatorSetTextPixelMapTest001
 * @tc.desc: Test SetTextPixelMap function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorSetTextPixelMapTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke HidePixelMap.
     */
    dragEventActuator->SetTextPixelMap(gestureEventHub);
    EXPECT_EQ(dragEventActuator->textPixelMap_, nullptr);
}

/**
 * @tc.name: DragEventActuatorSetImageNodeInitAttrTest001
 * @tc.desc: Test SetImageNodeInitAttr function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorSetImageNodeInitAttrTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke SetImageNodeInitAttr.
     * @tc.desc: defaultAnimationBeforeLifting = true, layoutProperty != nullptr.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imageNode, nullptr);
    auto imageContext = imageNode->GetRenderContext();
    EXPECT_NE(imageContext, nullptr);
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    dragPreviewOption.defaultAnimationBeforeLifting = true;
    auto layoutProperty = frameNode->GetLayoutProperty();
    auto shadow = Shadow::CreateShadow(ShadowStyle::None);

    dragEventActuator->SetImageNodeInitAttr(frameNode, imageNode);
    EXPECT_TRUE(dragPreviewOption.defaultAnimationBeforeLifting);
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(dragPreviewOption.options.shadow.has_value());

    /**
     * @tc.steps: step3. Invoke SetImageNodeInitAttr.
     * @tc.desc: defaultAnimationBeforeLifting = true, layoutProperty = nullptr.
     */
    frameNode->layoutProperty_ = nullptr;
    dragEventActuator->SetImageNodeInitAttr(frameNode, imageNode);
    EXPECT_EQ(frameNode->GetLayoutProperty(), nullptr);

    /**
     * @tc.steps: step3. Invoke SetImageNodeInitAttr.
     * @tc.desc: defaultAnimationBeforeLifting = false, layoutProperty = nullptr.
     */
    dragPreviewOption.defaultAnimationBeforeLifting = false;
    dragEventActuator->SetImageNodeInitAttr(frameNode, imageNode);
    EXPECT_FALSE(dragPreviewOption.defaultAnimationBeforeLifting);

    /**
     * @tc.steps: step3. Invoke SetImageNodeInitAttr.
     * @tc.desc: dragPreviewOption.options.shadow.has_value() = true.
     */
    dragPreviewOption.options.shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultXS);
    dragEventActuator->SetImageNodeInitAttr(frameNode, imageNode);
    EXPECT_TRUE(dragPreviewOption.options.shadow.has_value());
}

/**
 * @tc.name: DragEventActuatorSetImageNodeFinishAttrTest001
 * @tc.desc: Test SetImageNodeFinishAttr function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorSetImageNodeFinishAttrTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke SetImageNodeFinishAttr.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imageNode, nullptr);
    auto imageContext = imageNode->GetRenderContext();
    EXPECT_NE(imageContext, nullptr);
    auto dragPreviewOption = frameNode->GetDragPreviewOption();

    dragEventActuator->SetImageNodeFinishAttr(frameNode, imageNode);
    EXPECT_FALSE(dragPreviewOption.options.shadow->GetIsFilled());
    EXPECT_FALSE(dragPreviewOption.options.shadow.has_value());

    /**
     * @tc.steps: step3. Invoke SetImageNodeFinishAttr.
     */
    dragPreviewOption.options.shadow->isFilled_ = true;
    dragEventActuator->SetImageNodeFinishAttr(frameNode, imageNode);
    EXPECT_TRUE(dragPreviewOption.options.shadow->GetIsFilled());
    EXPECT_FALSE(dragPreviewOption.options.shadow.has_value());

    /**
     * @tc.steps: step4. Invoke SetImageNodeFinishAttr.
     */
    dragPreviewOption.options.shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultXS);
    dragPreviewOption.options.shadow->isFilled_ = false;
    dragEventActuator->SetImageNodeFinishAttr(frameNode, imageNode);
    EXPECT_FALSE(dragPreviewOption.options.shadow->GetIsFilled());
    EXPECT_TRUE(dragPreviewOption.options.shadow.has_value());

    /**
     * @tc.steps: step5. Invoke SetImageNodeFinishAttr.
     */
    dragPreviewOption.options.shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultXS);
    dragPreviewOption.options.shadow->isFilled_ = true;
    dragEventActuator->SetImageNodeFinishAttr(frameNode, imageNode);
    EXPECT_TRUE(dragPreviewOption.options.shadow->GetIsFilled());
    EXPECT_TRUE(dragPreviewOption.options.shadow.has_value());
}

/**
 * @tc.name: DragEventActuatorGetOrCreateGatherNodeTest001
 * @tc.desc: Test GetOrCreateGatherNode function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorGetOrCreateGatherNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke GetOrCreateGatherNode with dragEventActuator->IsNeedGather() false.
     */
    std::vector<GatherNodeChildInfo> gatherNodeChildInfo(2);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto overlayManager = pipeline->GetOverlayManager();
    EXPECT_NE(overlayManager, nullptr);
    auto gatherNode = dragEventActuator->GetOrCreateGatherNode(overlayManager, dragEventActuator, gatherNodeChildInfo);
    EXPECT_EQ(gatherNode, nullptr);
}

/**
 * @tc.name: DragEventActuatorResetNodeTest001
 * @tc.desc: Test ResetNode function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorResetNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke ResetNode.
     */
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    dragPreviewOption.defaultAnimationBeforeLifting = false;
    dragEventActuator->ResetNode(frameNode);
    dragPreviewOption = frameNode->GetDragPreviewOption();
    EXPECT_FALSE(dragPreviewOption.defaultAnimationBeforeLifting);

    /**
     * @tc.steps: step3. Invoke ResetNode.
     */
    dragPreviewOption.defaultAnimationBeforeLifting = true;
    frameNode->layoutProperty_ = nullptr;
    dragEventActuator->ResetNode(frameNode);
    EXPECT_EQ(frameNode->GetLayoutProperty(), nullptr);
}

/**
 * @tc.name: DragEventActuatorHandleTouchUpEventTest001
 * @tc.desc: Test HandleTouchUpEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke HandleTouchUpEvent.
     */
    dragEventActuator->HandleTouchUpEvent();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    EXPECT_NE(dragDropManager, nullptr);
    EXPECT_FALSE(dragEventActuator->IsNeedGather());
}

/**
 * @tc.name: DragEventActuatorCreateBadgeTextNodeTest001
 * @tc.desc: Test CreateBadgeTextNode function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorCreateBadgeTextNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke CreateBadgeTextNode.
     */
    auto textNode = dragEventActuator->CreateBadgeTextNode(frameNode, 1, 1.05f, true);
    EXPECT_EQ(textNode, nullptr);
}

/**
 * @tc.name: DragEventActuatorHandleTouchMoveEventTest001
 * @tc.desc: Test HandleTouchMoveEvent function.
 * @tc.type: FUNC 6
 */
HWTEST_F(DragEventTestNg, DragEventActuatorHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke HandleTouchMoveEvent.
     */
    dragEventActuator->longPressRecognizer_ = nullptr;
    dragEventActuator->HandleTouchMoveEvent();
    EXPECT_EQ(dragEventActuator->longPressRecognizer_, nullptr);

    /**
     * @tc.steps: step3. Invoke HandleTouchMoveEvent.
     */
    dragEventActuator->longPressRecognizer_ =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGERS_NUMBER, false, true);
    dragEventActuator->isOnBeforeLiftingAnimation = false;
    dragEventActuator->HandleTouchMoveEvent();
    EXPECT_NE(dragEventActuator->longPressRecognizer_, nullptr);
    EXPECT_FALSE(dragEventActuator->isOnBeforeLiftingAnimation);

    /**
     * @tc.steps: step4. Invoke HandleTouchMoveEvent.
     */
    dragEventActuator->isOnBeforeLiftingAnimation = true;
    dragEventActuator->longPressRecognizer_->disposal_ = GestureDisposal::ACCEPT;
    dragEventActuator->HandleTouchMoveEvent();
    EXPECT_NE(dragEventActuator->longPressRecognizer_, nullptr);
    EXPECT_TRUE(dragEventActuator->isOnBeforeLiftingAnimation);
    EXPECT_FALSE(dragEventActuator->longPressRecognizer_->GetGestureDisposal() == GestureDisposal::REJECT);

    /**
     * @tc.steps: step5. Invoke HandleTouchMoveEvent.
     */
    dragEventActuator->longPressRecognizer_->disposal_ = GestureDisposal::REJECT;
    dragEventActuator->isOnBeforeLiftingAnimation = true;
    dragEventActuator->HandleTouchMoveEvent();
    EXPECT_NE(dragEventActuator->longPressRecognizer_, nullptr);
    EXPECT_FALSE(dragEventActuator->isOnBeforeLiftingAnimation);
    EXPECT_TRUE(dragEventActuator->longPressRecognizer_->GetGestureDisposal() == GestureDisposal::REJECT);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest001
 * @tc.desc: Test MountGatherNode function.
 * @tc.type: FUNC 3
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    auto frameNode1 = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    EXPECT_NE(frameNode1, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode1));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    EXPECT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Create manager, gatherNode, gatherNodeChildrenInfo.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto manager = pipelineContext->GetOverlayManager();
    EXPECT_NE(manager, nullptr);
    auto gestureHub = dragEventActuator->gestureEventHub_.Upgrade();
    EXPECT_NE(gestureHub, nullptr);
    auto frameNode2 = gestureHub->GetFrameNode();
    EXPECT_NE(frameNode2, nullptr);
    manager->gatherNodeWeak_ = frameNode2;
    auto gatherNode = manager->GetGatherNode();
    EXPECT_NE(gatherNode, nullptr);
    std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo(2);
    dragEventActuator->MountGatherNode(manager, frameNode1, gatherNode, gatherNodeChildrenInfo);

    /**
     * @tc.steps: step3. Invoke MountGatherNode.
     */
    dragEventActuator->MountGatherNode(nullptr, frameNode1, gatherNode, gatherNodeChildrenInfo);
    EXPECT_FALSE(gatherNode->isLayoutDirtyMarked_);

    /**
     * @tc.steps: step4. Invoke MountGatherNode.
     */
    dragEventActuator->MountGatherNode(manager, nullptr, gatherNode, gatherNodeChildrenInfo);
    EXPECT_FALSE(gatherNode->isLayoutDirtyMarked_);

    /**
     * @tc.steps: step5. Invoke MountGatherNode.
     */
    dragEventActuator->MountGatherNode(nullptr, frameNode1, nullptr, gatherNodeChildrenInfo);
    EXPECT_FALSE(gatherNode->isLayoutDirtyMarked_);
}
}