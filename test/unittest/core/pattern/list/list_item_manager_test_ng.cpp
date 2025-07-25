/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "list_test_ng.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_item_drag_manager.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ListItemManagerTestNg : public ListTestNg {};

/**
 * @tc.name: GetListFrameNode001
 * @tc.desc: Test ListItemDragManager GetListFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, GetListFrameNode001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(node, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    frameNode->parent_ = node;
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    host->parent_ = frameNode;
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    auto result = listItemDragManager->GetListFrameNode();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: HandleAutoScroll001
 * @tc.desc: Test ListItemDragManager HandleAutoScroll
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, HandleAutoScroll001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    host->previewOption_.enableEdgeAutoScroll = false;
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    listItemDragManager->listNode_ = host;
    listItemDragManager->scrolling_ = true;
    PointF point(30.0f, 30.0f);
    RectF rect(20.0f, 25.0f, 20.0f, 10.0f);
    listItemDragManager->HandleAutoScroll(0, point, rect);
    EXPECT_FALSE(listItemDragManager->scrolling_);
}

/**
 * @tc.name: HandleScrollCallback001
 * @tc.desc: Test ListItemDragManager HandleScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, HandleScrollCallback001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(node, nullptr);
    node->geometryNode_ = nullptr;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    frameNode->parent_ = node;
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    host->geometryNode_->frame_.rect_.SetRect(OffsetF(20.0f, 20.0f), SizeF(100.0f, 100.0f));
    host->children_ = { frameNode, node };
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    listItemDragManager->listNode_ = node;
    listItemDragManager->scrolling_ = true;
    listItemDragManager->HandleScrollCallback();
    EXPECT_FALSE(listItemDragManager->scrolling_);
}

/**
 * @tc.name: HandleOnItemDragUpdate001
 * @tc.desc: Test ListItemDragManager HandleOnItemDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, HandleOnItemDragUpdate001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    host->geometryNode_->frame_.rect_.SetRect(OffsetF(20.0f, 20.0f), SizeF(100.0f, 100.0f));
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    listItemDragManager->axis_ = Axis::HORIZONTAL;
    listItemDragManager->listNode_ = nullptr;
    listItemDragManager->dragOffset_ = OffsetF(10.0f, 10.0f);
    listItemDragManager->realOffset_ = OffsetF(20.0f, 20.0f);
    GestureEvent info;
    info.SetOffsetX(30.0f);
    info.SetOffsetY(20.0f);
    listItemDragManager->HandleOnItemDragUpdate(info);
    EXPECT_EQ(listItemDragManager->realOffset_.GetY(), 10.0f);
}

/**
 * @tc.name: ScaleAxisNearItem001
 * @tc.desc: Test ListItemDragManager ScaleAxisNearItem001
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, ScaleAxisNearItem001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(node, nullptr);
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    listItemDragManager->listNode_ = node;
    RectF rect(0.0f, 25.0f, 20.0f, 10.0f);
    auto res = listItemDragManager->ScaleAxisNearItem(1, rect, OffsetF(20.0f, 20.0f), Axis::VERTICAL);
    EXPECT_FALSE(res.needMove);
}

/**
 * @tc.name: InitDragDropEvent_DragEvent
 * @tc.desc: Test ListItemDragManager InitDragDropEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, InitDragDropEvent_DragEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItemDragManager
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    WeakPtr<FrameNode> weakListNode = AceType::WeakClaim(AceType::RawPtr(listNode));
    auto host = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(host, nullptr);
    host->SetParent(weakListNode);
    host->renderContext_ = RenderContext::Create();
    auto pattern = host->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    WeakPtr<ListItemEventHub> weakListItemEventHub = AceType::WeakClaim(AceType::RawPtr(listItemEventHub));
    host->eventHub_ = listItemEventHub;
    auto eventHub = host->GetEventHub<ListItemEventHub>();
    RefPtr<GestureEventHub> gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(weakListItemEventHub);
    WeakPtr<GestureEventHub> weakGestureEventHub = AceType::WeakClaim(AceType::RawPtr(gestureEventHub));
    eventHub->gestureEventHub_ = gestureEventHub;
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);

    /**
     * @tc.steps: step2. Set SourceTool of info to FINGER
     */
    GestureEvent info;
    info.SetSourceTool(SourceTool::FINGER);

    /**
     * @tc.steps: step3. Calling the InitDragDropEvent function
     * @tc.expected: The DragEvent Actuator is created and has drag event
     */
    listItemDragManager->InitDragDropEvent();
    EXPECT_TRUE(eventHub->gestureEventHub_->GetDragEventActuator()->HasDragEvent());
    EXPECT_EQ(eventHub->gestureEventHub_->GetDragEventActuator()->GetFingers(), DEFAULT_PAN_FINGER);
    EXPECT_EQ(eventHub->gestureEventHub_->GetDragEventActuator()->GetDirection().type, PanDirection::ALL);
    EXPECT_EQ(eventHub->gestureEventHub_->GetDragEventActuator()->GetDistance(), DEFAULT_PAN_DISTANCE.Value());
    EXPECT_TRUE(eventHub->gestureEventHub_->GetDragEventActuator()->isForDragDrop_);
}

/**
 * @tc.name: InitDragDropEvent_actionStartTask
 * @tc.desc: Test ListItemDragManager InitDragDropEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, InitDragDropEvent_actionStartTask, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItemDragManager
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    WeakPtr<FrameNode> weakListNode = AceType::WeakClaim(AceType::RawPtr(listNode));
    auto host = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(host, nullptr);
    host->SetParent(weakListNode);
    host->renderContext_ = RenderContext::Create();
    OffsetF offset(10.0f, 10.0f);
    host->GetGeometryNode()->SetMarginFrameOffset(offset);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    WeakPtr<ListItemEventHub> weakListItemEventHub = AceType::WeakClaim(AceType::RawPtr(listItemEventHub));
    host->eventHub_ = listItemEventHub;
    auto eventHub = host->GetEventHub<ListItemEventHub>();
    RefPtr<GestureEventHub> gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(weakListItemEventHub);
    WeakPtr<GestureEventHub> weakGestureEventHub = AceType::WeakClaim(AceType::RawPtr(gestureEventHub));
    eventHub->gestureEventHub_ = gestureEventHub;
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);

    /**
     * @tc.steps: step2. Set dragState to IDLE and dragOffset to (20.0f, 20.0f)
     * and set SourceTool of info to FINGER
     */
    listItemDragManager->dragOffset_ = OffsetF(20.0f, 20.0f);
    listItemDragManager->dragState_ = ListItemDragState::IDLE;
    GestureEvent info;
    info.SetSourceTool(SourceTool::FINGER);

    /**
     * @tc.steps: step3. Calling the InitDragDropEvent and actionStartTask function
     * @tc.expected: The dragState is set to DRAGGING and dragOffset is set to (10.0f, 10.0f)
     */
    listItemDragManager->InitDragDropEvent();
    auto actionStartTask = eventHub->gestureEventHub_->GetDragEventActuator()->userCallback_->GetActionStartEventFunc();
    actionStartTask(info);
    EXPECT_EQ(listItemDragManager->dragOffset_.GetX(), 10.0f);
    EXPECT_EQ(listItemDragManager->dragOffset_.GetY(), 10.0f);
    EXPECT_EQ(listItemDragManager->dragState_, ListItemDragState::DRAGGING);
}

/**
 * @tc.name: InitDragDropEvent_actionUpdateTask
 * @tc.desc: Test ListItemDragManager InitDragDropEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, InitDragDropEvent_actionUpdateTask, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItemDragManager
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    WeakPtr<FrameNode> weakListNode = AceType::WeakClaim(AceType::RawPtr(listNode));
    auto host = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(host, nullptr);
    host->SetParent(weakListNode);
    host->renderContext_ = RenderContext::Create();
    OffsetF offset(10.0f, 10.0f);
    host->GetGeometryNode()->SetMarginFrameOffset(offset);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    WeakPtr<ListItemEventHub> weakListItemEventHub = AceType::WeakClaim(AceType::RawPtr(listItemEventHub));
    host->eventHub_ = listItemEventHub;
    auto eventHub = host->GetEventHub<ListItemEventHub>();
    RefPtr<GestureEventHub> gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(weakListItemEventHub);
    WeakPtr<GestureEventHub> weakGestureEventHub = AceType::WeakClaim(AceType::RawPtr(gestureEventHub));
    eventHub->gestureEventHub_ = gestureEventHub;
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);

    /**
     * @tc.steps: step2. Set SourceTool of info to FINGER and offset of info to (20.0f, 40.0f)
     * Set dragOffset to (20.0f, 20.0f) and realOffset to (0.0f, 0.0f)
     */
    listItemDragManager->dragOffset_ = OffsetF(20.0f, 20.0f);
    listItemDragManager->realOffset_ = OffsetF(0.0f, 0.0f);
    GestureEvent info;
    info.SetSourceTool(SourceTool::FINGER);
    info.SetOffsetX(20.0);
    info.SetOffsetY(40.0);

    /**
     * @tc.steps: step3. Calling the InitDragDropEvent and actionUpdateTask function
     * @tc.expected: The realOffset is set to (20.0f, 60.0f)
     */
    listItemDragManager->InitDragDropEvent();
    auto actionUpdateTask =
        eventHub->gestureEventHub_->GetDragEventActuator()->userCallback_->GetActionUpdateEventFunc();
    actionUpdateTask(info);
    EXPECT_EQ(listItemDragManager->realOffset_.GetX(), 20.0f);
    EXPECT_EQ(listItemDragManager->realOffset_.GetY(), 60.0f);
}

/**
 * @tc.name: InitDragDropEvent_actionEndTask
 * @tc.desc: Test ListItemDragManager InitDragDropEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, InitDragDropEvent_actionEndTask, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItemDragManager
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    WeakPtr<FrameNode> weakListNode = AceType::WeakClaim(AceType::RawPtr(listNode));
    auto host = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(host, nullptr);
    host->SetParent(weakListNode);
    host->renderContext_ = RenderContext::Create();
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    WeakPtr<ListItemEventHub> weakListItemEventHub = AceType::WeakClaim(AceType::RawPtr(listItemEventHub));
    host->eventHub_ = listItemEventHub;
    auto eventHub = host->GetEventHub<ListItemEventHub>();
    RefPtr<GestureEventHub> gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(weakListItemEventHub);
    WeakPtr<GestureEventHub> weakGestureEventHub = AceType::WeakClaim(AceType::RawPtr(gestureEventHub));
    eventHub->gestureEventHub_ = gestureEventHub;
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);

    /**
     * @tc.steps: step2. Set SourceTool of info to FINGER and draggingIndex_ to 0
     * Set isNeedDividerAnimation_ to false and scrolling to true
     * Set dragState to DRAGGING
     */
    listItemDragManager->scrolling_ = true;
    listItemDragManager->dragState_ = ListItemDragState::DRAGGING;
    pattern->SetDraggingIndex(0);
    pattern->SetIsNeedDividerAnimation(false);
    GestureEvent info;
    info.SetSourceTool(SourceTool::FINGER);

    /**
     * @tc.steps: step3. Calling the InitDragDropEvent and actionEndTask function
     * @tc.expected: The scrolling is false and dragState is set to IDLE
     * and draggingIndex_ is set to -1
     */
    listItemDragManager->InitDragDropEvent();
    auto actionEndTask = eventHub->gestureEventHub_->GetDragEventActuator()->userCallback_->GetActionEndEventFunc();
    actionEndTask(info);
    EXPECT_EQ(pattern->draggingIndex_, -1);
    EXPECT_FALSE(listItemDragManager->scrolling_);
    EXPECT_EQ(listItemDragManager->dragState_, ListItemDragState::IDLE);
}

/**
 * @tc.name: InitDragDropEvent_actionCancelTask
 * @tc.desc: Test ListItemDragManager InitDragDropEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, InitDragDropEvent_actionCancelTask, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItemDragManager
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    WeakPtr<FrameNode> weakListNode = AceType::WeakClaim(AceType::RawPtr(listNode));
    auto host = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(host, nullptr);
    host->SetParent(weakListNode);
    host->renderContext_ = RenderContext::Create();
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    WeakPtr<ListItemEventHub> weakListItemEventHub = AceType::WeakClaim(AceType::RawPtr(listItemEventHub));
    host->eventHub_ = listItemEventHub;
    auto eventHub = host->GetEventHub<ListItemEventHub>();
    RefPtr<GestureEventHub> gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(weakListItemEventHub);
    WeakPtr<GestureEventHub> weakGestureEventHub = AceType::WeakClaim(AceType::RawPtr(gestureEventHub));
    eventHub->gestureEventHub_ = gestureEventHub;
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);

    /**
     * @tc.steps: step2. Set SourceTool of info to FINGER
     * Set dragState to DRAGGING and isNeedDividerAnimation_ to false
     * Set hotZoneScrollCallback_ to a lambda function
     */
    listItemDragManager->dragState_ = ListItemDragState::DRAGGING;
    pattern->SetIsNeedDividerAnimation(false);
    auto func = []() {};
    pattern->SetHotZoneScrollCallback(std::move(func));
    GestureEvent info;
    info.SetSourceTool(SourceTool::FINGER);

    /**
     * @tc.steps: step3. Calling the InitDragDropEvent and actionCancelTask function
     * @tc.expected: The dragState is set to IDLE and the hotZoneScrollCallback_ is set to nullptr
     */
    listItemDragManager->InitDragDropEvent();
    auto actionCancelTask =
        eventHub->gestureEventHub_->GetDragEventActuator()->userCallback_->GetActionCancelEventFunc();
    actionCancelTask();
    EXPECT_EQ(listItemDragManager->dragState_, ListItemDragState::IDLE);
    EXPECT_EQ(pattern->hotZoneScrollCallback_, nullptr);
}

/**
 * @tc.name: InitDragDropEvent_actionLongPress
 * @tc.desc: Test ListItemDragManager InitDragDropEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, InitDragDropEvent_actionLongPress, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItemDragManager
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    WeakPtr<FrameNode> weakListNode = AceType::WeakClaim(AceType::RawPtr(listNode));
    auto host = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(host, nullptr);
    host->SetParent(weakListNode);
    host->renderContext_ = RenderContext::Create();
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    WeakPtr<ListItemEventHub> weakListItemEventHub = AceType::WeakClaim(AceType::RawPtr(listItemEventHub));
    host->eventHub_ = listItemEventHub;
    auto eventHub = host->GetEventHub<ListItemEventHub>();
    RefPtr<GestureEventHub> gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(weakListItemEventHub);
    WeakPtr<GestureEventHub> weakGestureEventHub = AceType::WeakClaim(AceType::RawPtr(gestureEventHub));
    eventHub->gestureEventHub_ = gestureEventHub;
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    int32_t number = 1;
    lazyForEachNode->onLongPressEvent_ = [&number](int32_t index) { number += index; };
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);

    /**
     * @tc.steps: step2. Set SourceTool of info to FINGER
     * and set dragState to IDLE
     */
    listItemDragManager->dragState_ = ListItemDragState::IDLE;
    GestureEvent info;
    info.SetSourceTool(SourceTool::FINGER);

    /**
     * @tc.steps: step3. Calling the InitDragDropEvent and longPress function
     * @tc.expected: The dragState is set to LONG_PRESS and number is set to 0
     */
    listItemDragManager->InitDragDropEvent();
    auto longPress = eventHub->gestureEventHub_->GetDragEventActuator()->userCallback_->GetLongPressEventFunc();
    longPress(info);
    EXPECT_EQ(listItemDragManager->dragState_, ListItemDragState::LONG_PRESS);
    EXPECT_EQ(number, 0);
}
} // namespace OHOS::Ace::NG