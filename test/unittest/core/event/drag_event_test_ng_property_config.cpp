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
    auto globalStatus = DragDropFuncWrapper::IsGlobalStatusSuitableForDragging();
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
 * @tc.name: DragEventActuatorBlurStyleToEffectionTest001
 * @tc.desc: Test BlurStyleToEffection function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorBlurStyleToEffectionTest001, TestSize.Level1)
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
     * @tc.steps: step2. Invoke BlurStyleToEffection.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
    auto imageContext = imageNode->GetRenderContext();
    ASSERT_NE(imageContext, nullptr);
    auto blurstyletmp = imageContext->GetBackBlurStyle();
    blurstyletmp->colorMode = ThemeColorMode::DARK;
    DragDropFuncWrapper::BlurStyleToEffection(blurstyletmp);
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

    DragAnimationHelper::SetImageNodeInitAttr(frameNode, imageNode);
    EXPECT_TRUE(dragPreviewOption.defaultAnimationBeforeLifting);
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(dragPreviewOption.options.shadow.has_value());

    /**
     * @tc.steps: step3. Invoke SetImageNodeInitAttr.
     * @tc.desc: defaultAnimationBeforeLifting = true, layoutProperty = nullptr.
     */
    frameNode->layoutProperty_ = nullptr;
    DragAnimationHelper::SetImageNodeInitAttr(frameNode, imageNode);
    EXPECT_EQ(frameNode->GetLayoutProperty(), nullptr);

    /**
     * @tc.steps: step3. Invoke SetImageNodeInitAttr.
     * @tc.desc: defaultAnimationBeforeLifting = false, layoutProperty = nullptr.
     */
    dragPreviewOption.defaultAnimationBeforeLifting = false;
    DragAnimationHelper::SetImageNodeInitAttr(frameNode, imageNode);
    EXPECT_FALSE(dragPreviewOption.defaultAnimationBeforeLifting);

    /**
     * @tc.steps: step3. Invoke SetImageNodeInitAttr.
     * @tc.desc: dragPreviewOption.options.shadow.has_value() = true.
     */
    dragPreviewOption.options.shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultXS);
    DragAnimationHelper::SetImageNodeInitAttr(frameNode, imageNode);
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

    DragAnimationHelper::SetImageNodeFinishAttr(frameNode, imageNode);
    EXPECT_FALSE(dragPreviewOption.options.shadow->GetIsFilled());
    EXPECT_FALSE(dragPreviewOption.options.shadow.has_value());

    /**
     * @tc.steps: step3. Invoke SetImageNodeFinishAttr.
     */
    dragPreviewOption.options.shadow->isFilled_ = true;
    DragAnimationHelper::SetImageNodeFinishAttr(frameNode, imageNode);
    EXPECT_TRUE(dragPreviewOption.options.shadow->GetIsFilled());
    EXPECT_FALSE(dragPreviewOption.options.shadow.has_value());

    /**
     * @tc.steps: step4. Invoke SetImageNodeFinishAttr.
     */
    dragPreviewOption.options.shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultXS);
    dragPreviewOption.options.shadow->isFilled_ = false;
    DragAnimationHelper::SetImageNodeFinishAttr(frameNode, imageNode);
    EXPECT_FALSE(dragPreviewOption.options.shadow->GetIsFilled());
    EXPECT_TRUE(dragPreviewOption.options.shadow.has_value());

    /**
     * @tc.steps: step5. Invoke SetImageNodeFinishAttr.
     */
    dragPreviewOption.options.shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultXS);
    dragPreviewOption.options.shadow->isFilled_ = true;
    DragAnimationHelper::SetImageNodeFinishAttr(frameNode, imageNode);
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
    DragDropFuncWrapper::ResetNode(frameNode);
    dragPreviewOption = frameNode->GetDragPreviewOption();
    EXPECT_FALSE(dragPreviewOption.defaultAnimationBeforeLifting);

    /**
     * @tc.steps: step3. Invoke ResetNode.
     */
    dragPreviewOption.defaultAnimationBeforeLifting = true;
    frameNode->layoutProperty_ = nullptr;
    DragDropFuncWrapper::ResetNode(frameNode);
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
    auto textNode = DragAnimationHelper::CreateBadgeTextNode(1);
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
    dragEventActuator->isOnBeforeLiftingAnimation_ = false;
    dragEventActuator->HandleTouchMoveEvent();
    EXPECT_NE(dragEventActuator->longPressRecognizer_, nullptr);
    EXPECT_FALSE(dragEventActuator->isOnBeforeLiftingAnimation_);

    /**
     * @tc.steps: step4. Invoke HandleTouchMoveEvent.
     */
    dragEventActuator->isOnBeforeLiftingAnimation_ = true;
    dragEventActuator->longPressRecognizer_->disposal_ = GestureDisposal::ACCEPT;
    dragEventActuator->HandleTouchMoveEvent();
    EXPECT_NE(dragEventActuator->longPressRecognizer_, nullptr);
    EXPECT_TRUE(dragEventActuator->isOnBeforeLiftingAnimation_);
    EXPECT_FALSE(dragEventActuator->longPressRecognizer_->GetGestureDisposal() == GestureDisposal::REJECT);

    /**
     * @tc.steps: step5. Invoke HandleTouchMoveEvent.
     */
    dragEventActuator->longPressRecognizer_->disposal_ = GestureDisposal::REJECT;
    dragEventActuator->isOnBeforeLiftingAnimation_ = true;
    dragEventActuator->HandleTouchMoveEvent();
    EXPECT_NE(dragEventActuator->longPressRecognizer_, nullptr);
    EXPECT_FALSE(dragEventActuator->isOnBeforeLiftingAnimation_);
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

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest002
 * @tc.desc: Test HandleDragDampingMove function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest002, TestSize.Level1)
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
    auto point = Point(
        info.GetTouches().front().GetGlobalLocation().GetX(), info.GetTouches().front().GetGlobalLocation().GetY());
    dragDropManager->SetDraggingPointer(info.GetTouches().front().GetFingerId());
    dragDropManager->ResetDragging(DragDropMgrState::IDLE);
    dragEventActuator->isRedragStart_ = false;
    dragEventActuator->HandleDragDampingMove(point, info.GetTouches().front().GetFingerId(), true);
    EXPECT_EQ(dragEventActuator->isRedragStart_, true);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest004
 * @tc.desc: Test SetDragPreviewOptions.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest004, TestSize.Level1)
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
    DragPreviewOption previewOption;
    previewOption.isDefaultRadiusEnabled = true;
    framenode->SetDragPreviewOptions(previewOption);
    dragEventActuator->UpdatePreviewOptionDefaultAttr(framenode);
    EXPECT_EQ(previewOption.isDefaultRadiusEnabled, true);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest005
 * @tc.desc: Test SetEventColumn.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest005, TestSize.Level1)
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
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    manager->hasEvent_ = true;
    dragEventActuator->SetEventColumn(dragEventActuator);
    EXPECT_EQ(manager->hasEvent_, true);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest006
 * @tc.desc: Test BindClickEvent.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest006, TestSize.Level1)
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
    dragEventActuator->BindClickEvent(framenode);
    auto columnGestureHub = framenode->GetOrCreateGestureEventHub();
    auto event = columnGestureHub->clickEventActuator_->clickEvents_;
    GestureEvent info;
    for (auto item : event) {
        (*item)(info);
    }
    EXPECT_EQ(columnGestureHub->GetHitTestMode(), HitTestMode::HTMBLOCK);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest007
 * @tc.desc: Test BindClickEvent.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest007, TestSize.Level1)
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
    dragEventActuator->BindClickEvent(framenode);
    auto columnGestureHub = framenode->GetOrCreateGestureEventHub();
    auto event = columnGestureHub->clickEventActuator_->clickEvents_;
    GestureEvent info;
    auto gestureHub = dragEventActuator->gestureEventHub_.Upgrade();
    gestureHub->textDraggable_ = true;
    for (auto item : event) {
        (*item)(info);
    }
    EXPECT_EQ(columnGestureHub->GetHitTestMode(), HitTestMode::HTMBLOCK);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest008
 * @tc.desc: Test SetImageNodeInitAttr.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    auto framenode1 = FrameNode::CreateFrameNode("test1", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    framenode->previewOption_.defaultAnimationBeforeLifting = true;
    ASSERT_NE(dragEventActuator, nullptr);
    DragAnimationHelper::SetImageNodeInitAttr(framenode, framenode1);
    framenode->layoutProperty_ = nullptr;
    DragAnimationHelper::SetImageNodeInitAttr(framenode, framenode1);
    EXPECT_EQ(framenode->previewOption_.defaultAnimationBeforeLifting, true);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest009
 * @tc.desc: Test GetFrameNodePreviewPixelMap.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest009, TestSize.Level1)
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
    framenode->dragPreviewInfo_.inspectorId = "test";
    dragEventActuator->GetFrameNodePreviewPixelMap(framenode);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(static_cast<void*>(new char[0]));
    framenode->dragPreviewInfo_.pixelMap = pixelMap;
    framenode->dragPreviewInfo_.inspectorId = "";
    dragEventActuator->GetFrameNodePreviewPixelMap(framenode);
    EXPECT_EQ(gestureEventHub->GetDragPreviewPixelMap(), nullptr);;
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest010
 * @tc.desc: Test OnCollectTouchTarget.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest010, TestSize.Level1)
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
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    ASSERT_NE(getEventTargetImpl, nullptr);
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    framenode->GetOrCreateFocusHub();
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    EXPECT_EQ(dragEventActuator->panRecognizer_->onActionEnd_, nullptr);
    EXPECT_TRUE(finalResult.empty());
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    GestureEventFunc actionStart = [&unknownPropertyValue](
                                       GestureEvent& info) { unknownPropertyValue = info.GetScale(); };
    GestureEventFunc actionUpdate = [&unknownPropertyValue](
                                        GestureEvent& info) { unknownPropertyValue = info.GetScale(); };
    GestureEventFunc actionEnd = [&unknownPropertyValue](
                                     GestureEvent& info) { unknownPropertyValue = info.GetScale(); };
    GestureEventNoParameter actionCancel = [&unknownPropertyValue]() {
        unknownPropertyValue = GESTURE_EVENT_PROPERTY_VALUE;
    };
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionUpdate), std::move(actionEnd), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    ASSERT_NE(dragEventActuator->userCallback_, nullptr);
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    GestureEvent info = GestureEvent();
    auto gestureHub = dragEventActuator->gestureEventHub_.Upgrade();
    gestureHub->textDraggable_ = true;
    (*(dragEventActuator->panRecognizer_->onActionEnd_))(info);
    EXPECT_EQ(gestureHub->textDraggable_, true);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest011
 * @tc.desc: Create DragEventActuator and invoke onActionCancel callback.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->SetDraggable(true);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. Create DragEvent and set as DragEventActuator's DragEvent.
     * @tc.expected: dragEventActuator's userCallback_ is not null.
     */
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventFunc actionUpdate = [](GestureEvent& info) {};
    GestureEventFunc actionEnd = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = [&unknownPropertyValue]() {
        unknownPropertyValue = GESTURE_EVENT_PROPERTY_VALUE;
    };
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionUpdate), std::move(actionEnd), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    ASSERT_NE(dragEventActuator->userCallback_, nullptr);
    /**
     * @tc.steps: step3. Invoke OnCollectTouchTarget when userCallback_ is not null.
     * @tc.expected: longPressRecognizer is not nullptr and panRecognizer's callback onActionCancel is not nullptr.
     */
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    frameNode->GetOrCreateFocusHub();
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    dragEventActuator->panRecognizer_->onActionCancel_ = std::make_unique<GestureEventFunc>(
        [&unknownPropertyValue](GestureEvent& info) { unknownPropertyValue = GESTURE_EVENT_PROPERTY_VALUE; });
    ASSERT_NE(dragEventActuator->panRecognizer_->onActionCancel_, nullptr);
    unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    dragEventActuator->isNotInPreviewState_ = true;
    auto gestureHub = dragEventActuator->gestureEventHub_.Upgrade();
    gestureHub->textDraggable_ = false;
    GestureEvent info = GestureEvent();
    (*(dragEventActuator->panRecognizer_->onActionCancel_))(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest012
 * @tc.desc: Create DragEventActuator and invoke longPressUpdate callback.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    DragDropInfo dragDropInfo;
    frameNode->SetDragPreview(dragDropInfo);
    frameNode->SetDraggable(true);
    frameNode->GetOrCreateFocusHub();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. Create DragEvent and set as DragEventActuator's DragEvent.
     * @tc.expected: dragEventActuator's userCallback_ is not null.
     */
    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventFunc actionUpdate = [](GestureEvent& info) {};
    GestureEventFunc actionEnd = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionUpdate), std::move(actionEnd), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    ASSERT_NE(dragEventActuator->userCallback_, nullptr);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    frameNode->GetOrCreateFocusHub();
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    ASSERT_NE(dragEventActuator->previewLongPressRecognizer_->onAction_, nullptr);
    SystemProperties::debugEnabled_ = true;
    GestureEvent info = GestureEvent();
    dragEventActuator->userCallback_->actionLongPress_ = actionEnd;
    (*(dragEventActuator->longPressRecognizer_->onAction_))(info);
    EXPECT_EQ(dragEventActuator->GetIsNotInPreviewState(), true);
    dragEventActuator->userCallback_ = nullptr;
    (*(dragEventActuator->longPressRecognizer_->onAction_))(info);
    EXPECT_EQ(dragEventActuator->GetIsNotInPreviewState(), true);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest013
 * @tc.desc: Create DragEventActuator and invoke longPressUpdate callback.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    DragDropInfo dragDropInfo;
    frameNode->SetDragPreview(dragDropInfo);
    frameNode->SetDraggable(true);
    frameNode->GetOrCreateFocusHub();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. Create DragEvent and set as DragEventActuator's DragEvent.
     * @tc.expected: dragEventActuator's userCallback_ is not null.
     */
    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventFunc actionUpdate = [](GestureEvent& info) {};
    GestureEventFunc actionEnd = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionUpdate), std::move(actionEnd), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    ASSERT_NE(dragEventActuator->userCallback_, nullptr);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    frameNode->GetOrCreateFocusHub();
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    ASSERT_NE(dragEventActuator->previewLongPressRecognizer_->onAction_, nullptr);
    SystemProperties::debugEnabled_ = true;
    GestureEvent info = GestureEvent();
    auto gestureHub = dragEventActuator->gestureEventHub_.Upgrade();
    gestureHub->textDraggable_ = true;
    dragEventActuator->userCallback_->actionLongPress_ = actionEnd;
    (*(dragEventActuator->longPressRecognizer_->onAction_))(info);
    EXPECT_EQ(dragEventActuator->GetIsNotInPreviewState(), true);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest014
 * @tc.desc: Create DragEventActuator and invoke longPressUpdate callback.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest014, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    DragDropInfo dragDropInfo;
    frameNode->SetDragPreview(dragDropInfo);
    frameNode->SetDraggable(true);
    frameNode->GetOrCreateFocusHub();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventFunc actionUpdate = [](GestureEvent& info) {};
    GestureEventFunc actionEnd = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionUpdate), std::move(actionEnd), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    ASSERT_NE(dragEventActuator->userCallback_, nullptr);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    frameNode->GetOrCreateFocusHub();
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    ASSERT_NE(dragEventActuator->previewLongPressRecognizer_->onAction_, nullptr);
    SystemProperties::debugEnabled_ = true;
    EXPECT_EQ(gestureEventHub->GetTextDraggable(), false);
    EXPECT_EQ(dragEventActuator->IsAllowedDrag(), true);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->hasPixelMap_ = true;
    GestureEvent info = GestureEvent();
    (*(dragEventActuator->previewLongPressRecognizer_->onAction_))(info);
    EXPECT_EQ(dragEventActuator->GetIsNotInPreviewState(), false);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest015
 * @tc.desc: Create DragEventActuator and invoke longPressUpdate callback.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    DragDropInfo dragDropInfo;
    frameNode->SetDragPreview(dragDropInfo);
    frameNode->SetDraggable(true);
    frameNode->GetOrCreateFocusHub();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);

    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventFunc actionUpdate = [](GestureEvent& info) {};
    GestureEventFunc actionEnd = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionUpdate), std::move(actionEnd), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    ASSERT_NE(dragEventActuator->userCallback_, nullptr);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    frameNode->GetOrCreateFocusHub();
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    ASSERT_NE(dragEventActuator->previewLongPressRecognizer_->onAction_, nullptr);
    SystemProperties::debugEnabled_ = true;
    EXPECT_EQ(gestureEventHub->GetTextDraggable(), false);
    EXPECT_EQ(dragEventActuator->IsAllowedDrag(), true);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->dragDropState_ = DragDropMgrState::ABOUT_TO_PREVIEW;
    GestureEvent info = GestureEvent();
    (*(dragEventActuator->previewLongPressRecognizer_->onAction_))(info);
    EXPECT_EQ(dragEventActuator->GetIsNotInPreviewState(), false);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest016
 * @tc.desc: Create DragEventActuator and invoke longPressUpdate callback.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    DragDropInfo dragDropInfo;
    frameNode->SetDragPreview(dragDropInfo);
    frameNode->SetDraggable(true);
    frameNode->GetOrCreateFocusHub();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventFunc actionUpdate = [](GestureEvent& info) {};
    GestureEventFunc actionEnd = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionUpdate), std::move(actionEnd), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    ASSERT_NE(dragEventActuator->userCallback_, nullptr);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    frameNode->GetOrCreateFocusHub();
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    ASSERT_NE(dragEventActuator->previewLongPressRecognizer_->onAction_, nullptr);
    SystemProperties::debugEnabled_ = true;
    EXPECT_EQ(gestureEventHub->GetTextDraggable(), false);
    EXPECT_EQ(dragEventActuator->IsAllowedDrag(), true);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->dragDropState_ = DragDropMgrState::DRAGGING;
    GestureEvent info = GestureEvent();
    (*(dragEventActuator->previewLongPressRecognizer_->onAction_))(info);
    EXPECT_EQ(dragEventActuator->GetIsNotInPreviewState(), false);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest017
 * @tc.desc: Test BlurStyleToEffection.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);

    std::vector<float> vecGrayScale = { 0.0f, 0.0f };
    BlurStyleOption blurStyleInfo = { BlurStyle::NO_MATERIAL, ThemeColorMode::SYSTEM, AdaptiveColor::DEFAULT, 1.0,
        { vecGrayScale } };
    std::optional<BlurStyleOption> optBlurStyleInfo(blurStyleInfo);
    auto optEffectOption = DragDropFuncWrapper::BlurStyleToEffection(optBlurStyleInfo);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    EXPECT_EQ(optEffectOption.has_value(), false);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<BlurStyleTheme>()));
    auto blurStyleTheme = pipeline->GetTheme<BlurStyleTheme>();
    ASSERT_NE(blurStyleTheme, nullptr);
    auto resAdapter = RefPtr<ResourceAdapter>();
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(resAdapter);
    std::unordered_map<std::string, ResValueWrapper> attributes;
    ResValueWrapper resValueWrapper;
    resValueWrapper.type = ThemeConstantsType::THEME;
    resValueWrapper.value = AceType::MakeRefPtr<ThemeStyle>();
    attributes.insert(std::pair<std::string, ResValueWrapper>(THEME_BLUR_STYLE_COMMON, resValueWrapper));
    themeConstants->currentThemeStyle_ = AceType::MakeRefPtr<ThemeStyle>();
    themeConstants->currentThemeStyle_->SetAttributes(attributes);
    auto blThemeInstance = BlurStyleTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(BlurStyleTheme::TypeId())).WillRepeatedly(Return(blThemeInstance));

    optBlurStyleInfo->colorMode = ThemeColorMode::LIGHT;
    optEffectOption = DragDropFuncWrapper::BlurStyleToEffection(optBlurStyleInfo);
    ASSERT_NE(optEffectOption.has_value(), true);
    EXPECT_EQ(resValueWrapper.type, ThemeConstantsType::THEME);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest018
 * @tc.desc: Test SetFilter.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest018, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    framenode->SetParent(parentNode);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    auto dragEventActuatorTwo = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuatorTwo, nullptr);
    dragEventActuator->SetFilter(dragEventActuatorTwo);
    parentNode->depth_ = 1;
    dragEventActuator->SetFilter(dragEventActuatorTwo);
    EXPECT_EQ(parentNode->depth_, 1);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest019
 * @tc.desc: Test SetFilter.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest019, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode(V2::WEB_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    framenode->SetParent(parentNode);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    auto dragEventActuatorTwo = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuatorTwo, nullptr);
    parentNode->depth_ = 1;
    MockContainer::SetUp();
    dragEventActuator->SetFilter(dragEventActuatorTwo);
    auto container = MockContainer::Current();
    container->isSceneBoardWindow_ = true;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto manager = pipelineContext->GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    manager->hasFilter_ = false;
    dragEventActuator->SetFilter(dragEventActuatorTwo);
    manager->isOnAnimation_ = true;
    manager->hasFilter_ = false;
    dragEventActuator->SetFilter(dragEventActuatorTwo);
    manager->hasFilter_ = true;
    dragEventActuator->SetFilter(dragEventActuatorTwo);
    container->isSceneBoardWindow_ = false;
    MockContainer::TearDown();
    EXPECT_EQ(manager->hasFilter_, true);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest021
 * @tc.desc: Test SetPixelMap.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest021, TestSize.Level1)
{
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

    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto manager = pipelineContext->GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    manager->SetHasPixelMap(false);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    gestureEventHub->SetPixelMap(pixelMap);
    dragEventActuator->SetPixelMap(dragEventActuator);
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->isSceneBoardWindow_ = true;
    manager->SetHasPixelMap(false);
    dragEventActuator->SetPixelMap(dragEventActuator);
    manager->SetHasPixelMap(false);
    container->isSceneBoardWindow_ = false;
    dragEventActuator->SetPixelMap(dragEventActuator);
    MockContainer::TearDown();
    EXPECT_EQ(container->isSceneBoardWindow_, false);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest022
 * @tc.desc: Test UpdatePreviewOptionFromModifier function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest022, TestSize.Level1)
{
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
    NG::DragPreviewOption previewOptions;
    previewOptions.onApply = [](WeakPtr<NG::FrameNode> frameNodes) {
        auto node = frameNodes.Upgrade();
        auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
        mockRenderContext->UpdateOpacity(-0.1f);
        BorderRadiusProperty borderRadius;
        borderRadius.SetRadius(Dimension(0.1));
        Shadow shadow;
        shadow.SetIsFilled(true);
        shadow.SetOffset(Offset(5, 5));
        shadow.SetBlurRadius(10.0);
        shadow.SetColor(Color::FromARGB(255, 255, 0, 0));
        mockRenderContext->UpdateBackShadow(shadow);
        mockRenderContext->UpdateBorderRadius(borderRadius);
        node->renderContext_ = mockRenderContext;
    };
    framenode->SetDragPreviewOptions(previewOptions);
    dragEventActuator->UpdatePreviewOptionFromModifier(framenode);

    previewOptions.onApply = [](WeakPtr<NG::FrameNode> frameNodes) {
        auto node = frameNodes.Upgrade();
        auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
        mockRenderContext->UpdateOpacity(1.1f);
        node->renderContext_ = mockRenderContext;
    };
    framenode->SetDragPreviewOptions(previewOptions);
    dragEventActuator->UpdatePreviewOptionFromModifier(framenode);

    previewOptions.onApply = [](WeakPtr<NG::FrameNode> frameNodes) {
        auto node = frameNodes.Upgrade();
        auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
        node->renderContext_ = mockRenderContext;
    };
    framenode->SetDragPreviewOptions(previewOptions);
    dragEventActuator->UpdatePreviewOptionFromModifier(framenode);
    EXPECT_EQ(previewOptions.isMultiSelectionEnabled, false);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest023
 * @tc.desc: Test UpdatePreviewOptionFromModifier function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest023, TestSize.Level1)
{
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
    NG::DragPreviewOption previewOptions;
    previewOptions.onApply = [](WeakPtr<NG::FrameNode> frameNodes) {
        auto node = frameNodes.Upgrade();
        auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
        BlurStyleOption styleOption;
        styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
        styleOption.scale = 0.5;
        styleOption.colorMode = ThemeColorMode::LIGHT;
        mockRenderContext->UpdateBackBlurStyle(styleOption);
        node->renderContext_ = mockRenderContext;
    };
    framenode->SetDragPreviewOptions(previewOptions);
    dragEventActuator->UpdatePreviewOptionFromModifier(framenode);

    previewOptions.onApply = [](WeakPtr<NG::FrameNode> frameNodes) {
        auto node = frameNodes.Upgrade();
        auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
        CalcDimension radius;
        radius.SetValue(80.0f);
        Color color = Color::FromARGB(13, 255, 255, 255);
        EffectOption effoption = { radius, 1.0, 1.08, color };
        const auto& groupProperty = mockRenderContext->GetOrCreateBackground();
        groupProperty->propEffectOption = effoption;
        node->renderContext_ = mockRenderContext;
    };
    framenode->SetDragPreviewOptions(previewOptions);
    dragEventActuator->UpdatePreviewOptionFromModifier(framenode);
    EXPECT_EQ(previewOptions.isMultiSelectionEnabled, false);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest024
 * @tc.desc: Test SetFilter.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest024, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    framenode->SetParent(parentNode);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    DragDropFuncWrapper::ApplyNewestOptionExecutedFromModifierToNode(framenode, parentNode);
    Dimension dimen(2.0);
    BlurBackGroundInfo bgBackEffect = { { dimen, 1.0f, 1.0f, Color::TRANSPARENT, AdaptiveColor::DEFAULT,
        { { 2.0f, 2.0f } } } };
    Shadow shadow;
    shadow.SetIsFilled(false);
    shadow.SetOffset(Offset(5, 5));
    shadow.SetBlurRadius(10.0);
    shadow.SetColor(Color::FromARGB(255, 255, 0, 0));
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(0.1));
    OptionsAfterApplied optionTmp = { 0, shadow, "test", true, borderRadius, { bgBackEffect } };
    NG::DragPreviewOption previewOptions;
    previewOptions.options = optionTmp;
    parentNode->SetDragPreviewOptions(previewOptions);
    DragDropFuncWrapper::ApplyNewestOptionExecutedFromModifierToNode(framenode, parentNode);
    EXPECT_EQ(previewOptions.isMultiSelectionEnabled, false);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest025
 * @tc.desc: Test SetEventColumn.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest025, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    DragDropInfo dragDropInfo;
    frameNode->SetDragPreview(dragDropInfo);
    frameNode->GetOrCreateFocusHub();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventFunc actionUpdate = [](GestureEvent& info) {};
    GestureEventFunc actionEnd = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionUpdate), std::move(actionEnd), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    GestureEvent info = GestureEvent();
    SystemProperties::debugEnabled_ = false;
    frameNode->SetDraggable(false);
    gestureEventHub->SetTextDraggable(true);
    gestureEventHub->SetIsTextDraggable(true);
    dragEventActuator->SetIsNotInPreviewState(true);
    (*(dragEventActuator->previewLongPressRecognizer_->onAction_))(info);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto manager = pipelineContext->GetOverlayManager();
    manager->hasEvent_ = false;
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->isSceneBoardWindow_ = true;
    (*(dragEventActuator->previewLongPressRecognizer_->onAction_))(info);
    container->isSceneBoardWindow_ = false;
    manager->hasEvent_ = false;
    (*(dragEventActuator->previewLongPressRecognizer_->onAction_))(info);
    (*(dragEventActuator->previewLongPressRecognizer_->onAction_))(info);
    MockContainer::TearDown();
    EXPECT_EQ(manager->hasEvent_, true);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest026
 * @tc.desc: Test SetImageNodeInitAttr
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest026, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    auto framenodeOne = FrameNode::CreateFrameNode("test1", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenodeOne, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    framenode->previewOption_.defaultAnimationBeforeLifting = true;
    ASSERT_NE(dragEventActuator, nullptr);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    mockRenderContext->UpdateOpacity(1.1f);
    framenodeOne->renderContext_ = mockRenderContext;
    Dimension dimen(2.0);
    BlurBackGroundInfo bgBackEffect = { { dimen, 1.0f, 1.0f, Color::TRANSPARENT, AdaptiveColor::DEFAULT,
        { { 2.0f, 2.0f } } } };
    Shadow shadow;
    shadow.SetIsFilled(false);
    shadow.SetOffset(Offset(5, 5));
    shadow.SetBlurRadius(10.0);
    shadow.SetColor(Color::FromARGB(255, 255, 0, 0));
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(0.1));
    OptionsAfterApplied optionTmp = { 0, shadow, "test", true, borderRadius, { bgBackEffect } };
    NG::DragPreviewOption previewOptions;
    previewOptions.options = optionTmp;
    framenode->SetDragPreviewOptions(previewOptions);
    DragAnimationHelper::SetImageNodeInitAttr(framenode, framenodeOne);
    DragAnimationHelper::SetImageNodeFinishAttr(framenode, framenodeOne);
    previewOptions.options.shadow->isFilled_ = true;
    framenode->SetDragPreviewOptions(previewOptions);
    DragAnimationHelper::SetImageNodeFinishAttr(framenode, framenodeOne);

    DragDropInfo dragDropInfo;
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(static_cast<void*>(new char[0]));
    dragDropInfo.pixelMap = pixelMap;
    dragDropInfo.inspectorId = "";
    gestureEventHub->dragPreviewPixelMap_ = pixelMap;
    framenode->SetDragPreview(dragDropInfo);
    GatherNodeChildInfo gatherNodeChildInfo;
    dragEventActuator->CreateImageNode(framenode, gatherNodeChildInfo);
    EXPECT_EQ(shadow.GetBlurRadius(), 10.0);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest027
 * @tc.desc: Test MountGatherNode function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest027, TestSize.Level1)
{
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
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto manager = pipelineContext->GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    auto gestureHub = dragEventActuator->gestureEventHub_.Upgrade();
    ASSERT_NE(gestureHub, nullptr);
    auto frameNodeOne = gestureHub->GetFrameNode();
    ASSERT_NE(frameNodeOne, nullptr);
    manager->gatherNodeWeak_ = frameNodeOne;
    auto gatherNode = manager->GetGatherNode();
    ASSERT_NE(gatherNode, nullptr);
    std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo(2);
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->isSceneBoardWindow_ = true;
    dragEventActuator->MountGatherNode(manager, frameNode, gatherNode, gatherNodeChildrenInfo);
    container->isSceneBoardWindow_ = false;
    MockContainer::TearDown();
    EXPECT_EQ(container->isSceneBoardWindow_, false);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest028
 * @tc.desc: Test IsBelongToMultiItemNode function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest028, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    frameNode->SetParent(parentNode);

    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    dragEventActuator->IsBelongToMultiItemNode(frameNode);
    DragPreviewOption previewOption;
    previewOption.isMultiSelectionEnabled = true;
    parentNode->SetDragPreviewOptions(previewOption);
    dragEventActuator->IsBelongToMultiItemNode(frameNode);
    auto eventHubp = parentNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHubp, nullptr);
    auto func = [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) { return DragDropInfo(); };
    eventHubp->onDragStart_ = func;
    dragEventActuator->IsBelongToMultiItemNode(frameNode);
    auto childNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childNode, nullptr);
    auto parentNodeTwo = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNodeTwo, nullptr);
    childNode->SetParent(parentNodeTwo);
    dragEventActuator->FindItemParentNode(frameNode);
    dragEventActuator->FindItemParentNode(childNode);
    EXPECT_EQ(previewOption.isMultiSelectionEnabled, true);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest029
 * @tc.desc: Test PrepareShadowParametersForDragData
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest029, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode(V2::RICH_EDITOR_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    auto framenodeOne = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenodeOne, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    Dimension dimen(2.0);
    BlurBackGroundInfo bgBackEffect = { { dimen, 1.0f, 1.0f, Color::TRANSPARENT, AdaptiveColor::DEFAULT,
        { { 2.0f, 2.0f } } } };
    Shadow shadow;
    shadow.SetIsFilled(false);
    shadow.SetOffset(Offset(5, 5));
    shadow.SetBlurRadius(10.0);
    shadow.SetColor(Color::FromARGB(255, 255, 0, 0));
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(0.1));
    OptionsAfterApplied optionTmp = { 0, shadow, "test", true, borderRadius, { bgBackEffect } };
    NG::DragPreviewOption previewOptions;
    previewOptions.options = optionTmp;
    previewOptions.options.shadow->isFilled_ = true;
    framenode->SetDragPreviewOptions(previewOptions);
    framenodeOne->SetDragPreviewOptions(previewOptions);
    std::unique_ptr<JsonValue> arkExtraInfoJson = std::make_unique<JsonValue>();
    float scale = 1.0f;
    auto gestureHub = framenode->GetOrCreateGestureEventHub();
    auto gestureHubOne = framenodeOne->GetOrCreateGestureEventHub();
    dragEventActuator->PrepareShadowParametersForDragData(framenode, arkExtraInfoJson, scale);
    gestureHub->textDraggable_ = true;
    dragEventActuator->PrepareShadowParametersForDragData(framenode, arkExtraInfoJson, scale);
    gestureHub->isTextDraggable_ = true;
    dragEventActuator->PrepareShadowParametersForDragData(framenode, arkExtraInfoJson, scale);
    gestureHubOne->isTextDraggable_ = true;
    gestureHubOne->textDraggable_ = true;
    dragEventActuator->PrepareShadowParametersForDragData(framenodeOne, arkExtraInfoJson, scale);
    EXPECT_EQ(gestureHubOne->textDraggable_, true);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest030
 * @tc.desc: Test PrepareShadowParametersForDragData
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest030, TestSize.Level1)
{
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
    Dimension dimen(2.0);
    BlurBackGroundInfo bgBackEffect = { { dimen, 1.0f, 1.0f, Color::TRANSPARENT, AdaptiveColor::DEFAULT,
        { { 2.0f, 2.0f } } } };
    Shadow shadow;
    shadow.SetIsFilled(false);
    shadow.SetOffset(Offset(0, 0));
    shadow.SetBlurRadius(-10.0);
    shadow.SetColor(Color::FromARGB(255, 255, 0, 0));
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(0.1));
    OptionsAfterApplied optionTmp = { 0, shadow, "test", true, borderRadius, { bgBackEffect } };
    NG::DragPreviewOption previewOptions;
    previewOptions.options = optionTmp;
    previewOptions.options.shadow->isFilled_ = true;
    framenode->SetDragPreviewOptions(previewOptions);
    std::unique_ptr<JsonValue> arkExtraInfoJson = std::make_unique<JsonValue>();
    float scale = 1.0f;
    dragEventActuator->PrepareShadowParametersForDragData(framenode, arkExtraInfoJson, scale);
    Shadow shadows;
    shadows.SetIsFilled(false);
    shadows.SetOffset(Offset(5, 5));
    optionTmp = { 0, shadows, "test", true, borderRadius, { bgBackEffect } };
    previewOptions.options = optionTmp;
    framenode->SetDragPreviewOptions(previewOptions);
    dragEventActuator->PrepareShadowParametersForDragData(framenode, arkExtraInfoJson, scale);
    EXPECT_EQ(previewOptions.options.opacity, 0.0f);
}
}