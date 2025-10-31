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

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_interaction_interface.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "frameworks/core/components_ng/pattern/text/text_pattern.h"

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
    EXPECT_TRUE(testModeStr != GestureEventHub::GetHitTestModeStr(EventHub));
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
    ResponseLinkResult responseLinkResult;

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

    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1);
    innerTargets.emplace_back(clickRecognizer);

    gestureEventHub->ProcessTouchTestHierarchy(
        COORDINATE_OFFSET, touchRestrict, innerTargets, finalResult, TOUCH_ID, nullptr, responseLinkResult);
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
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
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
    gestureEventHub->InitDragDropEvent();
    ASSERT_NE(gestureEventHub->dragEventActuator_, nullptr);
    gestureEventHub->SetTextDraggable(true);
    info.SetInputEventType(InputEventType::MOUSE_BUTTON);
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

    gestureEventHub->InitDragDropEvent();
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
    gestureEventHub->InitDragDropEvent();
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
 * @tc.desc: Test SetFrameNodeCommonOnClick and ClearJSFrameNodeOnClick.
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
     * @tc.steps: step2. Create GestureEventFunc and call SetFrameNodeCommonOnClick.
     * @tc.expected: ClickEventActuator_ is not nullptr.
     */
    GestureEventFunc gestureEventFunc = [](GestureEvent& info) {};
    gestureEventHub->SetFrameNodeCommonOnClick(std::move(gestureEventFunc));
    EXPECT_NE(gestureEventHub->clickEventActuator_, nullptr);

    /**
     * @tc.steps: step3. Set parallelCombineClick and call SetFrameNodeCommonOnClick.
     * @tc.expected: userParallelClickEventActuator_ is not nullptr.
     */
    gestureEventHub->parallelCombineClick = true;
    gestureEventHub->SetFrameNodeCommonOnClick(std::move(gestureEventFunc));
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
 * @tc.desc: Test SetOnTouchEvent, SetFrameNodeCommonOnTouchEvent and ClearJSFrameNodeOnClick.
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
    gestureEventHub->SetFrameNodeCommonOnTouchEvent(std::move(touchEventFunc));
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
     * @tc.expected: modifierGestures_ has one element & gestureHierarchy_ has zero element
     */
    auto longPressGesture = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    gestureEventHub->AttachGesture(longPressGesture);
    auto sizeModifierGestures = static_cast<int32_t>(gestureEventHub->modifierGestures_.size());
    auto sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeModifierGestures, 1);
    EXPECT_EQ(sizeGestureHierarchy, 0);

    /**
     * @tc.steps: step3. call RemoveGesture
     *            case: recreateGesture_ is true & modifierGestures_.size() != gestureHierarchy_.size()
     * @tc.expected: modifierGestures_ has zero element & gestureHierarchy_ has zero element
     */
    gestureEventHub->RemoveGesture(longPressGesture);
    sizeModifierGestures = static_cast<int32_t>(gestureEventHub->modifierGestures_.size());
    sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeModifierGestures, 0);
    EXPECT_EQ(sizeGestureHierarchy, 0);

    /**
     * @tc.steps: step4. call AttachGesture & ClearModifierGesture
     *            case: recreateGesture_ is true & gestures_.size() != gestureHierarchy_.size()
     * @tc.expected: modifierGestures_ has cleared & gestureHierarchy_ has cleared
     */
    gestureEventHub->AttachGesture(longPressGesture);
    sizeModifierGestures = static_cast<int32_t>(gestureEventHub->modifierGestures_.size());
    sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeModifierGestures, 1);
    EXPECT_EQ(sizeGestureHierarchy, 0);

    gestureEventHub->ClearModifierGesture();
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
     * @tc.expected: modifierGestures_ one element & gestureHierarchy_ has zero element & group has one child
     */
    std::vector<RefPtr<Gesture>> gestures;
    auto longPressGestureOne = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    longPressGestureOne->SetTag(CHECK_TAG_1);
    gestures.emplace_back(longPressGestureOne);
    auto longPressGestureTwo = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    gestures.emplace_back(longPressGestureTwo);
    auto group = AceType::MakeRefPtr<GestureGroup>(GestureMode::Exclusive, gestures);
    gestureEventHub->AttachGesture(group);
    auto sizeModifierGestures = static_cast<int32_t>(gestureEventHub->modifierGestures_.size());
    auto sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeModifierGestures, 1);
    EXPECT_EQ(sizeGestureHierarchy, 0);

    gestureEventHub->RemoveGesturesByTag(CHECK_TAG_1);
    sizeModifierGestures = static_cast<int32_t>(gestureEventHub->modifierGestures_.size());
    sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeModifierGestures, 1);
    EXPECT_EQ(sizeGestureHierarchy, 0);
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
    OptionsAfterApplied optionTmp = {0, shadowVal, "test", true, borderRadiusVal, {bgBackEffect}};
    DragPreviewOption dragPreviewInfos;
    dragPreviewInfos.options = optionTmp;
    frameNode->SetDragPreviewOptions(dragPreviewInfos);
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    /**
     * @tc.steps: step2. Test UpdateExtraInfo
    */
    auto arkExtraInfoJson = JsonUtil::Create(true);
    PreparedInfoForDrag data;
    guestureEventHub->UpdateExtraInfo(frameNode, arkExtraInfoJson, 1.0f, data);
    auto radiusJs = arkExtraInfoJson->GetDouble("blur_radius", -1);
    EXPECT_EQ(radiusJs, 2.0);
    /**
     * @tc.steps: step3. Test UpdateExtraInfo invalid
     */
    dragPreviewInfos.options.blurbgEffect.backGroundEffect.radius.SetValue(0);
    frameNode->SetDragPreviewOptions(dragPreviewInfos);
    auto jsInfos = JsonUtil::Create(true);
    guestureEventHub->UpdateExtraInfo(frameNode, jsInfos, 1.0f, data);
    radiusJs = jsInfos->GetDouble("blur_radius", -1);
    EXPECT_EQ(radiusJs, -1);
}

/**
 * @tc.name: GestureEventHubAddGestureToGestureHierarchyTest001
 * @tc.desc: Test AddGestureToGestureHierarchy.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubAddGestureToGestureHierarchyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Invoke AddGestureToGestureHierarchy.
     * @tc.expected: gesture is null.
     */
    guestureEventHub->AddGestureToGestureHierarchy(nullptr, false);
}

/**
 * @tc.name: GestureEventHubGetPixelMapScaleTest001
 * @tc.desc: Test GetPixelMapScale.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubGetPixelMapScaleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Invoke GetPixelMapScale.
     * @tc.expected: height is 1 and width is 0.
     */
    auto scale = guestureEventHub->GetPixelMapScale(1, 0);
    EXPECT_EQ(scale, 1.0f);

    /**
     * @tc.steps: step2. Invoke GetPixelMapScale.
     * @tc.expected: height is 1 and width is 0.
     */
    scale = guestureEventHub->GetPixelMapScale(0, 1);
    EXPECT_EQ(scale, 1.0f);
}

/**
 * @tc.name: GestureEventHubGenerateMousePixelMapTest001
 * @tc.desc: Test GenerateMousePixelMap.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubGenerateMousePixelMapTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Invoke GenerateMousePixelMap.
     * @tc.expected: TextDraggable is true.
     */
    GestureEvent info = GestureEvent();
    auto frameNode2 = guestureEventHub->GetFrameNode();
    ASSERT_NE(frameNode2, nullptr);
    EXPECT_EQ(guestureEventHub->pixelMap_, nullptr);
    guestureEventHub->SetTextDraggable(true);
    guestureEventHub->GenerateMousePixelMap(info);
    EXPECT_EQ(guestureEventHub->pixelMap_, 0);
    
    /**
     * @tc.steps: step3. Invoke GenerateMousePixelMap.
     * @tc.expected: TextDraggable is false.
     */
    guestureEventHub->pixelMap_ = nullptr;
    guestureEventHub->SetTextDraggable(false);
    guestureEventHub->GenerateMousePixelMap(info);
    EXPECT_EQ(guestureEventHub->pixelMap_, 0);
}

/**
 * @tc.name: GestureEventHubCopyEventTest001
 * @tc.desc: Test CopyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubCopyEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub1 = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub1, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    eventHub1->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub1 = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub1)));
    ASSERT_NE(gestureEventHub1, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub1)), DRAG_DIRECTION, FINGERS_NUMBER, DRAG_DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    auto eventHub2 = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub2, nullptr);
    auto gestureEventHub2 = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub2)));
    ASSERT_NE(gestureEventHub2, nullptr);

    /**
     * @tc.steps: step2. Invoke CopyEvent.
     */
    gestureEventHub2->CopyEvent(gestureEventHub1);
    EXPECT_FALSE(gestureEventHub1->touchEventActuator_);
    EXPECT_FALSE(gestureEventHub1->clickEventActuator_);
    EXPECT_FALSE(gestureEventHub1->longPressEventActuator_);
    EXPECT_FALSE(gestureEventHub1->dragEventActuator_);
    EXPECT_FALSE(gestureEventHub1->showMenu_);

    /**
     * @tc.steps: step3. Invoke CopyEvent.
     */
    gestureEventHub1->touchEventActuator_ = AceType::MakeRefPtr<TouchEventActuator>();
    EXPECT_NE(gestureEventHub1->touchEventActuator_, nullptr);
    gestureEventHub1->clickEventActuator_ = AceType::MakeRefPtr<ClickEventActuator>(gestureEventHub1);
    EXPECT_NE(gestureEventHub1->clickEventActuator_, nullptr);
    gestureEventHub1->longPressEventActuator_ = AceType::MakeRefPtr<LongPressEventActuator>(gestureEventHub1);
    EXPECT_NE(gestureEventHub1->longPressEventActuator_, nullptr);
    gestureEventHub1->dragEventActuator_ = dragEventActuator;
    EXPECT_NE(gestureEventHub1->dragEventActuator_, nullptr);
    GestureEventFunc callback = [](GestureEvent& info) {};
    gestureEventHub1->showMenu_ = AceType::MakeRefPtr<ClickEvent>(std::move(callback));
    EXPECT_NE(gestureEventHub1->showMenu_, nullptr);
    EXPECT_FALSE(gestureEventHub2->showMenu_);
    gestureEventHub2->CopyEvent(gestureEventHub1);
    EXPECT_TRUE(gestureEventHub2->showMenu_);

    /**
     * @tc.steps: step4. Invoke CopyEvent.
     */
    gestureEventHub2->showMenu_ = AceType::MakeRefPtr<ClickEvent>(std::move(callback));
    gestureEventHub2->CopyEvent(gestureEventHub1);
    EXPECT_TRUE(gestureEventHub2->showMenu_);
}

/**
 * @tc.name: GestureEventHubIsNeedSwitchToSubWindowTest001
 * @tc.desc: Test IsNeedSwitchToSubWindow.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubIsNeedSwitchToSubWindowTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode1 = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    auto gestureEventHub = frameNode1->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Invoke IsNeedSwitchToSubWindow.
     * @tc.expected: gestureEventHub->IsPixelMapNeedScale() is false.
     */
    auto frameNode2 = gestureEventHub->GetFrameNode();
    EXPECT_NE(frameNode2, nullptr);
    frameNode2->GetOrCreateFocusHub();
    auto focusHub = frameNode2->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    PreparedInfoForDrag data;
    gestureEventHub->IsNeedSwitchToSubWindow(data);
    EXPECT_FALSE(gestureEventHub->IsPixelMapNeedScale());
}

/**
 * @tc.name: GestureEventHubSetDragGatherPixelMapsTest001
 * @tc.desc: Test SetDragGatherPixelMaps.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubSetDragGatherPixelMapsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub and DragEventActuator.
     * @tc.expected: dragEventActuator and gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DRAG_DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke SetDragGatherPixelMaps.
     */
    GestureEvent info = GestureEvent();
    gestureEventHub->dragEventActuator_ = dragEventActuator;
    gestureEventHub->SetDragGatherPixelMaps(info);
    EXPECT_TRUE(!dragEventActuator->IsNeedGather());
}

/**
 * @tc.name: GestureEventHubGetSelectItemSizeTest001
 * @tc.desc: Test GetSelectItemSize.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubGetSelectItemSizeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub and DragEventActuator.
     * @tc.expected: dragEventActuator and gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto framenode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(framenode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DRAG_DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke GetSelectItemSize.
     */
    gestureEventHub->dragEventActuator_ = dragEventActuator;
    gestureEventHub->GetSelectItemSize();
    EXPECT_TRUE(!gestureEventHub->dragEventActuator_->IsNeedGather());
}

/**
 * @tc.name: GestureEventHubNodeTest003
 * @tc.desc: Test SetOnTouchEvent, SetFrameNodeCommonOnTouchEvent and ClearJSFrameNodeOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubNodeTest003, TestSize.Level1)
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
     * @tc.expected: TouchEventActuator_ is nullptr.
     */
    TouchEventFunc touchEventFunc = [](TouchEventInfo& info) {};
    gestureEventHub->touchEventActuator_ = AceType::MakeRefPtr<TouchEventActuator>();
    gestureEventHub->SetOnTouchEvent(std::move(touchEventFunc));
    gestureEventHub->touchEventActuator_ = nullptr;
    gestureEventHub->SetOnTouchEvent(std::move(touchEventFunc));
    gestureEventHub->SetFrameNodeCommonOnTouchEvent(std::move(touchEventFunc));
    gestureEventHub->ClearJSFrameNodeOnTouch();
    EXPECT_NE(gestureEventHub->touchEventActuator_, nullptr);
}

/**
 * @tc.name: GestureEventHubNodeTest004
 * @tc.desc: ClearJSFrameNodeOnClick.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubNodeTest004, TestSize.Level1)
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
     * @tc.steps: step2. Call ClearJSFrameNodeOnClick.
     * @tc.expected: clickEventActuator_ is nullptr.
     */
    gestureEventHub->ClearJSFrameNodeOnClick();
    EXPECT_FALSE(gestureEventHub->clickEventActuator_);
}

/**
 * @tc.name: HandleOnDragUpdate004
 * @tc.desc: Test Functions related with drag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, HandleOnDragUpdate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("MyButton", 102, AceType::MakeRefPtr<Pattern>());
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto eventHub = gestureEventHub->eventHub_.Upgrade();
    eventHub->AttachHost(frameNode);
    ASSERT_NE(eventHub, nullptr);

    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. call HandleOnDragUpdate
     * @tc.expected: dragDropProxy_ is not null.
     */
    constexpr int64_t PROXY_ID_NOT_FIT = 101;
    auto dragDropProxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    gestureEventHub->dragDropProxy_ = dragDropProxy;
    GestureEvent info;
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->isDragged_ = true;
    gestureEventHub->HandleOnDragUpdate(info);
    EXPECT_TRUE(dragDropManager->IsDragged());
}

/**
 * @tc.name: GestureEventHubGetPixelMapOffset001
 * @tc.desc: Test GetPixelMapOffset
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubGetPixelMapOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode1 = FrameNode::CreateFrameNode("MyButton", 102, AceType::MakeRefPtr<Pattern>());
    auto gestureEventHub = frameNode1->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto eventHub = gestureEventHub->eventHub_.Upgrade();
    eventHub->AttachHost(frameNode1);
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps2: Invoke GetPixelMapOffset
     * @tc.expected: NearZero(gestureEventHub->frameNodeSize_.Width()) is true,
     * NearZero(size.Width()) is false.
     */
    constexpr float PIXELMAP_WIDTH_RATE = -0.5f;
    constexpr float PIXELMAP_HEIGHT_RATE = -0.2f;
    GestureEvent info = GestureEvent();
    auto size = SizeF(1, 1);
    PreparedInfoForDrag data;
    gestureEventHub->GetPixelMapOffset(info, size, data, 1.0f);
    auto frameNode2 = gestureEventHub->GetFrameNode();
    EXPECT_NE(frameNode2, nullptr);
    OffsetF result = OffsetF(size.Width() * PIXELMAP_WIDTH_RATE, size.Height() * PIXELMAP_HEIGHT_RATE);
    EXPECT_TRUE(NearZero(gestureEventHub->frameNodeSize_.Width()));
    EXPECT_FALSE(NearZero(size.Width()));
    EXPECT_FALSE(result.GetX() >= 0.0f);
    EXPECT_FALSE(result.GetX() + size.Width() <= 0.0f);
    EXPECT_FALSE(result.GetY() >= 0.0f);
    EXPECT_FALSE(result.GetY() + size.Height() <= 0.0f);

    /**
     * @tc.steps3: Invoke GetPixelMapOffset
     * @tc.expected: NearZero(gestureEventHub->frameNodeSize_.Width()) is true,
     * NearZero(size.Width()) is true.
     */
    size = SizeF(0, 0);
    gestureEventHub->GetPixelMapOffset(info, size, data, 1.0f);
    result = OffsetF(size.Width() * PIXELMAP_WIDTH_RATE, size.Height() * PIXELMAP_HEIGHT_RATE);
    EXPECT_TRUE(NearZero(gestureEventHub->frameNodeSize_.Width()));
    EXPECT_TRUE(NearZero(size.Width()));
    EXPECT_TRUE(result.GetX() >= 0.0f);
    EXPECT_TRUE(result.GetX() + size.Width() <= 0.0f);
    EXPECT_TRUE(result.GetY() >= 0.0f);
    EXPECT_TRUE(result.GetY() + size.Height() <= 0.0f);

    /**
     * @tc.steps4: Invoke GetPixelMapOffset
     * @tc.expected: NearZero(gestureEventHub->frameNodeSize_.Width()) is false,
     * NearZero(size.Width()) is false.
     */
    size = SizeF(500, 600);
    gestureEventHub->frameNodeSize_ = SizeF(1, 1);
    gestureEventHub->GetPixelMapOffset(info, size, data, 1.0f);
    result = OffsetF(size.Width() * PIXELMAP_WIDTH_RATE, size.Height() * PIXELMAP_HEIGHT_RATE);
    EXPECT_FALSE(NearZero(gestureEventHub->frameNodeSize_.Width()));
    EXPECT_FALSE(NearZero(size.Width()));

    /**
     * @tc.steps5: Invoke GetPixelMapOffset
     * @tc.expected: NearZero(gestureEventHub->frameNodeSize_.Width()) is false,
     * NearZero(size.Width()) is true.
     */
    size = SizeF(0, 0);
    gestureEventHub->frameNodeSize_ = SizeF(1, 1);
    gestureEventHub->GetPixelMapOffset(info, size, data, 1.0f);
    result = OffsetF(size.Width() * PIXELMAP_WIDTH_RATE, size.Height() * PIXELMAP_HEIGHT_RATE);
    EXPECT_FALSE(NearZero(gestureEventHub->frameNodeSize_.Width()));
    EXPECT_TRUE(NearZero(size.Width()));
}

/**
 * @tc.name: GestureEventHubGetPixelMapScaleTest002
 * @tc.desc: Test GetPixelMapScale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubGetPixelMapScaleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode1 = FrameNode::CreateFrameNode(V2::WEB_ETS_TAG, 102, AceType::MakeRefPtr<Pattern>());
    auto gestureEventHub = frameNode1->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto eventHub = gestureEventHub->eventHub_.Upgrade();
    eventHub->AttachHost(frameNode1);
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps2: Invoke GetPixelMapScale
     */
    int32_t height = 500;
    int32_t width = 600;
    GestureEvent info = GestureEvent();
    auto size = SizeF(1, 1);
    PreparedInfoForDrag data;
    gestureEventHub->GetPixelMapOffset(info, size, data, 1.0f);
    auto frameNode2 = gestureEventHub->GetFrameNode();
    EXPECT_NE(frameNode2, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    EXPECT_NE(dragDropManager, nullptr);
    auto dragPreviewOption = frameNode2->GetDragPreviewOption();
    dragPreviewOption.isScaleEnabled = true;
    gestureEventHub->GetPixelMapScale(height, width);
    EXPECT_FALSE(!frameNode2->GetDragPreviewOption().isScaleEnabled);
    EXPECT_FALSE(!(frameNode2->GetTag() == V2::WEB_ETS_TAG));

    /**
     * @tc.steps3: Invoke GetPixelMapScale
     */
    constexpr float PIXELMAP_DEFALUT_LIMIT_SCALE = 0.5f;
    SystemProperties::SetDevicePhysicalHeight(600);
    SystemProperties::SetDevicePhysicalWidth(200);
    int32_t deviceHeight = SystemProperties::GetDevicePhysicalHeight();
    int32_t deviceWidth = SystemProperties::GetDevicePhysicalWidth();
    int32_t maxDeviceLength = std::max(deviceHeight, deviceWidth);
    int32_t minDeviceLength = std::min(deviceHeight, deviceWidth);
    gestureEventHub->GetPixelMapScale(height, width);
    EXPECT_TRUE(maxDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE > minDeviceLength);
    EXPECT_TRUE(height > minDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE);

    /**
     * @tc.steps4: Invoke GetPixelMapScale
     */
    height = 50;
    SystemProperties::SetDevicePhysicalHeight(600);
    SystemProperties::SetDevicePhysicalWidth(200);
    deviceHeight = SystemProperties::GetDevicePhysicalHeight();
    deviceWidth = SystemProperties::GetDevicePhysicalWidth();
    maxDeviceLength = std::max(deviceHeight, deviceWidth);
    minDeviceLength = std::min(deviceHeight, deviceWidth);
    gestureEventHub->GetPixelMapScale(height, width);
    EXPECT_TRUE(maxDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE > minDeviceLength);
    EXPECT_FALSE(height > minDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE);
}
} // namespace OHOS::Ace::NG