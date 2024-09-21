/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "test/unittest/core/event/gesture_event_hub_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void GestureEventHubTestCoverageNg::SetUpTestSuite()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    MOCK_DRAG_WINDOW = DragWindow::CreateDragWindow("", 0, 0, 0, 0);
    MOCK_TASK_EXECUTOR = AceType::MakeRefPtr<MockTaskExecutor>();
}

void GestureEventHubTestCoverageNg::TearDownTestSuite()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
    MOCK_DRAG_WINDOW = nullptr;
}

/**
 * @tc.name: GestureEventHubTestCoverage001
 * @tc.desc: test GetPreScaledPixelMapIfExist
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    bool result = true;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    gestureEventHub->GetPreScaledPixelMapIfExist(1.0f, pixelMap);
    gestureEventHub->GetPreScaledPixelMapIfExist(0.0f, pixelMap);
    gestureEventHub->dragEventActuator_->preScaledPixelMap_ = pixelMap;
    gestureEventHub->GetPreScaledPixelMapIfExist(1.0f, pixelMap);
    gestureEventHub->GetPreScaledPixelMapIfExist(0.0f, pixelMap);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GestureEventHubTestCoverage002
 * @tc.desc: test HandleOnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage002, TestSize.Level1)
{
    bool result = true;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    DragDropInfo dragDropInfo;
    dragDropInfo.customNode = customNode;
    dragDropInfo.inspectorId = "123";
    frameNode->SetDragPreview(dragDropInfo);

    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    auto onDragStart = [&customNode](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {
        DragDropInfo dragDropInfo;
        dragDropInfo.customNode = customNode;
        return dragDropInfo;
    };
    eventHub->SetOnDragStart(std::move(onDragStart));
    auto eventHubTwo = gestureEventHub->eventHub_.Upgrade();
    ASSERT_NE(eventHubTwo, nullptr);
    eventHubTwo->SetOnDragStart(std::move(onDragStart));
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetEventManager(eventManager);
    eventManager->SetLastMoveBeforeUp(false);
    GestureEvent gestureEvent;
    gestureEvent.SetSourceDevice(SourceType::TOUCH);
    gestureEvent.SetInputEventType(InputEventType::MOUSE_BUTTON);
    gestureEventHub->HandleOnDragStart(gestureEvent);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    gestureEventHub->dragEventActuator_->preScaledPixelMap_ = pixelMap;
    gestureEventHub->dragPreviewPixelMap_ = pixelMap;
    gestureEventHub->HandleOnDragStart(gestureEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GestureEventHubTestCoverage003
 * @tc.desc: test HandleOnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage003, TestSize.Level1)
{
    bool result = true;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    DragDropInfo dragDropInfo;
    dragDropInfo.customNode = customNode;
    frameNode->SetDragPreview(dragDropInfo);
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    auto onDragStart = [&customNode](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {
        DragDropInfo dragDropInfo;
        dragDropInfo.customNode = customNode;
        return dragDropInfo;
    };
    eventHub->SetOnDragStart(std::move(onDragStart));
    auto eventHubTwo = gestureEventHub->eventHub_.Upgrade();
    ASSERT_NE(eventHubTwo, nullptr);
    eventHubTwo->SetOnDragStart(std::move(onDragStart));
    frameNode->eventHub_ = eventHubTwo;
    eventHubTwo->AttachHost(frameNode);
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetEventManager(eventManager);
    eventManager->SetLastMoveBeforeUp(false);

    GestureEvent gestureEvent;
    gestureEvent.SetSourceDevice(SourceType::TOUCH);
    gestureEvent.SetInputEventType(InputEventType::MOUSE_BUTTON);
    gestureEventHub->HandleOnDragStart(gestureEvent);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    dragDropInfo.pixelMap = pixelMap;
    frameNode->SetDragPreview(dragDropInfo);
    gestureEventHub->dragEventActuator_->preScaledPixelMap_ = pixelMap;
    gestureEventHub->HandleOnDragStart(gestureEvent);
    gestureEventHub->dragPreviewPixelMap_ = pixelMap;
    gestureEventHub->HandleOnDragStart(gestureEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GestureEventHubTestCoverage004
 * @tc.desc: test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage004, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto childNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(childNode, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto patternNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->AddChild(childNode);
    DragDropInfo dragDropInfo;
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    GestureEvent gestureEvent;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    dragDropInfo.pixelMap = pixelMap;
    frameNode->SetDragPreview(dragDropInfo);
    gestureEventHub->dragEventActuator_->preScaledPixelMap_ = pixelMap;
    gestureEventHub->dragPreviewPixelMap_ = pixelMap;
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto dragDropProxy = AceType::MakeRefPtr<DragDropProxy>(101);
    gestureEventHub->dragDropProxy_ = dragDropProxy;
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    textPattern->dragRecordSize_ = 1;
    frameNode->pattern_ = textPattern;
    frameNode->GetOrCreateFocusHub();
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    auto overlayManager = mainPipeline->GetOverlayManager();
    overlayManager->pixmapColumnNodeWeak_ = WeakPtr<FrameNode>(AceType::DynamicCast<FrameNode>(frameNode));
    gestureEventHub->OnDragStart(gestureEvent, pipeline, frameNode, dragDropInfo, event);
    gestureEventHub->dragEventActuator_->itemParentNode_ = patternNode;
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    patternNode->pattern_ = mockPn;
    gestureEventHub->dragEventActuator_->isSelectedItemNode_ = true;
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    dragDropInfo.pixelMap = pixmap;
    EXPECT_CALL(*pixmap, GetWidth()).WillRepeatedly(Return(200));
    gestureEvent.inputEventType_ = InputEventType::MOUSE_BUTTON;
    auto mock = AceType::DynamicCast<MockInteractionInterface>(InteractionInterface::GetInstance());
    if (mock->gDragOutCallback) {
        mock->gDragOutCallback();
    }
    gestureEventHub->OnDragStart(gestureEvent, pipeline, frameNode, dragDropInfo, event);
    EXPECT_EQ(gestureEvent.inputEventType_, InputEventType::MOUSE_BUTTON);
}

/**
 * @tc.name: GestureEventHubTestCoverage005
 * @tc.desc: test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage005, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto childNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(childNode, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AddChild(childNode);
    DragDropInfo dragDropInfo;
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    GestureEvent gestureEvent;
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    event->SetData(unifiedData);
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    frameNode->pattern_ = textPattern;
    frameNode->GetOrCreateFocusHub();
    gestureEventHub->dragEventActuator_->isSelectedItemNode_ = true;
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    dragDropInfo.pixelMap = pixmap;
    frameNode->SetDragPreview(dragDropInfo);
    gestureEventHub->dragEventActuator_->preScaledPixelMap_ = pixmap;
    EXPECT_CALL(*pixmap, GetWidth()).WillRepeatedly(Return(200));
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    auto overlayManager = mainPipeline->GetOverlayManager();
    overlayManager->pixmapColumnNodeWeak_ = WeakPtr<FrameNode>(AceType::DynamicCast<FrameNode>(frameNode));
    gestureEventHub->textDraggable_ = true;
    gestureEventHub->OnDragStart(gestureEvent, pipeline, frameNode, dragDropInfo, event);
    textPattern->dragNode_ = childNode;
    gestureEventHub->OnDragStart(gestureEvent, pipeline, frameNode, dragDropInfo, event);
    EXPECT_EQ(gestureEventHub->textDraggable_, true);
}

/**
 * @tc.name: GestureEventHubTestCoverage006
 * @tc.desc: test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage006, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto childNode = AceType::MakeRefPtr<FrameNode>(V2::WEB_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(childNode, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::WEB_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AddChild(childNode);
    DragDropInfo dragDropInfo;
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    GestureEvent gestureEvent;
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    event->SetData(unifiedData);
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    frameNode->pattern_ = textPattern;
    frameNode->GetOrCreateFocusHub();
    gestureEventHub->dragEventActuator_->isSelectedItemNode_ = true;
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    dragDropInfo.pixelMap = pixmap;
    frameNode->SetDragPreview(dragDropInfo);
    gestureEventHub->dragEventActuator_->preScaledPixelMap_ = pixmap;
    EXPECT_CALL(*pixmap, GetWidth()).WillRepeatedly(Return(200));
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    auto overlayManager = mainPipeline->GetOverlayManager();
    overlayManager->pixmapColumnNodeWeak_ = WeakPtr<FrameNode>(AceType::DynamicCast<FrameNode>(frameNode));
    gestureEventHub->textDraggable_ = true;
    gestureEventHub->OnDragStart(gestureEvent, pipeline, frameNode, dragDropInfo, event);
    EXPECT_EQ(gestureEventHub->textDraggable_, true);
}

/**
 * @tc.name: GestureEventHubTestCoverage007
 * @tc.desc: test CheckClickActuator
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage007, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->parallelCombineClick = true;
    GestureEventFunc gestureEventFunc = [](GestureEvent& info) {};
    gestureEventHub->SetJSFrameNodeOnClick(std::move(gestureEventFunc));
    gestureEventHub->CheckClickActuator();
    EXPECT_EQ(gestureEventHub->parallelCombineClick, true);
}

/**
 * @tc.name: GestureEventHubTestCoverage008
 * @tc.desc: test ClearJSFrameNodeOnClick
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage008, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->ClearJSFrameNodeOnClick();
    EXPECT_EQ(gestureEventHub->touchEventActuator_, nullptr);
}

/**
 * @tc.name: GestureEventHubTestCoverage009
 * @tc.desc: test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage009, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto childNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto patternNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->AddChild(childNode);
    DragDropInfo dragDropInfo;
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    GestureEvent gestureEvent;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    dragDropInfo.pixelMap = pixelMap;
    frameNode->SetDragPreview(dragDropInfo);
    gestureEventHub->dragEventActuator_->preScaledPixelMap_ = pixelMap;
    gestureEventHub->dragPreviewPixelMap_ = pixelMap;
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto dragDropProxy = AceType::MakeRefPtr<DragDropProxy>(101);
    gestureEventHub->dragDropProxy_ = dragDropProxy;
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    textPattern->dragRecordSize_ = 1;
    frameNode->pattern_ = textPattern;
    frameNode->GetOrCreateFocusHub();
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    auto overlayManager = mainPipeline->GetOverlayManager();
    overlayManager->pixmapColumnNodeWeak_ = WeakPtr<FrameNode>(AceType::DynamicCast<FrameNode>(frameNode));
    gestureEventHub->OnDragStart(gestureEvent, pipeline, frameNode, dragDropInfo, event);
    gestureEventHub->dragEventActuator_->itemParentNode_ = patternNode;
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    patternNode->pattern_ = mockPn;
    gestureEventHub->dragEventActuator_->isSelectedItemNode_ = true;
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    dragDropInfo.pixelMap = pixmap;
    EXPECT_CALL(*pixmap, GetWidth()).WillRepeatedly(Return(200));
    gestureEvent.inputEventType_ = InputEventType::MOUSE_BUTTON;
    auto mock = AceType::DynamicCast<MockInteractionInterface>(InteractionInterface::GetInstance());
    if (mock->gDragOutCallback) {
        mock->gDragOutCallback();
    }
    mock->gStartDrag = 1;
    gestureEventHub->OnDragStart(gestureEvent, pipeline, frameNode, dragDropInfo, event);
    mock->gStartDrag = 0;
    EXPECT_EQ(gestureEvent.inputEventType_, InputEventType::MOUSE_BUTTON);
}

} // namespace OHOS::Ace::NG