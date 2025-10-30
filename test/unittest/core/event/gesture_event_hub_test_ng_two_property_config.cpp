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
    MockContainer::SetUp();
    auto gridNode = CreateGridNodeWithChild(DEFAULT_CHILD_COUNT, GridItemStyle::NONE);
    ASSERT_NE(gridNode, nullptr);
    auto gestureEventHub = gridNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto eventHub = gridNode->GetEventHub<GridEventHub>();
    gridNode->instanceId_ = MockContainer::CurrentId();

    /**
     * @tc.steps: step2. create taskExecutor to fire task callBack.
     * @tc.expected: taskExecutor is not null.
     */
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    container->pipelineContext_ = context;
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    container->taskExecutor_ = context->taskExecutor_;
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
    int32_t callbackInfo = 0;
    eventHub->SetOnDragEnd([&callbackInfo](const RefPtr<OHOS::Ace::DragEvent>& /*dragEvent*/) {
        callbackInfo = 1;
    });
    auto dragCallback = gestureEventHub->GetDragCallback();
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