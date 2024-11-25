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
    OptionsAfterApplied optionTmp = { 0, shadow, "test", borderRadius, { bgBackEffect } };
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
    OptionsAfterApplied optionTmp = { 0, shadow, "test", borderRadius, { bgBackEffect } };
    NG::DragPreviewOption previewOptions;
    previewOptions.options = optionTmp;
    frameNode->SetDragPreviewOptions(previewOptions);
    std::unique_ptr<JsonValue> arkExtraInfoJson = std::make_unique<JsonValue>();
    dragEventActuator->PrepareRadiusParametersForDragData(frameNode, arkExtraInfoJson);
    BorderRadiusProperty borderRadiusTwo;
    borderRadiusTwo.radiusBottomLeft = dimen;
    optionTmp = { 0, shadow, "test", borderRadiusTwo, { bgBackEffect } };
    previewOptions.options = optionTmp;
    frameNode->SetDragPreviewOptions(previewOptions);
    dragEventActuator->PrepareRadiusParametersForDragData(frameNode, arkExtraInfoJson);
    EXPECT_EQ(shadow.GetBlurRadius(), 10.0);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest033
 * @tc.desc: Create DragEventActuator and invoke OnCollectTouchTarget function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest033, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
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
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    GestureEvent info = GestureEvent();
    info.SetScale(GESTURE_EVENT_PROPERTY_VALUE);
    dragEventActuator->panRecognizer_->onActionCancel_ = std::make_unique<GestureEventNoParameter>(
        [&unknownPropertyValue]() {});
    (*(dragEventActuator->panRecognizer_->onActionCancel_))();
    dragEventActuator->panRecognizer_->deviceType_ = SourceType::MOUSE;
    (*(dragEventActuator->panRecognizer_->onActionCancel_))();
    gestureEventHub->textDraggable_ = true;
    (*(dragEventActuator->panRecognizer_->onActionCancel_))();
    auto onKeyEvent = [](const KeyEvent& event) -> bool { return true; };
    focusHub->SetOnKeyEventInternal(onKeyEvent, OnKeyEventType::CONTEXT_MENU);
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    (*(dragEventActuator->panRecognizer_->onActionCancel_))();
    (*(dragEventActuator->longPressRecognizer_->onAction_))(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_DEFAULT_VALUE);
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
    dragDropManager->SetPreDragStatus(PreDragStatus::PREVIEW_LANDING_STARTED);
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
    dragEventActuator->GetPreviewPixelMap("testid", frameNode);
    layoutProperty->propVisibility_ = VisibleType::GONE;
    dragEventActuator->GetPreviewPixelMap("testid", frameNode);
    layoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    dragEventActuator->GetPreviewPixelMap("testid", frameNode);
    EXPECT_EQ(gestureEventHub->GetTextDraggable(), true);
}

/**
 * @tc.name: DragEventActuatorUpdatePreviewAttrTest045
 * @tc.desc: Create DragEventActuator and invoke OnCollectTouchTarget function.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventActuatorUpdatePreviewAttrTest045, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
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
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    GestureEvent info = GestureEvent();
    info.SetScale(GESTURE_EVENT_PROPERTY_VALUE);
    (*(dragEventActuator->panRecognizer_->onReject_))();
    dragEventActuator->gatherNode_ = framenode;
    (*(dragEventActuator->panRecognizer_->onReject_))();
    dragEventActuator->isNotInPreviewState_ = true;
    (*(dragEventActuator->panRecognizer_->onReject_))();
    auto onKeyEvent = [](const KeyEvent& event) -> bool { return true; };
    focusHub->SetOnKeyEventInternal(onKeyEvent, OnKeyEventType::CONTEXT_MENU);
    dragEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    (*(dragEventActuator->panRecognizer_->onReject_))();
    dragEventActuator->isNotInPreviewState_ = false;
    (*(dragEventActuator->panRecognizer_->onReject_))();
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_DEFAULT_VALUE);
}
} // namespace OHOS::Ace::NG