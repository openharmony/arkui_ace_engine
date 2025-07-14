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

#include <utility>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ListItemPatternTestNg : public TestNG {
public:
};

/**
 * @tc.name: OnDidPop001
 * @tc.desc: Test ListItemPattern OnDidPop
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnDidPop001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_ = { frameNode, frameNode, frameNode, frameNode, frameNode };
    listItemPattern->frameNode_ = frameNode;
    listItemPattern->endNodeIndex_ = 2;
    listItemPattern->childNodeIndex_ = 3;
    listItemPattern->OnDidPop();
    EXPECT_EQ(listItemPattern->endNodeIndex_, 0);
    EXPECT_EQ(listItemPattern->childNodeIndex_, 2);
}

/**
 * @tc.name: OnDidPop002
 * @tc.desc: Test ListItemPattern OnDidPop
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnDidPop002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_ = { frameNode, frameNode, frameNode, frameNode, frameNode };
    listItemPattern->frameNode_ = frameNode;
    listItemPattern->endNodeIndex_ = 2;
    listItemPattern->childNodeIndex_ = 1;
    listItemPattern->OnDidPop();
    EXPECT_EQ(listItemPattern->endNodeIndex_, 2);
    EXPECT_EQ(listItemPattern->childNodeIndex_, 1);
}

/**
 * @tc.name: OnDidPop003
 * @tc.desc: Test ListItemPattern OnDidPop
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnDidPop003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_ = { frameNode, frameNode, frameNode, frameNode, frameNode };
    listItemPattern->frameNode_ = frameNode;
    listItemPattern->endNodeIndex_ = -1;
    listItemPattern->childNodeIndex_ = 2;
    listItemPattern->OnDidPop();
    EXPECT_EQ(listItemPattern->endNodeIndex_, -1);
    EXPECT_EQ(listItemPattern->childNodeIndex_, 2);
}

/**
 * @tc.name: GetParentFrameNode001
 * @tc.desc: Test ListItemPattern GetParentFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, GetParentFrameNode001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->parent_ = frameNode;
    listItemPattern->frameNode_ = frameNode;
    auto result = listItemPattern->GetParentFrameNode();
    EXPECT_EQ(result, frameNode);
}

/**
 * @tc.name: GetParentFrameNode002
 * @tc.desc: Test ListItemPattern GetParentFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, GetParentFrameNode002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->parent_ = nullptr;
    listItemPattern->frameNode_ = frameNode;
    auto result = listItemPattern->GetParentFrameNode();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetParentFrameNode003
 * @tc.desc: Test ListItemPattern GetParentFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, GetParentFrameNode003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    node->parent_ = frameNode;
    frameNode->parent_ = node;
    listItemPattern->frameNode_ = frameNode;
    auto result = listItemPattern->GetParentFrameNode();
    EXPECT_EQ(result, frameNode);
}

/**
 * @tc.name: HandleDragStart001
 * @tc.desc: Test ListItemPattern HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragStart001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::MOUSE;
    listItemPattern->HandleDragStart(info);
    EXPECT_FALSE(listItemPattern->isDragging_);
}

/**
 * @tc.name: HandleDragStart002
 * @tc.desc: Test ListItemPattern HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragStart002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    GestureEvent info;
    info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    info.sourceTool_ = SourceTool::MOUSE;
    listItemPattern->HandleDragStart(info);
    EXPECT_TRUE(listItemPattern->isDragging_);
}

/**
 * @tc.name: HandleDragStart003
 * @tc.desc: Test ListItemPattern HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragStart003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::AIRBRUSH;
    listItemPattern->HandleDragStart(info);
    EXPECT_TRUE(listItemPattern->isDragging_);
}

/**
 * @tc.name: CalculateFriction001
 * @tc.desc: Test ListItemPattern CalculateFriction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, CalculateFriction001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto result = listItemPattern->CalculateFriction(2.0f);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: CalculateFriction002
 * @tc.desc: Test ListItemPattern CalculateFriction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, CalculateFriction002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto result = listItemPattern->CalculateFriction(-5.0f);
    EXPECT_EQ(result, 1.0f);
}

/**
 * @tc.name: HandleDragUpdate001
 * @tc.desc: Test ListItemPattern HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragUpdate001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::MOUSE;
    listItemPattern->hasStartDeleteArea_ = true;
    listItemPattern->HandleDragUpdate(info);
    EXPECT_TRUE(listItemPattern->hasStartDeleteArea_);
}

/**
 * @tc.name: HandleDragUpdate002
 * @tc.desc: Test ListItemPattern HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragUpdate002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    RefPtr<ListItemLayoutProperty> listItemLayoutProperty = AceType::MakeRefPtr<ListItemLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listItemLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    GestureEvent info;
    info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    info.sourceTool_ = SourceTool::MOUSE;
    listItemPattern->hasStartDeleteArea_ = true;
    listItemPattern->HandleDragUpdate(info);
    EXPECT_FALSE(listItemPattern->hasStartDeleteArea_);
}

/**
 * @tc.name: HandleDragUpdate003
 * @tc.desc: Test ListItemPattern HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragUpdate003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    RefPtr<ListItemLayoutProperty> listItemLayoutProperty = AceType::MakeRefPtr<ListItemLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listItemLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::AIRBRUSH;
    listItemPattern->hasStartDeleteArea_ = true;
    listItemPattern->HandleDragUpdate(info);
    EXPECT_FALSE(listItemPattern->hasStartDeleteArea_);
}

/**
 * @tc.name: OnRecycle001
 * @tc.desc: Test ListItemPatternTestNg OnRecycle001
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, OnRecycle001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->OnRecycle();
    EXPECT_EQ(listItemPattern->swipeActionState_, SwipeActionState::COLLAPSED);
}


/**
 * @tc.name: HandleDragEnd001
 * @tc.desc: Test ListItemPattern HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragEnd001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::MOUSE;
    listItemPattern->isDragging_ = true;
    listItemPattern->HandleDragEnd(info);
    EXPECT_TRUE(listItemPattern->isDragging_);
}

/**
 * @tc.name: HandleDragEnd002
 * @tc.desc: Test ListItemPattern HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragEnd002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(node, nullptr);
    node->tag_ = V2::LIST_ETS_TAG;
    node->pattern_ = listPattern;
    frameNode->parent_ = node;
    listItemPattern->frameNode_ = frameNode;
    listPattern->swiperItem_ = listItemPattern;
    listPattern->canReplaceSwiperItem_ = false;
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    listItemEventHub->startOnDeleteEvent_ = []() {};
    listItemEventHub->endOnDeleteEvent_ = []() {};
    frameNode->eventHub_ = listItemEventHub;
    GestureEvent info;
    info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    info.sourceTool_ = SourceTool::MOUSE;
    listItemPattern->isDragging_ = true;
    listItemPattern->HandleDragEnd(info);
    EXPECT_TRUE(listPattern->canReplaceSwiperItem_);
    EXPECT_FALSE(listItemPattern->isDragging_);
}

/**
 * @tc.name: HandleDragEnd003
 * @tc.desc: Test ListItemPattern HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(ListItemPatternTestNg, HandleDragEnd003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(node, nullptr);
    node->tag_ = V2::LIST_ETS_TAG;
    node->pattern_ = listPattern;
    frameNode->parent_ = node;
    listItemPattern->frameNode_ = frameNode;
    listPattern->swiperItem_ = listItemPattern;
    listPattern->canReplaceSwiperItem_ = false;
    RefPtr<ListItemEventHub> listItemEventHub = AceType::MakeRefPtr<ListItemEventHub>();
    listItemEventHub->startOnDeleteEvent_ = []() {};
    listItemEventHub->endOnDeleteEvent_ = []() {};
    frameNode->eventHub_ = listItemEventHub;
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::AIRBRUSH;
    listItemPattern->isDragging_ = true;
    listItemPattern->HandleDragEnd(info);
    EXPECT_TRUE(listPattern->canReplaceSwiperItem_);
    EXPECT_FALSE(listItemPattern->isDragging_);
}
} // namespace OHOS::Ace::NG