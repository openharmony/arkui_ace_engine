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

#include "test/unittest/core/event/gesture_event_hub_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: GetHitTestModeStr
 * @tc.desc: Test GetHitTestModeStr001
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetHitTestModeStr001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 101, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    auto eventHub = guestureEventHub->eventHub_.Upgrade();
    auto pipline = PipelineContext::GetCurrentContext();
    auto EventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EventHub->CancelDragForWeb();
    string testModeStr;
    /**
     * @tc.steps: step1. Calling the GetHitTestModeStr interface
     * @tc.expected: EventHub ->GetHitTestModeStr() is not equal to nullptr
     */
    EXPECT_TRUE(testModeStr != EventHub->GetHitTestModeStr());
}

/**
 * @tc.name: HandleOnDragUpdate001
 * @tc.desc: Test Functions related with drag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, HandleOnDragUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create guestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("MyButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    auto eventHub = guestureEventHub->eventHub_.Upgrade();
    eventHub->AttachHost(frameNode);
    ASSERT_NE(eventHub, nullptr);

    auto pipline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipline, nullptr);

    /**
     * @tc.steps: step2. call HandleOnDragStart
     *            case: eventHub->HasOnDragStart() is null
     * @tc.expected: dragDropProxy_ is null.
     */
    GestureEvent info;
    info.SetSourceDevice(SourceType::MOUSE);
    guestureEventHub->HandleOnDragStart(info);
    EXPECT_EQ(guestureEventHub->dragDropProxy_, nullptr);
    /**
     * @tc.steps: step3. set OnDragStart for eventHub
     *            after that eventHub->HasOnDragStart() is not null
     *            case: dragDropInfo.customNode is not null
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto onDragStart = [&customNode](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {
        DragDropInfo dragDropInfo;
        dragDropInfo.customNode = customNode;
        return dragDropInfo;
    };
    eventHub->SetOnDragStart(std::move(onDragStart));

    /**
     * @tc.steps: step4. call HandleOnDragStart
     *            case: dragDropInfo.customNode is not null
     * @tc.expected: dragDropProxy_ is null.
     */
    guestureEventHub->HandleOnDragStart(info);
    EXPECT_EQ(guestureEventHub->dragDropProxy_, nullptr);

    /**
     * @tc.steps: step5. call HandleOnDragEnd
     *            case: eventHub->HasOnDrop() is true
     * @tc.expected: dragDropProxy_ is null
     *               onDrop has been called, msg1 = CHECK_TAG_1
     */
    std::string msg1;
    auto onDrop = [&msg1](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */, const std::string& /* param */) {
        msg1 = CHECK_TAG_1;
    };
    eventHub->SetOnDrop(std::move(onDrop));
    guestureEventHub->HandleOnDragStart(info);
    guestureEventHub->HandleOnDragEnd(info);
    EXPECT_EQ(guestureEventHub->dragDropProxy_, nullptr);
    EXPECT_EQ(msg1, "HELLO");
}

/**
 * @tc.name: HandleOnDragUpdate002
 * @tc.desc: Test Functions related with drag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, HandleOnDragUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. update the input parameter attributes.
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    DragDropInfo dragDropInfo;
    dragDropInfo.customNode = customNode;
    frameNode->SetDragPreview(dragDropInfo);

    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    auto onDragStart = [&customNode](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {
        DragDropInfo dragDropInfo;
        dragDropInfo.customNode = customNode;
        return dragDropInfo;
    };
    eventHub->SetOnDragStart(std::move(onDragStart));

    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetEventManager(eventManager);
    eventManager->SetLastMoveBeforeUp(false);

    /**
     * @tc.steps: step3. call HandleOnDragStart with SourceType::MOUSE and InputEventType::TOUCH_SCREEN.
     * @tc.expected: eventManager->IsLastMoveBeforeUp() the return value is false.
     */
    GestureEvent gestureEvent;
    gestureEvent.SetSourceDevice(SourceType::MOUSE);
    gestureEvent.SetInputEventType(InputEventType::MOUSE_BUTTON);
    gestureEventHub->HandleOnDragStart(gestureEvent);
    EXPECT_FALSE(eventManager->IsLastMoveBeforeUp());
}

/**
 * @tc.name: HandleOnDragUpdate003
 * @tc.desc: Test Functions related with drag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, HandleOnDragUpdate003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::WEB_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    auto eventHub = guestureEventHub->eventHub_.Upgrade();
    eventHub->AttachHost(frameNode);
    ASSERT_NE(eventHub, nullptr);

    auto pipline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipline, nullptr);

    pipline->SetupRootElement();
    pipline->onVisibleAreaChangeNodeIds_.clear();
    pipline->AddOnAreaChangeNode(frameNode->GetId());

    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto onDragStart = [&customNode](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {
        void* voidPtr = static_cast<void*>(new char[0]);
        RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
        DragDropInfo dragDropInfo;
        dragDropInfo.customNode = customNode;
        return dragDropInfo;
    };
    eventHub->SetOnDragStart(std::move(onDragStart));

    GestureEvent info;
    info.SetSourceDevice(SourceType::MOUSE);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    guestureEventHub->HandleOnDragStart(info);
    EXPECT_EQ(guestureEventHub->dragDropProxy_, nullptr);
}

/**
 * @tc.name: GestureEventHubTest032
 * @tc.desc: Test ProcessTouchTestHierarchy
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest032, TestSize.Level1)
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
     * @tc.steps: step2. call ProcessTouchTestHierarchy
     *            case: innerRecognizers & gestureHierarchy_ is empty, current is null
     * @tc.expected: finalResult is empty
     */
    TouchRestrict touchRestrict;
    std::list<RefPtr<NGGestureRecognizer>> innerTargets;
    TouchTestResult finalResult;
    TouchTestResult responseLinkResult;

    /**
     * @tc.steps: step3. call externalExclusiveRecognizer_
     *            case: innerRecognizers & gestureHierarchy_ is empty, current is null
     * @tc.expected: finalResult is empty
     */
    gestureEventHub->externalExclusiveRecognizer_.push_back(nullptr);
    gestureEventHub->externalParallelRecognizer_.push_back(nullptr);
    EXPECT_EQ(static_cast<int32_t>(gestureEventHub->externalExclusiveRecognizer_.size()), 1);
    EXPECT_EQ(static_cast<int32_t>(gestureEventHub->externalParallelRecognizer_.size()), 1);

    /**
     * @tc.steps: step4. call ProcessTouchTestHierarchy
     *            case: innerRecognizers & gestureHierarchy_ is empty, current is null
     * @tc.expected: finalResult is empty
     */
    gestureEventHub->ProcessTouchTestHierarchy(
        COORDINATE_OFFSET, touchRestrict, innerTargets, finalResult, TOUCH_ID, nullptr, responseLinkResult);
    EXPECT_TRUE(finalResult.empty());
}

/**
 * @tc.name: GetPixelMapScale001
 * @tc.desc: Test GetPixelMapScale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetPixelMapScale001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);

    /**
     * @tc.steps: step2. construct a dragDropProxy and update gestureEventHub attributes.
     */
    constexpr int64_t PROXY_ID_NOT_FIT = 101;
    auto dragDropProxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    gestureEventHub->dragDropProxy_ = dragDropProxy;

    /**
     * @tc.steps: step3. call HandleOnDragUpdate with GestureEvent.
     * @tc.expected: gestureEventHub->dragDropProxy_ is true.
     */
    GestureEvent info;
    gestureEventHub->HandleOnDragUpdate(info);

    /**
     * @tc.steps: step4. call GetPixelMapScale.
     * @tc.expected: scale is true.
     */
    const int32_t height = 600.0f;
    const int32_t width = 500.0f;
    float scale = gestureEventHub->GetPixelMapScale(height, width);
    EXPECT_TRUE(scale);
}

/**
 * @tc.name: IsPixelMapNeedScale001
 * @tc.desc: Test IsPixelMapNeedScale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, IsPixelMapNeedScale001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create guestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("mybutton", -1, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    auto eventHub = guestureEventHub->eventHub_.Upgrade();
    eventHub->AttachHost(frameNode);
    ASSERT_NE(eventHub, nullptr);

    auto pipline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipline, nullptr);

    void* voidPtr2 = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap2 = PixelMap::CreatePixelMap(voidPtr2);
    guestureEventHub->SetPixelMap(pixelMap2);

    bool result = guestureEventHub->IsPixelMapNeedScale();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetDragDropInfo001
 * @tc.desc: Test GetDragDropInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetDragDropInfo001, TestSize.Level1)
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
     * @tc.steps: step2. set defaultOnDragStart for eventHub
     */
    auto defaultOnDragStart = [](const RefPtr<OHOS::Ace::DragEvent>& dragEvent, const std::string& /* param */) {
        DragDropInfo dragDropInfo;
        auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
        dragEvent->SetData(unifiedData);
        dragDropInfo.extraInfo = "default extraInfo";
        return dragDropInfo;
    };
    eventHub->SetDefaultOnDragStart(std::move(defaultOnDragStart));

    /**
     * @tc.steps: step3. call GetDragDropInfo function
     *            case: textDraggable is false, and component is text
     * @tc.expected: customNode is null, extraInfo is 'default extraInfo'.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    GestureEvent info;
    DragDropInfo dragPreviewInfo;
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto dragDropInfo = gestureEventHub->GetDragDropInfo(info, frameNode, dragPreviewInfo, dragEvent);
    EXPECT_FALSE(dragDropInfo.customNode);
    EXPECT_EQ(dragDropInfo.extraInfo, "default extraInfo");

    /**
     * @tc.steps: step4. call GetDragDropInfo function
     *            case: textDraggable is true, and component is text
     * @tc.expected: customNode is null, extraInfo is 'default extraInfo'.
     */
    gestureEventHub->SetTextDraggable(true);
    dragDropInfo = gestureEventHub->GetDragDropInfo(info, frameNode, dragPreviewInfo, dragEvent);
    EXPECT_FALSE(dragDropInfo.customNode);
    EXPECT_EQ(dragDropInfo.extraInfo, "default extraInfo");

    /**
     * @tc.steps: step5. set onDragStart for eventHub
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
     * @tc.steps: step6. call GetDragDropInfo function
     *            case: textDraggable is true, and component is text
     * @tc.expected: customNode is null, extraInfo is 'user set extraInfo'.
     */
    dragDropInfo = gestureEventHub->GetDragDropInfo(info, frameNode, dragPreviewInfo, dragEvent);
    EXPECT_FALSE(dragDropInfo.customNode);
    EXPECT_EQ(dragDropInfo.extraInfo, "user set extraInfo");
}

/**
 * @tc.name: GetDragDropInfo002
 * @tc.desc: Test GetDragDropInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetDragDropInfo002, TestSize.Level1)
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
    eventHub->SetOnDragStart(std::move(onDragStart));;

    /**
     * @tc.steps: step3. set dragPreview for frameNode
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(frameNode, nullptr);
    DragDropInfo dragPreviewDropInfo;
    dragPreviewDropInfo.extraInfo = "drag preview extraInfo";
    auto customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragPreviewDropInfo.customNode = customNode;
    frameNode->SetDragPreview(dragPreviewDropInfo);

    /**
     * @tc.steps: step4. call GetDragDropInfo function
     *            case: textDraggable is false, and component is image
     * @tc.expected: dragPreviewInfo.customNode is not null, extraInfo is 'drag preview extraInfo'.
     */
    GestureEvent info;
    DragDropInfo dragPreviewInfo;
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto dragDropInfo = gestureEventHub->GetDragDropInfo(info, frameNode, dragPreviewInfo, dragEvent);
    EXPECT_TRUE(dragDropInfo.customNode);
    EXPECT_EQ(dragDropInfo.extraInfo, "user set extraInfo");
    EXPECT_TRUE(dragPreviewInfo.customNode);
    EXPECT_EQ(dragPreviewInfo.extraInfo, "drag preview extraInfo");
}

/**
 * @tc.name: GetUnifiedData001
 * @tc.desc: Test GetUnifiedData function when user has not set the onDragStart callback.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetUnifiedData001, TestSize.Level1)
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
     * @tc.steps: step2. set OnDragStart for eventHub
     *            case: user not set onDragStart callback function
     */
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto defaultOnDragStart = [](const RefPtr<OHOS::Ace::DragEvent>& dragEvent, const std::string& /* param */) {
        DragDropInfo dragDropInfo;
        auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
        dragEvent->SetData(unifiedData);
        dragDropInfo.extraInfo = "default extraInfo";
        return dragDropInfo;
    };
    eventHub->SetDefaultOnDragStart(std::move(defaultOnDragStart));
    EXPECT_TRUE(eventHub->GetDefaultOnDragStart());

    /**
     * @tc.steps: step3. Call GetUnifiedData function
     *            case: Do not set default onDragStart function
     * @tc.expected: unifiedData is not null, extraInfo is not empty.
     */
    DragDropInfo dragDropInfo;
    gestureEventHub->GetUnifiedData("", dragDropInfo, dragEvent);
    EXPECT_TRUE(dragEvent->GetData());
    EXPECT_EQ(dragDropInfo.extraInfo, "default extraInfo");

    /**
     * @tc.steps: step4. Call GetUnifiedData function
     *            case: Do not set default onDragStart function
     * @tc.expected: unifiedData is not null, extraInfo is not empty.
     */
    dragEvent->SetData(nullptr);
    dragDropInfo.extraInfo = "";
    eventHub->SetDefaultOnDragStart(nullptr);
    gestureEventHub->GetUnifiedData("", dragDropInfo, dragEvent);
    EXPECT_EQ(dragEvent->GetData(), nullptr);
    EXPECT_EQ(dragDropInfo.extraInfo, "");
}

/**
 * @tc.name: GetUnifiedData002
 * @tc.desc: Test GetUnifiedData function when user set the onDragStart callback.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetUnifiedData002, TestSize.Level1)
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
     * @tc.steps: step2. set OnDragStart for eventHub
     *            case: set user set onDragStart and defaultOnDragStart
     */
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto defaultOnDragStart = [](const RefPtr<OHOS::Ace::DragEvent>& dragEvent, const std::string& /* param */) {
        DragDropInfo dragDropInfo;
        auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
        dragEvent->SetData(unifiedData);
        dragDropInfo.extraInfo = "default extraInfo";
        return dragDropInfo;
    };
    eventHub->SetDefaultOnDragStart(std::move(defaultOnDragStart));
    EXPECT_TRUE(eventHub->GetDefaultOnDragStart());

    /**
     * @tc.steps: step3. Call GetUnifiedData function
     *            case: user do not set unifiedData and extraInfo
     * @tc.expected: unifiedData is not null, extraInfo is not empty.
     */
    DragDropInfo dragDropInfo;
    gestureEventHub->GetUnifiedData("", dragDropInfo, dragEvent);
    EXPECT_TRUE(dragEvent->GetData());
    EXPECT_EQ(dragDropInfo.extraInfo, "default extraInfo");

    /**
     * @tc.steps: step4. set OnDragStart for eventHub
     *            case: user set onDragStart function
     */
    auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    dragEvent->SetData(unifiedData);
    dragDropInfo.extraInfo = "user set extraInfo";
    eventHub->SetDefaultOnDragStart(std::move(defaultOnDragStart));
    EXPECT_TRUE(eventHub->GetDefaultOnDragStart());

    /**
     * @tc.steps: step5. Call GetUnifiedData function
     *            case: user set unifiedData and extraInfo
     * @tc.expected: unifiedData is not null, extraInfo is not empty.
     */
    gestureEventHub->GetUnifiedData("", dragDropInfo, dragEvent);
    EXPECT_TRUE(dragEvent->GetData());
    EXPECT_EQ(dragDropInfo.extraInfo, "user set extraInfo");
}

/**
 * @tc.name: GestureEventHubNodeTest001
 * @tc.desc: Test SetJSFrameNodeOnClick and ClearJSFrameNodeOnClick.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubNodeTest001, TestSize.Level1)
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
     * @tc.steps: step2. Create GestureEventFunc and call SetJSFrameNodeOnClick.
     * @tc.expected: ClickEventActuator_ is not nullptr.
     */
    GestureEventFunc gestureEventFunc = [](GestureEvent& info) {};
    gestureEventHub->SetJSFrameNodeOnClick(std::move(gestureEventFunc));
    EXPECT_NE(gestureEventHub->clickEventActuator_, nullptr);

    /**
     * @tc.steps: step3. Set parallelCombineClick and call SetJSFrameNodeOnClick.
     * @tc.expected: userParallelClickEventActuator_ is not nullptr.
     */
    gestureEventHub->parallelCombineClick = true;
    gestureEventHub->SetJSFrameNodeOnClick(std::move(gestureEventFunc));
    EXPECT_NE(gestureEventHub->userParallelClickEventActuator_, nullptr);

    /**
     * @tc.steps: step4. Call ClearJSFrameNodeOnClick.
     * @tc.expected: jsFrameNodeCallback_ is nullptr.
     */
    gestureEventHub->ClearJSFrameNodeOnClick();
    EXPECT_EQ(gestureEventHub->clickEventActuator_->jsFrameNodeCallback_, nullptr);
}

/**
 * @tc.name: GestureEventHubNodeTest002
 * @tc.desc: Test SetOnTouchEvent, SetJSFrameNodeOnTouchEvent and ClearJSFrameNodeOnClick.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubNodeTest002, TestSize.Level1)
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
     * @tc.steps: step2. Create touchEventFunc and call SetOnTouchEvent.
     * @tc.expected: ouchEventActuator_ is not nullptr.
     */
    TouchEventFunc touchEventFunc = [](TouchEventInfo& info) {};
    gestureEventHub->SetOnTouchEvent(std::move(touchEventFunc));
    gestureEventHub->SetJSFrameNodeOnTouchEvent(std::move(touchEventFunc));
    EXPECT_NE(gestureEventHub->touchEventActuator_, nullptr);

    /**
     * @tc.steps: step3. Call ClearJSFrameNodeOnTouch.
     * @tc.expected: commonTouchEventCallback_ is nullptr.
     */
    gestureEventHub->ClearJSFrameNodeOnTouch();
    EXPECT_EQ(gestureEventHub->touchEventActuator_->commonTouchEventCallback_, nullptr);
}

/**
 * @tc.name: TestSetDragGatherPixelMap001
 * @tc.desc: Test SetDragGatherPixelMap.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, TestSetDragGatherPixelMap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Grid Node.
     */
    auto gridNode = FrameNode::CreateFrameNode(
        V2::GRID_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(gridNode, nullptr);
    /**
     * @tc.steps: step2. Create Grid Item Node.
     */
    auto gridItemNode1 = FrameNode::CreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<GridItemPattern>(nullptr, GridItemStyle::NONE));
    ASSERT_NE(gridItemNode1, nullptr);
    auto gridItemNode2 = FrameNode::CreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<GridItemPattern>(nullptr, GridItemStyle::NONE));
    ASSERT_NE(gridItemNode2, nullptr);
    auto itemPattern1 = gridItemNode1->GetPattern<GridItemPattern>();
    ASSERT_NE(itemPattern1, nullptr);
    itemPattern1->SetSelected(true);
    auto itemPattern2 = gridItemNode2->GetPattern<GridItemPattern>();
    ASSERT_NE(itemPattern2, nullptr);
    itemPattern2->SetSelected(true);
    NG::DragPreviewOption option { true, false, true };
    gridItemNode1->SetDragPreviewOptions(option);
    gridNode->AddChild(gridItemNode1);
    gridNode->AddChild(gridItemNode2);
    /**
     * @tc.steps: step3. Create gestureEventHub and Test SetDragGatherPixelMap.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    GestureEvent info;
    info.SetInputEventType(InputEventType::MOUSE_BUTTON);
    gestureEventHub->SetDragGatherPixelMaps(info);
    /**
     * @tc.steps: step4. Get DragDropManager.
     */
    auto pipeline = PipelineContext::GetMainPipelineContext();
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    /**
     * @tc.steps: step5. Test SetDragGatherPixelMap result.
     */
    DragDataCore dragData;
    dragDropManager->GetGatherPixelMap(dragData, 1.0f);
    auto size = dragData.shadowInfos.size();
    EXPECT_EQ(size, 0);
}

/**
 * @tc.name: GestureEventHubModifierTest001
 * @tc.desc: Test modifier AttachGesture & RemoveGesture & ClearModifierGesture
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. call AttachGesture
     *            case: recreateGesture_ is true & modifierGestures_.size() != gestureHierarchy_.size()
     * @tc.expected: recreateGesture_ = false
     *               modifierGestures_ has one element & gestureHierarchy_ has one element
     */
    auto longPressGesture = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    gestureEventHub->AttachGesture(longPressGesture);
    EXPECT_FALSE(gestureEventHub->recreateGesture_);
    auto sizeModifierGestures = static_cast<int32_t>(gestureEventHub->modifierGestures_.size());
    auto sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeModifierGestures, 1);
    EXPECT_EQ(sizeGestureHierarchy, 1);

    /**
     * @tc.steps: step3. call RemoveGesture
     *            case: recreateGesture_ is true & modifierGestures_.size() != gestureHierarchy_.size()
     * @tc.expected: recreateGesture_ = false
     *               modifierGestures_ has zero element & gestureHierarchy_ has zero element
     */
    gestureEventHub->RemoveGesture(longPressGesture);
    EXPECT_FALSE(gestureEventHub->recreateGesture_);
    sizeModifierGestures = static_cast<int32_t>(gestureEventHub->modifierGestures_.size());
    sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeModifierGestures, 0);
    EXPECT_EQ(sizeGestureHierarchy, 0);

    /**
     * @tc.steps: step4. call AttachGesture & ClearModifierGesture
     *            case: recreateGesture_ is true & gestures_.size() != gestureHierarchy_.size()
     * @tc.expected: recreateGesture_ = false
     *               modifierGestures_ has cleared & gestureHierarchy_ has cleared
     */
    gestureEventHub->AttachGesture(longPressGesture);
    EXPECT_FALSE(gestureEventHub->recreateGesture_);
    sizeModifierGestures = static_cast<int32_t>(gestureEventHub->modifierGestures_.size());
    sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeModifierGestures, 1);
    EXPECT_EQ(sizeGestureHierarchy, 1);

    gestureEventHub->ClearModifierGesture();
    EXPECT_FALSE(gestureEventHub->recreateGesture_);
    sizeModifierGestures = static_cast<int32_t>(gestureEventHub->modifierGestures_.size());
    sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeModifierGestures, 0);
    EXPECT_EQ(sizeGestureHierarchy, 0);
}

/**
 * @tc.name: GestureEventHubModifierTest002
 * @tc.desc: Test modifier RemoveGesturesByTag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubModifierTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step4. call RemoveGesturesByTag
     * @tc.expected: recreateGesture_ = false
     *               modifierGestures_ one element & gestureHierarchy_ has one element & group has one child
     */
    std::vector<RefPtr<Gesture>> gestures;
    auto longPressGestureOne = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    longPressGestureOne->SetTag(CHECK_TAG_1);
    gestures.emplace_back(longPressGestureOne);
    auto longPressGestureTwo = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    gestures.emplace_back(longPressGestureTwo);
    auto group = AceType::MakeRefPtr<GestureGroup>(GestureMode::Exclusive, gestures);
    gestureEventHub->AttachGesture(group);
    EXPECT_FALSE(gestureEventHub->recreateGesture_);
    auto sizeModifierGestures = static_cast<int32_t>(gestureEventHub->modifierGestures_.size());
    auto sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeModifierGestures, 1);
    EXPECT_EQ(sizeGestureHierarchy, 1);

    gestureEventHub->RemoveGesturesByTag(CHECK_TAG_1);
    EXPECT_FALSE(gestureEventHub->recreateGesture_);
    sizeModifierGestures = static_cast<int32_t>(gestureEventHub->modifierGestures_.size());
    sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeModifierGestures, 1);
    EXPECT_EQ(sizeGestureHierarchy, 1);
    EXPECT_EQ(group->gestures_.size(), 1);
}


/**
 * @tc.name: GestureEventHubTest033
 * @tc.desc: Test ClickEventActuator AddClickAfterEvent.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    auto clickCallback = [](GestureEvent& info) {};
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    guestureEventHub->AddClickAfterEvent(clickEvent);
    EXPECT_NE(guestureEventHub->GetClickEvent(), nullptr);
}

/**
 * @tc.name: UpdateExtraInfoTest001
 * @tc.desc: Test UpdateExtraInfo function
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, UpdateExtraInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode、guestureEventHub.DragPreviewOption
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    Dimension dimen(2.0);
    BlurBackGroundInfo bgBackEffect = {{dimen, 1.0f, 1.0f, Color::TRANSPARENT,
        AdaptiveColor::DEFAULT, {{2.0f, 2.0f}}}};
    std::optional<Shadow> shadowVal;
    std::optional<BorderRadiusProperty> borderRadiusVal;
    OptionsAfterApplied optionTmp = {0, shadowVal, "test", borderRadiusVal, {bgBackEffect}};
    DragPreviewOption dragPreviewInfos;
    dragPreviewInfos.options = optionTmp;
    frameNode->SetDragPreviewOptions(dragPreviewInfos);
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    /**
     * @tc.steps: step2. Test UpdateExtraInfo
    */
    auto arkExtraInfoJson = JsonUtil::Create(true);
    guestureEventHub->UpdateExtraInfo(frameNode, arkExtraInfoJson, 1.0f);
    auto radiusJs = arkExtraInfoJson->GetDouble("blur_radius", -1);
    EXPECT_EQ(radiusJs, 2.0);
    /**
     * @tc.steps: step3. Test UpdateExtraInfo invalid
     */
    dragPreviewInfos.options.blurbgEffect.backGroundEffect.radius.SetValue(0);
    frameNode->SetDragPreviewOptions(dragPreviewInfos);
    auto jsInfos = JsonUtil::Create(true);
    guestureEventHub->UpdateExtraInfo(frameNode, jsInfos, 1.0f);
    radiusJs = jsInfos->GetDouble("blur_radius", -1);
    EXPECT_EQ(radiusJs, -1);
}
} // namespace OHOS::Ace::NG