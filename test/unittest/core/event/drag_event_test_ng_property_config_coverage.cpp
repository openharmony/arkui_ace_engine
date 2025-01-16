/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/mock/base/mock_task_executor.h"
#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: DragEventActuatorMountGatherNodeTest031
 * @tc.desc: Test UpdatePreviewAttr function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest031, TestSize.Level1)
{
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
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
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
    frameNode->SetDragPreviewOptions(previewOptions);
    dragEventActuator->UpdatePreviewAttr(frameNode, imageNode);
    EXPECT_EQ(shadow.GetBlurRadius(), 10.0);
}
/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest032
 * @tc.desc: Test PrepareRadiusParametersForDragData function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest032, TestSize.Level1)
{
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
    Dimension dimen(2.0);
    BlurBackGroundInfo bgBackEffect = { { dimen, 1.0f, 1.0f, Color::TRANSPARENT, AdaptiveColor::DEFAULT,
        { { 2.0f, 2.0f } } } };
    Shadow shadow;
    shadow.SetIsFilled(false);
    shadow.SetOffset(Offset(5, 5));
    shadow.SetBlurRadius(10.0);
    shadow.SetColor(Color::FromARGB(255, 255, 0, 0));
    BorderRadiusProperty borderRadius;
    borderRadius.radiusBottomRight = dimen;
    OptionsAfterApplied optionTmp = { 0, shadow, "test", true, borderRadius, { bgBackEffect } };
    NG::DragPreviewOption previewOptions;
    previewOptions.options = optionTmp;
    frameNode->SetDragPreviewOptions(previewOptions);
    std::unique_ptr<JsonValue> arkExtraInfoJson = std::make_unique<JsonValue>();
    dragEventActuator->PrepareRadiusParametersForDragData(frameNode, arkExtraInfoJson);
    BorderRadiusProperty borderRadiusTwo;
    borderRadiusTwo.radiusBottomLeft = dimen;
    optionTmp = { 0, shadow, "test", true, borderRadiusTwo, { bgBackEffect } };
    previewOptions.options = optionTmp;
    frameNode->SetDragPreviewOptions(previewOptions);
    dragEventActuator->PrepareRadiusParametersForDragData(frameNode, arkExtraInfoJson);
    EXPECT_EQ(shadow.GetBlurRadius(), 10.0);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest034
 * @tc.desc: Create DragEventActuator and invoke longPressUpdate callback.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest034, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    DragDropInfo dragDropInfo;
    frameNode->SetDragPreview(dragDropInfo);
    frameNode->SetDraggable(true);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionStart), std::move(actionStart), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    SystemProperties::debugEnabled_ = true;
    GestureEvent info = GestureEvent();
    NG::DragPreviewOption previewOptions;
    previewOptions.isNumber = true;
    previewOptions.badgeNumber = 2;
    frameNode->SetDragPreviewOptions(previewOptions);
    gestureEventHub->previewMode_ = MenuPreviewMode::IMAGE;
    (*(dragEventActuator->previewLongPressRecognizer_->onAction_))(info);
    auto onKeyEvent = [](const KeyEvent& event) -> bool { return true; };
    focusHub->SetOnKeyEventInternal(onKeyEvent, OnKeyEventType::CONTEXT_MENU);
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    (*(dragEventActuator->previewLongPressRecognizer_->onAction_))(info);
    EXPECT_EQ(previewOptions.isNumber, true);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest035
 * @tc.desc: Create DragEventActuator and invoke longPressUpdate callback.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest035, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    DragDropInfo dragDropInfo;
    frameNode->SetDragPreview(dragDropInfo);
    frameNode->SetDraggable(true);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionStart), std::move(actionStart), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    GestureEvent info = GestureEvent();
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    auto childNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childNode, nullptr);
    frameNode->AddChild(childNode);
    ASSERT_NE(childNode->GetRenderContext(), nullptr);
    auto parentNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    frameNode->SetParent(parentNode);
    dragEventActuator->itemParentNode_ = parentNode;
    manager->pixmapColumnNodeWeak_ = WeakPtr<FrameNode>(AceType::DynamicCast<FrameNode>(frameNode));
    (*(dragEventActuator->previewLongPressRecognizer_->onAction_))(info);
    gestureEventHub->contextMenuShowStatus_ = true;
    (*(dragEventActuator->previewLongPressRecognizer_->onAction_))(info);
    Offset offSet;
    dragEventActuator->previewLongPressRecognizer_->callback_(offSet);
    gestureEventHub->textDraggable_ = true;
    dragEventActuator->previewLongPressRecognizer_->callback_(offSet);
    EXPECT_EQ(gestureEventHub->textDraggable_, true);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest036
 * @tc.desc: Create DragEventActuator and invoke thumbnail callback.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest036, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->SetDraggable(true);
    NG::DragDropInfo dragPreviewInfo;
    dragPreviewInfo.inspectorId = "123";
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(static_cast<void*>(new char[0]));
    dragPreviewInfo.pixelMap = pixelMap;
    frameNode->SetDragPreview(dragPreviewInfo);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto onDragStart = [](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) -> DragDropInfo {
        DragDropInfo info;
        info.inspectorId = "123";
        void* voidPtr = static_cast<void*>(new char[0]);
        info.pixelMap = PixelMap::CreatePixelMap(voidPtr);
        return info;
    };
    eventHub->SetOnDragStart(std::move(onDragStart));

    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);

    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    GestureEventFunc actionStart = [&unknownPropertyValue](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = [&unknownPropertyValue]() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionStart), std::move(actionStart), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);

    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    frameNode->GetOrCreateFocusHub();
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);

    dragEventActuator->longPressRecognizer_->callback_(Offset(WIDTH, HEIGHT));
    EXPECT_EQ(gestureEventHub->pixelMap_, nullptr);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest037
 * @tc.desc: Create DragEventActuator and invoke longPressUpdate callback.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest037, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionStart), std::move(actionStart), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    GestureEvent info = GestureEvent();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    auto childNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childNode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    frameNode->SetParent(parentNode);
    dragEventActuator->itemParentNode_ = parentNode;
    manager->pixmapColumnNodeWeak_ = WeakPtr<FrameNode>(AceType::DynamicCast<FrameNode>(frameNode));
    dragEventActuator->isSelectedItemNode_ = true;
    auto pattern = AceType::MakeRefPtr<GridPattern>();
    auto itemPattern = AceType::MakeRefPtr<GridItemPattern>(nullptr, GridItemStyle::NONE);
    itemPattern->isSelected_ = true;
    auto tempChildNode = FrameNode::CreateFrameNode("BackButton", 2, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(tempChildNode, nullptr);
    childNode->pattern_ = itemPattern;
    tempChildNode->pattern_ = itemPattern;
    frameNode->AddChild(childNode);
    frameNode->AddChild(tempChildNode);
    pattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    pattern->info_.startIndex_ = 0;
    pattern->info_.endIndex_ = 3;
    parentNode->pattern_ = pattern;
    (*(dragEventActuator->previewLongPressRecognizer_->onAction_))(info);
    EXPECT_EQ(itemPattern->isSelected_, true);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest038
 * @tc.desc: SetGatherNodeAboveFilter
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest038, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    auto childNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childNode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    frameNode->SetParent(parentNode);
    dragEventActuator->itemParentNode_ = parentNode;
    dragEventActuator->isSelectedItemNode_ = true;
    auto pattern = AceType::MakeRefPtr<GridPattern>();
    auto itemPattern = AceType::MakeRefPtr<GridItemPattern>(nullptr, GridItemStyle::NONE);
    itemPattern->isSelected_ = true;
    auto tempChildNode = FrameNode::CreateFrameNode("BackButton", 2, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(tempChildNode, nullptr);
    childNode->pattern_ = itemPattern;
    tempChildNode->pattern_ = itemPattern;
    frameNode->AddChild(childNode);
    frameNode->AddChild(tempChildNode);
    pattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    pattern->info_.startIndex_ = 0;
    pattern->info_.endIndex_ = 3;
    parentNode->pattern_ = pattern;
    dragEventActuator->SetGatherNodeAboveFilter(dragEventActuator);
    EXPECT_EQ(itemPattern->isSelected_, true);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest039
 * @tc.desc: Test GetOrCreateGatherNode function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest039, TestSize.Level1)
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
    std::vector<GatherNodeChildInfo> gatherNodeChildInfo(2);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto childNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childNode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    dragEventActuator->itemParentNode_ = parentNode;
    dragEventActuator->isSelectedItemNode_ = true;
    auto pattern = AceType::MakeRefPtr<GridPattern>();
    auto itemPattern = AceType::MakeRefPtr<GridItemPattern>(nullptr, GridItemStyle::NONE);
    itemPattern->isSelected_ = true;
    auto tempChildNode = FrameNode::CreateFrameNode("BackButton", 2, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(tempChildNode, nullptr);
    childNode->pattern_ = itemPattern;
    tempChildNode->pattern_ = itemPattern;
    frameNode->AddChild(childNode);
    frameNode->AddChild(tempChildNode);
    pattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    pattern->info_.startIndex_ = 0;
    pattern->info_.endIndex_ = 3;
    parentNode->pattern_ = pattern;
    auto gatherNode = dragEventActuator->GetOrCreateGatherNode(overlayManager, dragEventActuator, gatherNodeChildInfo);
    NG::DragPreviewOption previewOptions;
    previewOptions.isMultiSelectionEnabled = true;
    frameNode->SetDragPreviewOptions(previewOptions);
    dragEventActuator->GetOrCreateGatherNode(overlayManager, dragEventActuator, gatherNodeChildInfo);
    overlayManager->gatherNodeWeak_ = dragEventActuator->CreateGatherNode(dragEventActuator);
    dragEventActuator->GetOrCreateGatherNode(overlayManager, dragEventActuator, gatherNodeChildInfo);
    EXPECT_EQ(gatherNode, nullptr);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest040
 * @tc.desc: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest040, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    auto childNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childNode, nullptr);
    auto parentNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    frameNode->SetParent(parentNode);
    dragEventActuator->itemParentNode_ = parentNode;
    dragEventActuator->isSelectedItemNode_ = true;
    auto pattern = AceType::MakeRefPtr<GridPattern>();
    auto itemPattern = AceType::MakeRefPtr<GridItemPattern>(nullptr, GridItemStyle::NONE);
    itemPattern->isSelected_ = true;
    auto tempChildNode = FrameNode::CreateFrameNode("BackButton", 2, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(tempChildNode, nullptr);
    childNode->pattern_ = itemPattern;
    tempChildNode->pattern_ = itemPattern;
    frameNode->AddChild(childNode);
    frameNode->AddChild(tempChildNode);
    pattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    pattern->info_.startIndex_ = 0;
    pattern->info_.endIndex_ = 3;
    parentNode->pattern_ = pattern;
    dragEventActuator->HandleTouchUpEvent();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    DragDropGlobalController::GetInstance().SetPreDragStatus(PreDragStatus::PREVIEW_LANDING_STARTED);
    dragEventActuator->HandleTouchUpEvent();
    dragEventActuator->SetResponseRegionFull();
    dragEventActuator->ResetResponseRegion();
    dragEventActuator->isResponseRegionFull_ = false;
    dragEventActuator->ResetResponseRegion();
    EXPECT_EQ(dragEventActuator->isResponseRegionFull_, false);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest041
 * @tc.desc: AddTouchListener
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest041, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionStart), std::move(actionStart), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    TouchRestrict touchRestrict;
    dragEventActuator->AddTouchListener(touchRestrict);
    auto touchEventActuator = gestureEventHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto events = touchEventActuator->touchEvents_;
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::CANCEL);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    ASSERT_NE(events.size(), 0);
    for (auto event : events) {
        event->callback_(info);
    }
    info.touches_.clear();
    touchInfo1.SetTouchType(TouchType::UP);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    for (auto event : events) {
        event->callback_(info);
    }
    info.touches_.clear();
    touchInfo1.SetTouchType(TouchType::MOVE);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    for (auto event : events) {
        event->callback_(info);
    }
    info.touches_.clear();
    for (auto event : events) {
        event->callback_(info);
    }
    EXPECT_EQ(gestureEventHub->GetTextDraggable(), false);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest042
 * @tc.desc: AddTouchListener
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest042, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionStart), std::move(actionStart), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    TouchRestrict touchRestrict;
    auto onKeyEvent = [](const KeyEvent& event) -> bool { return true; };
    focusHub->SetOnKeyEventInternal(onKeyEvent, OnKeyEventType::CONTEXT_MENU);
    dragEventActuator->AddTouchListener(touchRestrict);
    auto touchEventActuator = gestureEventHub->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto events = touchEventActuator->touchEvents_;
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::MOVE);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    for (auto event : events) {
        event->callback_(info);
    }
    EXPECT_EQ(gestureEventHub->GetTextDraggable(), false);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest043
 * @tc.desc: Create DragEventActuator and invoke HideTextAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest043, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    NG::DragDropInfo dragPreviewInfo;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    dragPreviewInfo.pixelMap = pixelMap;
    frameNode->SetDragPreview(dragPreviewInfo);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    frameNode->SetDraggable(true);
    gestureEventHub->SetTextDraggable(true);
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto childNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childNode, nullptr);
    auto patterns = AceType::MakeRefPtr<TextDragPattern>();
    patterns->CreateNodePaintMethod();
    childNode->pattern_ = patterns;
    pattern->dragNode_ = childNode;
    frameNode->pattern_ = pattern;

    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetOverlayManager();
    manager->pixmapColumnNodeWeak_ = childNode;
    dragEventActuator->HideTextAnimation();
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pixmap, GetWidth()).WillRepeatedly(Return(200));
    gestureEventHub->pixelMap_ = pixmap;
    dragEventActuator->HideTextAnimation(true);
    EXPECT_EQ(gestureEventHub->GetTextDraggable(), true);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest044
 * @tc.desc: Create GetPreviewPixelMap and invoke HideTextAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest044, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    gestureEventHub->SetTextDraggable(true);

    gestureEventHub->pixelMap_ = pixelMap;
    frameNode->UpdateInspectorId("testid");
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    frameNode->layoutProperty_ = layoutProperty;
    Inspector::offscreenNodes.clear();
    Inspector::AddOffscreenNode(frameNode);
    DragDropFuncWrapper::GetPreviewPixelMap("testid", frameNode);
    layoutProperty->propVisibility_ = VisibleType::GONE;
    DragDropFuncWrapper::GetPreviewPixelMap("testid", frameNode);
    layoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    DragDropFuncWrapper::GetPreviewPixelMap("testid", frameNode);
    EXPECT_EQ(gestureEventHub->GetTextDraggable(), true);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest045
 * @tc.desc: Create DragEventActuator and invoke CreateTiledPixelMap function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest045, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    gestureEventHub->contextMenuShowStatus_ = true;
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    ResponseLinkResult responseLinkResult;
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    GestureEventFunc actionStart = [&unknownPropertyValue](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = [&unknownPropertyValue]() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionStart), std::move(actionStart), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    dragEventActuator->SequencedRecognizer_ = nullptr;
    auto parentNode = FrameNode::CreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    dragEventActuator->itemParentNode_ = parentNode;
    auto scrollablePatternDummy =
        FrameNode::GetOrCreateFrameNode(V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<PartiallyMockedScrollable>(); });
    ASSERT_NE(scrollablePatternDummy, nullptr);
    auto scrollablePatternDummyPattern = scrollablePatternDummy->GetPattern<PartiallyMockedScrollable>();
    ASSERT_NE(scrollablePatternDummyPattern, nullptr);
    std::vector<RefPtr<FrameNode>> childrenNull;
    std::vector<RefPtr<FrameNode>> children;
    children.emplace_back(framenode);
    children.emplace_back(framenode);
    parentNode->pattern_ = scrollablePatternDummy->GetPattern();
    NG::DragPreviewOption previewOptions;
    previewOptions.isMultiTiled = true;
    framenode->SetDragPreviewOptions(previewOptions);
    DragDropFuncWrapper::CreateTiledPixelMap(framenode);
    auto gestureHub = dragEventActuator->gestureEventHub_.Upgrade();
    ASSERT_NE(gestureHub, nullptr);
    previewOptions.isMultiTiled = false;
    framenode->SetDragPreviewOptions(previewOptions);
    dragEventActuator->isSelectedItemNode_ = true;
    DragDropFuncWrapper::CreateTiledPixelMap(framenode);
    EXPECT_EQ(gestureHub->pixelMap_, nullptr);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest046
 * @tc.desc: Create DragEventActuator and invoke CreateTiledPixelMap function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest046, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    gestureEventHub->contextMenuShowStatus_ = true;
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    ASSERT_NE(getEventTargetImpl, nullptr);
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    auto focusHub = framenode->GetOrCreateFocusHub();
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    GestureEventFunc actionStart = [&unknownPropertyValue](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = [&unknownPropertyValue]() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionStart), std::move(actionStart), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    dragEventActuator->SequencedRecognizer_ = nullptr;
    auto parentNode = FrameNode::CreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    dragEventActuator->itemParentNode_ = parentNode;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> tiledPixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(tiledPixelMap, nullptr);
    std::vector<RefPtr<FrameNode>> children;
    Rect pixelMapRect;
    DragDropFuncWrapper::DrawTiledPixelMap(tiledPixelMap, children, pixelMapRect);
    EXPECT_TRUE(children.empty());
    children.emplace_back(framenode);
    children.emplace_back(framenode);
    for (auto& node : children) {
        auto gestureHub = node->GetOrCreateGestureEventHub();
        ASSERT_NE(gestureHub, nullptr);
        gestureHub->dragPreviewPixelMap_ = tiledPixelMap;
    }
    DragDropFuncWrapper::DrawTiledPixelMap(tiledPixelMap, children, pixelMapRect);
    EXPECT_FALSE(children.empty());
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest047
 * @tc.desc: Create DragEventActuator and invoke CreateTiledPixelMap function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest047, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    gestureEventHub->contextMenuShowStatus_ = true;
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    ASSERT_NE(getEventTargetImpl, nullptr);
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    auto focusHub = framenode->GetOrCreateFocusHub();
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    GestureEventFunc actionStart = [&unknownPropertyValue](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = [&unknownPropertyValue]() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionStart), std::move(actionStart), std::move(actionCancel));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    dragEventActuator->SetCustomDragEvent(dragEvent);
    dragEventActuator->SequencedRecognizer_ = nullptr;
    auto parentNode = FrameNode::CreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    dragEventActuator->itemParentNode_ = parentNode;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> tiledPixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(tiledPixelMap, nullptr);
    std::vector<RefPtr<FrameNode>> children;
    children.emplace_back(framenode);
    children.emplace_back(framenode);
    for (auto& node : children) {
        auto gestureHub = node->GetOrCreateGestureEventHub();
        ASSERT_NE(gestureHub, nullptr);
        gestureHub->SetDragPreviewPixelMap(tiledPixelMap);
    }
    EXPECT_EQ(DragDropFuncWrapper::GetTiledPixelMapInfo(children), nullptr);
}

/**
 * @tc.name: DragEventActuatorDragGestureTest001
 * @tc.desc: Create DragEventActuator and invoke OnCollectTouchTarget function, then test recognizer callback.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorDragGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragEventActuator and collect drag event.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    GestureEventFunc actionStart = [&unknownPropertyValue](
                                       GestureEvent& info) { unknownPropertyValue = GESTURE_EVENT_PROPERTY_VALUE; };
    GestureEventFunc actionLongPress = [&unknownPropertyValue](
                                           GestureEvent& info) { unknownPropertyValue = GESTURE_EVENT_PROPERTY_VALUE; };
    GestureEventNoParameter actionCancel = [&unknownPropertyValue]() {
        unknownPropertyValue = GESTURE_EVENT_PROPERTY_VALUE;
    };
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), std::move(actionStart), std::move(actionStart), std::move(actionCancel));
    dragEvent->SetLongPressEventFunc(std::move(actionLongPress));
    dragEventActuator->ReplaceDragEvent(dragEvent);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    ASSERT_NE(dragEventActuator->panRecognizer_->onActionCancel_, nullptr);
    ASSERT_NE(dragEventActuator->longPressRecognizer_->onAction_, nullptr);
    ASSERT_NE(dragEventActuator->SequencedRecognizer_->onActionCancel_, nullptr);

    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    /**
     * @tc.steps: step2. call actionCancel function.
     */
    GestureEvent info = GestureEvent();
    (*(dragEventActuator->panRecognizer_->onActionCancel_))(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_DEFAULT_VALUE);
    frameNode->SetDraggable(false);
    (*(dragEventActuator->panRecognizer_->onActionCancel_))(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
    unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;

    /**
     * @tc.steps: step3. call sequenceCancel function.
     */
    dragEventActuator->longPressRecognizer_->refereeState_ = RefereeState::READY;
    (*(dragEventActuator->SequencedRecognizer_->onActionCancel_))(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_DEFAULT_VALUE);
    dragEventActuator->longPressRecognizer_->refereeState_ = RefereeState::SUCCEED;
    (*(dragEventActuator->SequencedRecognizer_->onActionCancel_))(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
    unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;

    /**
     * @tc.steps: step3. call longPressAction function.
     */
    dragEventActuator->isDragPrepareFinish_ = true;
    (*(dragEventActuator->longPressRecognizer_->onAction_))(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_DEFAULT_VALUE);
    dragEventActuator->isDragPrepareFinish_ = false;
    (*(dragEventActuator->longPressRecognizer_->onAction_))(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
}

/**
 * @tc.name: DragEventActuatorMountGatherNodeTest032
 * @tc.desc: Test UpdateGatherAnimatePosition function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorMountGatherNodeTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gatherNodeChildInfo
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step1. Test UpdateGatherAnimatePosition
     */
    std::vector<GatherNodeChildInfo> gatherNodeChildInfo(1);
    gatherNodeChildInfo[0].imageNode = frameNode;
    auto tempOffset = OffsetT<Dimension>(Dimension(0.0f), Dimension(0.0f));
    auto targetOffset = OffsetT<Dimension>(Dimension(COORDINATE_OFFSET.GetX()), Dimension(COORDINATE_OFFSET.GetY()));
    EXPECT_EQ(renderContext->GetPositionValue(tempOffset), tempOffset);
    DragEventActuator::UpdateGatherAnimatePosition(
        gatherNodeChildInfo, { COORDINATE_OFFSET.GetX(), COORDINATE_OFFSET.GetY() });
    EXPECT_EQ(renderContext->GetPositionValue(tempOffset), targetOffset);
}
} // namespace OHOS::Ace::NG