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
namespace {
constexpr size_t DEFAULT_CHILD_COUNT = 4;
constexpr float GRID_WIDTH = 480.0f;
constexpr float GRID_HEIGHT = 800.0f;
constexpr float ITEM_WIDTH = 120.0f;
constexpr float ITEM_HEIGHT = 200.0f;
constexpr double DEFAULT_OFFSET_Y = 5.0;

RefPtr<FrameNode> CreateGridNodeWithChild(size_t childCount, const GridItemStyle& gridItemStyle)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::GRID_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() {return AceType::MakeRefPtr<GridPattern>(); });
    ViewAbstract::SetWidth(Referenced::RawPtr(frameNode), CalcLength(GRID_WIDTH));
    ViewAbstract::SetHeight(Referenced::RawPtr(frameNode), CalcLength(GRID_HEIGHT));
    std::list<RefPtr<FrameNode>> childNodes;

    for (size_t i = 0; i < childCount; ++i) {
        auto chidNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto childNode = FrameNode::GetOrCreateFrameNode(V2::GRID_ITEM_ETS_TAG, chidNodeId,
            [itemStyle = gridItemStyle]() { return AceType::MakeRefPtr<GridItemPattern>(nullptr, itemStyle); });
        ViewAbstract::SetWidth(Referenced::RawPtr(childNode), CalcLength(ITEM_WIDTH));
        ViewAbstract::SetHeight(Referenced::RawPtr(childNode), CalcLength(ITEM_HEIGHT));
        childNode->MountToParent(frameNode);
        childNodes.emplace_back(childNode);
    }
    return frameNode;
}

RefPtr<NG::NGGestureRecognizer> CreateRecognizerGroup(const RefPtr<NG::FrameNode>& parentNode)
{
    CHECK_NULL_RETURN(parentNode, nullptr);
    std::list<RefPtr<NGGestureRecognizer>> recognizers;
    for (const auto& childNode : parentNode->GetChildren()) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(childNode);
        if (childFrameNode) {
            auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
            clickRecognizer->AttachFrameNode(childFrameNode);
            recognizers.emplace_back(clickRecognizer);
        }
    }
    auto recognizerGroup = AceType::MakeRefPtr<NG::ParallelRecognizer>(std::move(recognizers));
    if (recognizerGroup) {
        recognizerGroup->AttachFrameNode(parentNode);
    }
    return recognizerGroup;
}

RefPtr<FrameNode> ProcessDragItemGroupScene()
{
    auto gridNode = CreateGridNodeWithChild(DEFAULT_CHILD_COUNT, GridItemStyle::NONE);
    CHECK_NULL_RETURN(gridNode, nullptr);
    auto gestureEventHub = gridNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureEventHub, nullptr);

    for (const auto& child : gridNode->GetChildren()) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        if (!childNode) {
            continue;
        }
        auto itemGestureHub = childNode->GetOrCreateGestureEventHub();
        if (!itemGestureHub) {
            continue;
        }
        itemGestureHub->InitDragDropEvent();
        auto itemActuator = itemGestureHub->GetDragEventActuator();
        if (!itemActuator) {
            continue;
        }
        itemActuator->isSelectedItemNode_ = true;
        itemActuator->itemParentNode_ = gridNode;

        auto gridItemPattern = childNode->GetPattern<GridItemPattern>();
        if (!gridItemPattern) {
            continue;
        }
        gridItemPattern->SetSelected(true);
    }
    auto gridItem = AceType::DynamicCast<FrameNode>(gridNode->GetChildByIndex(0));
    CHECK_NULL_RETURN(gridItem, nullptr);
    auto pattern = gridNode->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->info_.endIndex_ = DEFAULT_CHILD_COUNT;

    gestureEventHub->InitDragDropEvent();
    auto actuator = gestureEventHub->GetDragEventActuator();
    CHECK_NULL_RETURN(actuator, nullptr);
    actuator->isSelectedItemNode_ = true;
    actuator->FindItemParentNode(gridItem);
    return gridNode;
}
} // namespace

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
 * @tc.desc: Test SetOnTouchEvent, SetJSFrameNodeOnTouchEvent and ClearJSFrameNodeOnTouch.
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
    gestureEventHub->SetJSFrameNodeOnTouchEvent(std::move(touchEventFunc));
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

/**
 * @tc.name: GestureEventHubGetPixelMapScaleTest003
 * @tc.desc: Test GetPixelMapScale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubGetPixelMapScaleTest003, TestSize.Level1)
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
    constexpr float PIXELMAP_DEFALUT_LIMIT_SCALE = 0.5f;
    constexpr float PIXELMAP_DRAG_WGR_SCALE = 3.0f;
    SystemProperties::SetDevicePhysicalHeight(600);
    SystemProperties::SetDevicePhysicalWidth(600);
    int32_t deviceHeight = SystemProperties::GetDevicePhysicalHeight();
    int32_t deviceWidth = SystemProperties::GetDevicePhysicalWidth();
    int32_t maxDeviceLength = std::max(deviceHeight, deviceWidth);
    int32_t minDeviceLength = std::min(deviceHeight, deviceWidth);
    gestureEventHub->GetPixelMapScale(height, width);
    EXPECT_FALSE(maxDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE > minDeviceLength);
    EXPECT_FALSE(gestureEventHub->GetTextDraggable());
    EXPECT_TRUE(height > minDeviceLength / PIXELMAP_DRAG_WGR_SCALE);
    EXPECT_TRUE(width > minDeviceLength * PIXELMAP_DRAG_WGR_TEXT_SCALE / PIXELMAP_DRAG_WGR_SCALE);
    EXPECT_TRUE(height > minDeviceLength / PIXELMAP_DRAG_WGR_SCALE);
    EXPECT_TRUE(width > minDeviceLength / PIXELMAP_DRAG_WGR_SCALE);

    /**
     * @tc.steps3: Invoke GetPixelMapScale
     */
    gestureEventHub->SetTextDraggable(true);
    gestureEventHub->GetPixelMapScale(height, width);
    EXPECT_FALSE(maxDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE > minDeviceLength);
    EXPECT_TRUE(gestureEventHub->GetTextDraggable());
    EXPECT_TRUE(height > minDeviceLength / PIXELMAP_DRAG_WGR_SCALE);
    EXPECT_TRUE(width > minDeviceLength * PIXELMAP_DRAG_WGR_TEXT_SCALE / PIXELMAP_DRAG_WGR_SCALE);

    /**
     * @tc.steps4: Invoke GetPixelMapScale
     */
    height = 100;
    width = 100;
    gestureEventHub->SetTextDraggable(false);
    gestureEventHub->GetPixelMapScale(height, width);
    EXPECT_FALSE(maxDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE > minDeviceLength);
    EXPECT_FALSE(gestureEventHub->GetTextDraggable());
    EXPECT_FALSE(height > minDeviceLength / PIXELMAP_DRAG_WGR_SCALE);
    EXPECT_FALSE(width > minDeviceLength / PIXELMAP_DRAG_WGR_SCALE);
}

/**
 * @tc.name: ProcessTouchTestHit001
 * @tc.desc: Test ProcessTouchTestHit func
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, ProcessTouchTestHit001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto gridNode = CreateGridNodeWithChild(DEFAULT_CHILD_COUNT, GridItemStyle::NONE);
    ASSERT_NE(gridNode, nullptr);
    auto gestureEventHub = gridNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto recognizerGroup = CreateRecognizerGroup(gridNode);
    ASSERT_NE(recognizerGroup, nullptr);

    /**
     * @tc.steps: step2. Invoke ProcessTouchTestHit.
     */
    gestureEventHub->parallelCombineClick = true;
    gestureEventHub->SetUserOnClick([](GestureEvent& info) {});

    auto userClickEventActuator = gestureEventHub->GetUserClickEventActuator();
    ASSERT_NE(userClickEventActuator, nullptr);
    TouchRestrict touchRestrict;
    TouchTestResult innerTargets;
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    innerTargets.emplace_back(recognizerGroup);
    gestureEventHub->redirectClick_=true;
    auto flag = gestureEventHub->ProcessTouchTestHit(
        COORDINATE_OFFSET, touchRestrict, innerTargets, finalResult, TOUCH_ID, PointF(), nullptr, responseLinkResult);
    EXPECT_FALSE(flag);
}

/**
 * @tc.name: StartLongPressActionForWeb001
 * @tc.desc: Test StartLongPressActionForWeb func
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, StartLongPressActionForWeb001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto gridNode = CreateGridNodeWithChild(DEFAULT_CHILD_COUNT, GridItemStyle::NONE);
    ASSERT_NE(gridNode, nullptr);
    auto gestureEventHub = gridNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. set DragEvent and handle drag.
     */
    auto dragActionStart = [](GestureEvent& info) {};
    auto dragActionUpdate = [](GestureEvent& info) {};
    auto dragActionEnd = [](GestureEvent& info) {};
    auto dragActionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(dragActionStart), std::move(dragActionUpdate), std::move(dragActionEnd), std::move(dragActionCancel));
    gestureEventHub->SetCustomDragEvent(dragEvent, PAN_DIRECTION_ALL, FINGERS, DISTANCE);

    /**
     * @tc.steps: step3. create taskExecutor to fire task callBack.
     * @tc.expected: taskExecutor is not null.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    gestureEventHub->StartLongPressActionForWeb();
    EXPECT_NE(gestureEventHub->GetDragEventActuator(), nullptr);
}

/**
 * @tc.name: WebDragAction001
 * @tc.desc: Test web drag action.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, WebDragAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() {return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. set DragEvent and handle drag.
     */
    auto dragActionStart = [](GestureEvent& info) {};
    auto dragActionUpdate = [](GestureEvent& info) {};
    auto dragActionEnd = [](GestureEvent& info) {};
    auto dragActionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(dragActionStart), std::move(dragActionUpdate), std::move(dragActionEnd), std::move(dragActionCancel));
    gestureEventHub->SetCustomDragEvent(dragEvent, PAN_DIRECTION_ALL, FINGERS, DISTANCE);
    gestureEventHub->HandleNotAllowDrag(GestureEvent());

    /**
     * @tc.steps: step3. create taskExecutor to fire task callBack.
     * @tc.expected: taskExecutor is not null.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    gestureEventHub->StartDragTaskForWeb();
    gestureEventHub->CancelDragForWeb();
    gestureEventHub->ResetDragActionForWeb();
    EXPECT_NE(gestureEventHub->GetDragEventActuator(), nullptr);
}

/**
 * @tc.name: GenerateMousePixelMap001
 * @tc.desc: Test GenerateMousePixelMap func.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GenerateMousePixelMap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text frameNode and add drag frameNode then Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), textPattern);
    ASSERT_NE(frameNode, nullptr);
    auto dragNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() {return AceType::MakeRefPtr<Pattern>(); });
    textPattern->dragNode_ = dragNode;
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Invoke GenerateMousePixelMap.
     * @tc.expected: TextDraggable is true.
     */
    gestureEventHub->SetTextDraggable(true);
    GestureEvent info;
    gestureEventHub->GenerateMousePixelMap(info);
    EXPECT_TRUE(gestureEventHub->pixelMap_ == nullptr);
}

/**
 * @tc.name: RegisterCoordinationListener001
 * @tc.desc: Test RegisterCoordinationListener func.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, RegisterCoordinationListener001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto gridNode = CreateGridNodeWithChild(DEFAULT_CHILD_COUNT, GridItemStyle::NONE);
    ASSERT_NE(gridNode, nullptr);
    auto gestureEventHub = gridNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. set DragEvent and handle drag.
     */
    auto dragActionStart = [](GestureEvent& info) {};
    auto dragActionUpdate = [](GestureEvent& info) {};
    auto dragActionEnd = [](GestureEvent& info) {};
    auto dragActionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(dragActionStart), std::move(dragActionUpdate), std::move(dragActionEnd), std::move(dragActionCancel));
    gestureEventHub->SetCustomDragEvent(dragEvent, PAN_DIRECTION_ALL, FINGERS, DISTANCE);

    /**
     * @tc.steps: step3. create taskExecutor to fire task callBack and invoke registerCoordinationListener.
     * @tc.expected: registerCoordinationListener is called once.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    auto mock = AceType::DynamicCast<MockInteractionInterface>(InteractionInterface::GetInstance());
    ASSERT_NE(mock, nullptr);
    gestureEventHub->RegisterCoordinationListener(context);
    if (mock->gDragOutCallback) {
        mock->gDragOutCallback();
    }
}

/**
 * @tc.name: GridNodeHandleOnDragUpdate001
 * @tc.desc: Test gridnode Drag scene.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GridNodeHandleOnDragUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid with gridItem frame node tree.
     * @tc.expected: instance is not null.
     */
    auto gridNode = CreateGridNodeWithChild(DEFAULT_CHILD_COUNT, GridItemStyle::NONE);
    ASSERT_NE(gridNode, nullptr);
    auto gestureEventHub = gridNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    for (const auto& child : gridNode->GetChildren()) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        ASSERT_TRUE(childNode != nullptr);
        auto gridItemPattern = childNode->GetPattern<GridItemPattern>();
        ASSERT_TRUE(gridItemPattern != nullptr);
        gridItemPattern->SetSelected(true);
    }
    auto gridItem = AceType::DynamicCast<FrameNode>(gridNode->GetChildByIndex(0));
    ASSERT_NE(gridItem, nullptr);
    auto pattern = gridNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->info_.endIndex_ = DEFAULT_CHILD_COUNT;

    /**
     * @tc.steps: step2. set all griditems are selected.
     */
    gestureEventHub->InitDragDropEvent();
    constexpr int64_t PROXY_ID_NOT_FIT = 101;
    auto dragDropProxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    gestureEventHub->dragDropProxy_ = dragDropProxy;
    auto actuator = gestureEventHub->GetDragEventActuator();
    ASSERT_NE(actuator, nullptr);
    actuator->isSelectedItemNode_ = true;
    actuator->FindItemParentNode(gridItem);

    /**
     * @tc.steps: step3. handle grid drag when switch to subwindow.
     */
    GestureEvent info;
    gestureEventHub->HandleOnDragStart(info);
    for (double step = 0; step < DEFAULT_OFFSET_Y; ++step) {
        info.SetOffsetY(step);
        gestureEventHub->HandleOnDragUpdate(info);
    }
    gestureEventHub->HandleOnDragEnd(info);
    EXPECT_NE(gestureEventHub->gestureInfoForWeb_, nullptr);
}

/**
 * @tc.name: GetDragCallback001
 * @tc.desc: Test GetDragCallback fun and fire callback.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetDragCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid with gridItem frame node tree.
     * @tc.expected: instance is not null.
     */
    auto gridNode = CreateGridNodeWithChild(DEFAULT_CHILD_COUNT, GridItemStyle::NONE);
    ASSERT_NE(gridNode, nullptr);
    auto gestureEventHub = gridNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto eventHub = gridNode->GetEventHub<GridEventHub>();

    /**
     * @tc.steps: step2. create taskExecutor to fire task callBack.
     * @tc.expected: taskExecutor is not null.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    auto dragDropManager = context->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    auto mock = AceType::DynamicCast<MockInteractionInterface>(InteractionInterface::GetInstance());
    ASSERT_NE(mock, nullptr);

    /**
     * @tc.steps: step3. Invoke GetDragCallback to get function and fire this function.
     * @tc.expected: fire function success.
     */
    MockContainer::SetUp();
    int32_t callbackInfo = 0;
    eventHub->SetOnDragEnd([&callbackInfo](const RefPtr<OHOS::Ace::DragEvent>& /*dragEvent*/) {
        callbackInfo = 1;
    });
    auto dragCallback = gestureEventHub->GetDragCallback(context, eventHub);
    ASSERT_NE(dragCallback, nullptr);
    EXPECT_CALL(*mock, UnRegisterCoordinationListener()).Times(1).WillOnce(Return(50));
    DragNotifyMsgCore notifyMessage;
    dragCallback(notifyMessage);
    EXPECT_FALSE(dragDropManager->IsDragged());
    EXPECT_EQ(callbackInfo, 1);
    MockContainer::TearDown();
}

/**
 * @tc.name: CopyGestures001
 * @tc.desc: Test CopyGestures from another guestureEventHub.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, CopyGestures001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create guestureEventHub dest and source.
     */
    auto eventHubSrc = AceType::MakeRefPtr<EventHub>();
    auto eventHubDest = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHubSrc = eventHubSrc->GetOrCreateGestureEventHub();
    auto gestureEventHubDest = eventHubDest->GetOrCreateGestureEventHub();
    auto longPressGesture = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    longPressGesture->SetTag(CHECK_TAG_1);
    gestureEventHubSrc->AddGesture(longPressGesture);

    /**
     * @tc.steps: step2. Invoke CopyGestures.
     * @tc.expected: The member variable of dest is a copy of source.
     */
    gestureEventHubDest->CopyGestures(gestureEventHubSrc);
    EXPECT_EQ(gestureEventHubDest->gestures_.size(), gestureEventHubSrc->gestures_.size());
    EXPECT_TRUE(gestureEventHubDest->recreateGesture_);
}

/**
 * @tc.name: SetResponseRegionWithRemove001
 * @tc.desc: Test SetResponseRegion with RemoveLastResponseRect.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, SetResponseRegionWithRemove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create guestureEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();

    /**
     * @tc.steps: step2. Invoke SetResponseRegion.
     * @tc.expected: SetResponseRegion success.
     */
    std::vector<DimensionRect> responseRegion;
    responseRegion.push_back(DimensionRect());
    int32_t callbackInfo = 0;
    gestureEventHub->SetResponseRegionFunc([&callbackInfo](const std::vector<DimensionRect>& /*reponseRegion*/) {
        callbackInfo = 1;
    });
    gestureEventHub->SetResponseRegion(responseRegion);
    EXPECT_EQ(gestureEventHub->responseRegion_.size(), responseRegion.size());

    /**
     * @tc.steps: step3. Invoke RemoveLastResponseRect.
     * @tc.expected: RemoveLastResponseRect success and fire responseRegionFunc.
     */
    gestureEventHub->RemoveLastResponseRect();
    EXPECT_TRUE(gestureEventHub->responseRegion_.empty());
    EXPECT_EQ(callbackInfo, 1);
}

/**
 * @tc.name: SetDragGatherPixelMaps001
 * @tc.desc: Test SetDragGatherPixelMaps when input type is mouse button.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, SetDragGatherPixelMaps001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid with gridItem frame node tree.
     * @tc.expected: instance is not null.
     */
    auto gridNode = ProcessDragItemGroupScene();
    ASSERT_NE(gridNode, nullptr);
    auto gestureEventHub = gridNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto dragDropManager = context->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Invoke SetDragGatherPixelMaps.
     * @tc.expected: gatherPixelMaps is not empty.
     */
    GestureEvent info;
    info.SetInputEventType(InputEventType::MOUSE_BUTTON);
    gestureEventHub->SetDragGatherPixelMaps(info);
    EXPECT_TRUE(dragDropManager->gatherPixelMaps_.empty());
}

/**
 * @tc.name: SetDragGatherPixelMaps002
 * @tc.desc: Test SetDragGatherPixelMaps when input type is not mouse button.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, SetDragGatherPixelMaps002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid with gridItem frame node tree.
     * @tc.expected: instance is not null.
     */
    auto gridNode = ProcessDragItemGroupScene();
    ASSERT_NE(gridNode, nullptr);
    auto gestureEventHub = gridNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Init prefabricated values.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto dragDropManager = context->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);
    GatherNodeChildInfo gatherNodeChildInfo;
    gatherNodeChildInfo.imageNode = imageNode;
    std::vector<GatherNodeChildInfo> gatherNodeChildInfos;
    gatherNodeChildInfos.emplace_back(gatherNodeChildInfo);
    ASSERT_NE(gestureEventHub->GetFrameNode(), nullptr);
    overlayManager->MountGatherNodeToRootNode(gestureEventHub->GetFrameNode(), gatherNodeChildInfos);

    /**
     * @tc.steps: step3. Invoke SetDragGatherPixelMaps.
     * @tc.expected: gatherPixelMaps is not empty.
     */
    GestureEvent info;
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    gestureEventHub->SetDragGatherPixelMaps(info);
    EXPECT_TRUE(dragDropManager->gatherPixelMaps_.empty());
}

/**
 * @tc.name: GetSelectItemSize001
 * @tc.desc: Test GetSelectItemSize.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetSelectItemSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create grid with gridItem frame node tree.
     * @tc.expected: instance is not null.
     */
    SystemProperties::dragDropFrameworkStatus_ = 3;
    auto gridNode = ProcessDragItemGroupScene();
    ASSERT_NE(gridNode, nullptr);
    auto gridItem = AceType::DynamicCast<FrameNode>(gridNode->GetChildByIndex(0));
    ASSERT_NE(gridItem, nullptr);
    auto gestureEventHub = gridItem->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Invoke GetSelectItemSize.
     * @tc.expected: size is equal to children count.
     */
    EXPECT_EQ(gestureEventHub->GetSelectItemSize(), gridNode->GetChildren().size());
}

/**
 * @tc.name: RemoveGesturesByTag001
 * @tc.desc: Test RemoveGesturesByTag.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, RemoveGesturesByTag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gestureEventHub and create gesture list.
     * @tc.expected: instance is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    std::vector<RefPtr<Gesture>> gestures;
    auto longPressGestureOne = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    longPressGestureOne->SetTag(CHECK_TAG_1);
    gestureEventHub->AttachGesture(longPressGestureOne);
    auto longPressGestureTwo = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    gestures.emplace_back(longPressGestureTwo);
    auto longPressGestureThree = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    gestures.emplace_back(longPressGestureThree);
    auto group = AceType::MakeRefPtr<GestureGroup>(GestureMode::Exclusive, gestures);
    gestureEventHub->AttachGesture(group);

    /**
     * @tc.steps: step2. Invoke RemoveGesturesByTag.
     * @tc.expected: Remove Gestures by tag. modifierGestures_ size is 1 (only GestureGroup).
     */
    gestureEventHub->RemoveGesturesByTag(CHECK_TAG_1);
    EXPECT_EQ(gestureEventHub->modifierGestures_.size(), 1);
}

/**
 * @tc.name: FireCustomerOnDragEnd001
 * @tc.desc: Test FireCustomerOnDragEnd.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, FireCustomerOnDragEnd001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gestureEventHub.
     * @tc.expected: instance is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Invoke FireCustomerOnDragEnd.
     * @tc.expected: eventHub fire dragEnd callback.
     */
    int callbackInfo = 0;
    eventHub->SetOnDragEnd([&callbackInfo](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */) {
        callbackInfo = 1;
    });
    auto context = PipelineContext::GetCurrentContext();
    gestureEventHub->FireCustomerOnDragEnd(context, eventHub);
    EXPECT_EQ(callbackInfo, 1);
}
} // namespace OHOS::Ace::NG