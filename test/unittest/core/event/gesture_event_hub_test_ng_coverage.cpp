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

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_interaction_interface.h"
#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"

#include "frameworks/core/components_ng/pattern/text/text_pattern.h"

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
    gestureEventHub->SetFrameNodeCommonOnClick(std::move(gestureEventFunc));
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

/**
 * @tc.name: GestureEventHubTestCoverage010
 * @tc.desc: test GetDefaultPixelMapScale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gestureEventHub, gestureEvent and pixelMap.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    GestureEvent gestureEvent;
    gestureEvent.SetSourceDevice(SourceType::TOUCH);
    gestureEvent.SetInputEventType(InputEventType::MOUSE_BUTTON);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);

    /**
     * @tc.steps: step2. test default mouse scale.
     */
    auto defaultScale = gestureEventHub->GetDefaultPixelMapScale(frameNode, gestureEvent, false, pixelMap);
    EXPECT_EQ(defaultScale, 1.0f);

    /**
     * @tc.steps: step3. test default touch scale.
     */
    gestureEvent.SetInputEventType(InputEventType::TOUCH_SCREEN);
    defaultScale = gestureEventHub->GetDefaultPixelMapScale(frameNode, gestureEvent, false, pixelMap);
    EXPECT_EQ(defaultScale, 1.05f);

    /**
     * @tc.steps: step4. test menu scale.
     */
    gestureEventHub->menuPreviewScale_ = 2.0f;
    defaultScale = gestureEventHub->GetDefaultPixelMapScale(frameNode, gestureEvent, true, pixelMap);
    EXPECT_EQ(defaultScale, 2.0f);
}

/**
 * @tc.name: GestureEventHubTestCoverage011
 * @tc.desc: test GetPreScaledPixelMapIfExist
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage011, TestSize.Level1)
{
    DragDropInfo dragDropInfo;
    dragDropInfo.onlyForLifting = true;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->SetDragPreview(dragDropInfo);
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    gestureEventHub->InitDragDropEvent();
    EXPECT_EQ(gestureEventHub->GetPreScaledPixelMapIfExist(0.0f, pixelMap), pixelMap);
}

/**
 * @tc.name: GestureEventHubTestCoverage012
 * @tc.desc: test GetDefaultPixelMapScale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gestureEventHub, gestureEvent and pixelMap.
     */
    DragDropInfo dragDropInfo;
    dragDropInfo.onlyForLifting = true;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->SetDragPreview(dragDropInfo);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    GestureEvent gestureEvent;
    gestureEvent.SetSourceDevice(SourceType::TOUCH);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);

    /**
     * @tc.steps: step4. test onlyForLifting.
     */
    gestureEventHub->menuPreviewScale_ = 2.0f;
    auto defaultScale = gestureEventHub->GetDefaultPixelMapScale(frameNode, gestureEvent, true, pixelMap);
    EXPECT_EQ(defaultScale, 1.05f);
}

/**
 * @tc.name: GestureEventHubTestCoverage013
 * @tc.desc: Test GetDragDropInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    SystemProperties::dragDropFrameworkStatus_ = 3;

    /**
     * @tc.steps: step2. set onDragStart for eventHub
     */
    auto onDragStart = [](const RefPtr<OHOS::Ace::DragEvent>& dragEvent, const std::string& /* param */) {
        DragDropInfo dragDropInfo;
        auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
        dragEvent->SetData(unifiedData);
        auto customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
        dragDropInfo.customNode = customNode;
        dragDropInfo.extraInfo = "user set extraInfo";
        return dragDropInfo;
    };
    eventHub->SetOnDragStart(std::move(onDragStart));

    /**
     * @tc.steps: step3. set dragPreview for frameNode
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(frameNode, nullptr);
    DragDropInfo dragPreviewDropInfo;
    dragPreviewDropInfo.extraInfo = "drag preview extraInfo";
    auto customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragPreviewDropInfo.customNode = customNode;
    auto buildFunc = [node = customNode]() -> RefPtr<NG::UINode> { return AceType::DynamicCast<NG::UINode>(node); };
    dragPreviewDropInfo.buildFunc = buildFunc;
    dragPreviewDropInfo.onlyForLifting = true;
    dragPreviewDropInfo.delayCreating = false;
    frameNode->SetDragPreview(dragPreviewDropInfo);

    /**
     * @tc.steps: step4. call GetDragDropInfo function
     *            case: textDraggable is false, and component is image
     * @tc.expected: dragPreviewInfo.customNode is not null, extraInfo is 'drag preview extraInfo'.
     */
    GestureEvent info;
    DragDropInfo dragPreviewInfo;
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    gestureEventHub->SetTextDraggable(true);
    info.SetInputEventType(InputEventType::MOUSE_BUTTON);
    auto dragDropInfo = gestureEventHub->GetDragDropInfo(info, frameNode, dragPreviewInfo, dragEvent);
    EXPECT_TRUE(dragDropInfo.customNode);
    EXPECT_EQ(dragDropInfo.extraInfo, "user set extraInfo");
    EXPECT_FALSE(dragPreviewInfo.customNode);
    EXPECT_NE(dragPreviewInfo.customNode, buildFunc());
}

/**
 * @tc.name: GestureEventHubTestCoverage014
 * @tc.desc: Test GetDragDropInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. set onDragStart for eventHub
     */
    auto onDragStart = [](const RefPtr<OHOS::Ace::DragEvent>& dragEvent, const std::string& /* param */) {
        DragDropInfo dragDropInfo;
        auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
        dragEvent->SetData(unifiedData);
        auto customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
        dragDropInfo.customNode = customNode;
        dragDropInfo.extraInfo = "user set extraInfo";
        return dragDropInfo;
    };
    eventHub->SetOnDragStart(std::move(onDragStart));

    /**
     * @tc.steps: step3. set dragPreview for frameNode
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(frameNode, nullptr);
    DragDropInfo dragPreviewDropInfo;
    dragPreviewDropInfo.extraInfo = "drag preview extraInfo";
    auto customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragPreviewDropInfo.customNode = nullptr;
    auto buildFunc = [node = customNode]() -> RefPtr<NG::UINode> { return AceType::DynamicCast<NG::UINode>(node); };
    dragPreviewDropInfo.buildFunc = buildFunc;
    dragPreviewDropInfo.onlyForLifting = false;
    dragPreviewDropInfo.delayCreating = true;
    frameNode->SetDragPreview(dragPreviewDropInfo);

    /**
     * @tc.steps: step4. call GetDragDropInfo function
     *            case: textDraggable is false, and component is image
     * @tc.expected: dragPreviewInfo.customNode is not null, extraInfo is 'drag preview extraInfo'.
     */
    GestureEvent info;
    DragDropInfo dragPreviewInfo;
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    gestureEventHub->SetTextDraggable(true);
    info.SetInputEventType(InputEventType::MOUSE_BUTTON);
    auto dragDropInfo = gestureEventHub->GetDragDropInfo(info, frameNode, dragPreviewInfo, dragEvent);
    EXPECT_TRUE(dragDropInfo.customNode);
    EXPECT_EQ(dragDropInfo.extraInfo, "user set extraInfo");
    EXPECT_TRUE(dragPreviewInfo.customNode);
    EXPECT_EQ(dragPreviewInfo.customNode, buildFunc());
}

/**
 * @tc.name: GestureEventHubTestCoverage015
 * @tc.desc: test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCoverage015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
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

    /**
     * @tc.steps: step2. InitDragDropEvent.
     */
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    GestureEvent gestureEvent;
    char voidPtr[0];
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
    auto pipeline = PipelineContext::GetCurrentContext();
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    ASSERT_NE(mainPipeline, nullptr);
    auto overlayManager = mainPipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
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

    /**
     * @tc.steps: step3. set gestureEvent info, set MouseTransformEnable true.
     */
    gestureEvent.SetSourceTool(SourceTool::MOUSE);
    gestureEvent.SetSourceDevice(SourceType::TOUCH);
    AceApplicationInfo::GetInstance().SetMouseTransformEnable(true);

    /**
     * @tc.steps: step4. call OnDragStart function.
     *            case: GetSourceDevice is TOUCH, GetSourceTool is MOUSE, and MouseTransformEnable is true.
     * @tc.expected: branch is covered.
     */
    auto mock = AceType::DynamicCast<MockInteractionInterface>(InteractionInterface::GetInstance());
    ASSERT_NE(mock, nullptr);
    if (mock->gDragOutCallback) {
        mock->gDragOutCallback();
    }
    gestureEventHub->OnDragStart(gestureEvent, pipeline, frameNode, dragDropInfo, event);
    EXPECT_EQ(gestureEvent.inputEventType_, InputEventType::MOUSE_BUTTON);
    EXPECT_EQ(gestureEvent.GetSourceDevice(), SourceType::TOUCH);
    EXPECT_EQ(gestureEvent.GetSourceTool(), SourceTool::MOUSE);
}

/**
 * @tc.name: GestureEventHubTestCollectRecognizers001
 * @tc.desc: test ProcessParallelPriorityGesture
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestCoverageNg, GestureEventHubTestCollectRecognizers001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    Offset offset = Offset(0, 0);
    int32_t touchId = 0;
    RefPtr<TargetComponent> targetComponent = nullptr;
    RefPtr<FrameNode> host = nullptr;
    RefPtr<NGGestureRecognizer> current = nullptr;
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    std::list<RefPtr<NGGestureRecognizer>> recognizers { 1, clickRecognizer };
    int32_t parallelIndex = 0;
    std::vector<RefPtr<NGGestureRecognizer>> parallelVc;
    parallelVc.push_back(clickRecognizer);
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(parallelVc);

    gestureEventHub->externalParallelRecognizer_.push_back(parallelRecognizer);
    gestureEventHub->ProcessParallelPriorityGesture(
        offset, touchId, targetComponent, host, current, recognizers, parallelIndex);
    ASSERT_NE(gestureEventHub->externalParallelRecognizer_[parallelIndex], nullptr);
    auto touchPoint = gestureEventHub->externalParallelRecognizer_[parallelIndex]->GetTouchPoints();
    EXPECT_EQ(touchPoint.size(), 1);
    EXPECT_EQ(parallelIndex, 0);
    EXPECT_EQ(current, clickRecognizer);
}
} // namespace OHOS::Ace::NG