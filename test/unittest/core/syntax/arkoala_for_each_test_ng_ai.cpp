/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <functional>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/syntax/arkoala_for_each_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include <string>

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_2 = 2;
constexpr int32_t INVALID_INDEX = -1;
}

class ArkoalaForEachTestNgAI : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }

    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }

    RefPtr<ArkoalaForEachNode> CreateForEachNode(bool isRepeat = false)
    {
        return AceType::MakeRefPtr<ArkoalaForEachNode>(TEST_NODE_ID, isRepeat);
    }

    RefPtr<FrameNode> CreateFrameNode(const std::string& tag)
    {
        auto pattern = AceType::MakeRefPtr<Pattern>();
        auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
        pattern->AttachToFrameNode(frameNode);
        return frameNode;
    }

    RefPtr<FrameNode> CreateListItemNode()
    {
        auto pattern = AceType::MakeRefPtr<NG::ListItemPattern>(nullptr);
        auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::LIST_ITEM_ETS_TAG, -1, pattern);
        pattern->AttachToFrameNode(frameNode);
        return frameNode;
    }
};

/**
 * @tc.name: Constructor_BasicTest
 * @tc.desc: Test ArkoalaForEachNode constructor initializes correctly
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, Constructor_BasicTest, TestSize.Level1)
{
    auto node = CreateForEachNode(false);
    ASSERT_NE(node, nullptr);

    EXPECT_EQ(node->GetId(), TEST_NODE_ID);
    EXPECT_EQ(node->GetTag(), V2::JS_FOR_EACH_ETS_TAG);
    EXPECT_FALSE(node->isRepeat_);
}

/**
 * @tc.name: Constructor_RepeatNodeTest
 * @tc.desc: Test ArkoalaForEachNode constructor with isRepeat=true
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, Constructor_RepeatNodeTest, TestSize.Level1)
{
    auto node = CreateForEachNode(true);
    ASSERT_NE(node, nullptr);

    EXPECT_EQ(node->GetTag(), V2::JS_REPEAT_ETS_TAG);
    EXPECT_TRUE(node->isRepeat_);
}

/**
 * @tc.name: IsAtomicNode_ReturnsFalseTest
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, IsAtomicNode_ReturnsFalseTest, TestSize.Level1)
{
    auto node = CreateForEachNode();
    ASSERT_NE(node, nullptr);

    EXPECT_FALSE(node->IsAtomicNode());
}

/**
 * @tc.name: IsSyntaxNode_ReturnsTrueTest
 * @tc.desc: Test IsSyntaxNode returns true (inherited from ForEachBaseNode)
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, IsSyntaxNode_ReturnsTrueTest, TestSize.Level1)
{
    auto node = CreateForEachNode();
    ASSERT_NE(node, nullptr);

    EXPECT_TRUE(node->IsSyntaxNode());
}

/**
 * @tc.name: FinishRender_UpdatesParentTest
 * @tc.desc: Test FinishRender notifies parent frame node
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, FinishRender_UpdatesParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto parentNode = CreateFrameNode(V2::COLUMN_ETS_TAG);
    ASSERT_NE(parentNode, nullptr);

    parentNode->AddChild(forEachNode);

    forEachNode->FinishRender();

    SUCCEED();
}

/**
 * @tc.name: FlushUpdateAndMarkDirty_MarksDirtyTest
 * @tc.desc: Test FlushUpdateAndMarkDirty marks dirty flags
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, FlushUpdateAndMarkDirty_MarksDirtyTest, TestSize.Level1)
{
    auto node = CreateForEachNode();
    ASSERT_NE(node, nullptr);

    node->FlushUpdateAndMarkDirty();

    SUCCEED();
}

/**
 * @tc.name: SetOnMove_SetsCallbackTest
 * @tc.desc: Test SetOnMove sets the onMove callback
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, SetOnMove_SetsCallbackTest, TestSize.Level1)
{
    auto node = CreateForEachNode();
    ASSERT_NE(node, nullptr);

    bool onMoveCalled = false;
    node->SetOnMove([&onMoveCalled](int32_t, int32_t) { onMoveCalled = true; });

    EXPECT_EQ(node->onMoveEvent_, nullptr);
}

/**
 * @tc.name: SetOnMove_ClearsCallbackTest
 * @tc.desc: Test SetOnMove with nullptr clears the callback
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, SetOnMove_ClearsCallbackTest, TestSize.Level1)
{
    auto node = CreateForEachNode();
    ASSERT_NE(node, nullptr);

    node->SetOnMove([](int32_t, int32_t) {});
    EXPECT_EQ(node->onMoveEvent_, nullptr);

    node->SetOnMove(nullptr);
    EXPECT_EQ(node->onMoveEvent_, nullptr);
}

/**
 * @tc.name: SetItemDragEvent_SetsHandlersTest
 * @tc.desc: Test SetItemDragEvent sets drag handlers when onMove exists
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, SetItemDragEvent_SetsHandlersTest, TestSize.Level1)
{
    auto node = CreateForEachNode();
    ASSERT_NE(node, nullptr);

    node->onMoveEvent_ = [](int32_t, int32_t) {};

    bool onLongPressCalled = false;
    bool onDragStartCalled = false;
    bool onMoveThroughCalled = false;
    bool onDropCalled = false;

    node->SetItemDragEvent(
        [&onLongPressCalled](int32_t) { onLongPressCalled = true; },
        [&onDragStartCalled](int32_t) { onDragStartCalled = true; },
        [&onMoveThroughCalled](int32_t, int32_t) { onMoveThroughCalled = true; },
        [&onDropCalled](int32_t) { onDropCalled = true; }
    );

    EXPECT_NE(node->onLongPressEvent_, nullptr);
    EXPECT_NE(node->onDragStartEvent_, nullptr);
    EXPECT_NE(node->onMoveThroughEvent_, nullptr);
    EXPECT_NE(node->onDropEvent_, nullptr);
}

/**
 * @tc.name: SetItemDragEvent_WithoutOnMoveTest
 * @tc.desc: Test SetItemDragEvent does not set handlers when onMove is null
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, SetItemDragEvent_WithoutOnMoveTest, TestSize.Level1)
{
    auto node = CreateForEachNode();
    ASSERT_NE(node, nullptr);

    node->onMoveEvent_ = nullptr;

    node->SetItemDragEvent([](int32_t) {}, [](int32_t) {}, [](int32_t, int32_t) {}, [](int32_t) {});

    EXPECT_EQ(node->onLongPressEvent_, nullptr);
    EXPECT_EQ(node->onDragStartEvent_, nullptr);
    EXPECT_EQ(node->onMoveThroughEvent_, nullptr);
    EXPECT_EQ(node->onDropEvent_, nullptr);
}

/**
 * @tc.name: FireOnMove_TriggersCallbackTest
 * @tc.desc: Test FireOnMove triggers the callback with correct parameters
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, FireOnMove_TriggersCallbackTest, TestSize.Level1)
{
    auto node = CreateForEachNode();
    ASSERT_NE(node, nullptr);

    bool onMoveCalled = false;
    int32_t receivedFrom = INVALID_INDEX;
    int32_t receivedTo = INVALID_INDEX;

    node->onMoveEvent_ = [&onMoveCalled, &receivedFrom, &receivedTo](int32_t from, int32_t to) {
        onMoveCalled = true;
        receivedFrom = from;
        receivedTo = to;
    };

    node->FireOnMove(INDEX_0, INDEX_1);

    EXPECT_TRUE(onMoveCalled);
    EXPECT_EQ(receivedFrom, INDEX_0);
    EXPECT_EQ(receivedTo, INDEX_1);
}

/**
 * @tc.name: FireOnMove_SameIndexTest
 * @tc.desc: Test FireOnMove with same index does not trigger callback
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, FireOnMove_SameIndexTest, TestSize.Level1)
{
    auto node = CreateForEachNode();
    ASSERT_NE(node, nullptr);

    bool onMoveCalled = false;
    node->onMoveEvent_ = [&onMoveCalled](int32_t, int32_t) { onMoveCalled = true; };

    node->FireOnMove(INDEX_0, INDEX_0);

    EXPECT_FALSE(onMoveCalled);
}

/**
 * @tc.name: MoveData_ReordersItemsTest
 * @tc.desc: Test MoveData reorders children correctly
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, MoveData_ReordersItemsTest, TestSize.Level1)
{
    auto node = CreateForEachNode();
    ASSERT_NE(node, nullptr);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto child1 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto child2 = CreateFrameNode(V2::TEXT_ETS_TAG);

    node->AddChild(child0);
    node->AddChild(child1);
    node->AddChild(child2);

    EXPECT_EQ(node->GetChildren().size(), 3);

    node->MoveData(INDEX_0, INDEX_2);

    const auto& children = node->GetChildren();
    EXPECT_EQ(children.size(), 3);
}

/**
 * @tc.name: MoveData_SameIndexTest
 * @tc.desc: Test MoveData with same index returns early
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, MoveData_SameIndexTest, TestSize.Level1)
{
    auto node = CreateForEachNode();
    ASSERT_NE(node, nullptr);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    node->AddChild(child0);

    const auto& childrenBefore = node->GetChildren();
    node->MoveData(INDEX_0, INDEX_0);
    const auto& childrenAfter = node->GetChildren();

    EXPECT_EQ(childrenBefore.size(), childrenAfter.size());
}

/**
 * @tc.name: MoveData_NegativeIndexTest
 * @tc.desc: Test MoveData with negative index returns early
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, MoveData_NegativeIndexTest, TestSize.Level1)
{
    auto node = CreateForEachNode();
    ASSERT_NE(node, nullptr);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    node->AddChild(child0);

    node->MoveData(INVALID_INDEX, INDEX_0);
    node->MoveData(INDEX_0, INVALID_INDEX);

    SUCCEED();
}

/**
 * @tc.name: DumpInfo_RepeatNodeTest
 * @tc.desc: Test DumpInfo for repeat node
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, DumpInfo_RepeatNodeTest, TestSize.Level1)
{
    auto node = CreateForEachNode(true);
    ASSERT_NE(node, nullptr);

    node->DumpInfo();

    SUCCEED();
}

/**
 * @tc.name: DumpInfo_ForEachNodeTest
 * @tc.desc: Test DumpInfo for foreach node
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, DumpInfo_ForEachNodeTest, TestSize.Level1)
{
    auto node = CreateForEachNode(false);
    ASSERT_NE(node, nullptr);

    node->DumpInfo();

    SUCCEED();
}

/**
 * @tc.name: SetOnMove_WithParentNodeTest
 * @tc.desc: Test SetOnMove when parent node exists and init drag manager
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, SetOnMove_WithParentNodeTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto parentNode = CreateFrameNode(V2::LIST_ETS_TAG);
    ASSERT_NE(parentNode, nullptr);
    forEachNode->SetParent(parentNode);
    forEachNode->onMainTree_ = true;

    auto listItem = CreateListItemNode();
    ASSERT_NE(listItem, nullptr);
    auto listItemPattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(listItemPattern, nullptr);

    auto listItemWrapper = CreateFrameNode("wrapper");
    listItemWrapper->AddChild(listItem);
    parentNode->AddChild(forEachNode);
    forEachNode->AddChild(listItemWrapper);

    auto setOnMoveCbFunc = [](int32_t from, int32_t to) {};
    forEachNode->SetOnMove(setOnMoveCbFunc);

    SUCCEED();
}

/**
 * @tc.name: SetOnMove_WithoutParentNodeTest
 * @tc.desc: Test SetOnMove when parent node does not exist, should post task
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, SetOnMove_WithoutParentNodeTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    forEachNode->onMainTree_ = false;

    auto setOnMoveCbFunc = [](int32_t from, int32_t to) {};
    forEachNode->SetOnMove(setOnMoveCbFunc);

    SUCCEED();
}

/**
 * @tc.name: SetOnMove_ClearOnMoveWithExistingEventTest
 * @tc.desc: Test SetOnMove clears onMoveEvent_ when onMove is nullptr and onMoveEvent_ exists
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, SetOnMove_ClearOnMoveWithExistingEventTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto parentNode = CreateFrameNode(V2::LIST_ETS_TAG);
    forEachNode->SetParent(parentNode);
    forEachNode->onMainTree_ = true;

    forEachNode->SetOnMove([](int32_t, int32_t) {});

    forEachNode->SetOnMove(nullptr);

    EXPECT_EQ(forEachNode->onMoveEvent_, nullptr);
}

/**
 * @tc.name: InitDragManager_WithListParentTest
 * @tc.desc: Test InitDragManager with List parent
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, InitDragManager_WithListParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto parentNode = CreateFrameNode(V2::LIST_ETS_TAG);
    forEachNode->SetParent(parentNode);

    auto listItem = CreateListItemNode();
    ASSERT_NE(listItem, nullptr);

    forEachNode->InitDragManager(listItem);

    SUCCEED();
}

/**
 * @tc.name: InitDragManager_WithGridParentTest
 * @tc.desc: Test InitDragManager with Grid parent
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, InitDragManager_WithGridParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto gridNode = CreateFrameNode(V2::GRID_ETS_TAG);
    forEachNode->SetParent(gridNode);

    auto gridItem = CreateFrameNode(V2::GRID_ITEM_ETS_TAG);
    ASSERT_NE(gridItem, nullptr);

    forEachNode->InitDragManager(gridItem);

    SUCCEED();
}

/**
 * @tc.name: InitDragManager_WithNonListGridParentTest
 * @tc.desc: Test InitDragManager with non-List/Grid parent returns early
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, InitDragManager_WithNonListGridParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto columnNode = CreateFrameNode(V2::COLUMN_ETS_TAG);
    forEachNode->SetParent(columnNode);

    auto listItem = CreateListItemNode();
    ASSERT_NE(listItem, nullptr);

    forEachNode->InitDragManager(listItem);

    SUCCEED();
}

/**
 * @tc.name: InitDragManager_NullChildTest
 * @tc.desc: Test InitDragManager with null child returns early
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, InitDragManager_NullChildTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto parentNode = CreateFrameNode(V2::LIST_ETS_TAG);
    forEachNode->SetParent(parentNode);

    forEachNode->InitDragManager(nullptr);

    SUCCEED();
}

/**
 * @tc.name: InitAllChildrenDragManager_InitWithListParentTest
 * @tc.desc: Test InitAllChildrenDragManager init=true with List parent
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, InitAllChildrenDragManager_InitWithListParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto listParent = CreateFrameNode(V2::LIST_ETS_TAG);
    forEachNode->SetParent(listParent);

    auto listItem = CreateListItemNode();
    auto listItemPattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(listItemPattern, nullptr);

    auto wrapperNode = AceType::MakeRefPtr<FrameNode>("wrapper", -1, AceType::MakeRefPtr<Pattern>());
    wrapperNode->AddChild(listItem);
    forEachNode->AddChild(wrapperNode);

    forEachNode->InitAllChildrenDragManager(true);

    SUCCEED();
}

/**
 * @tc.name: InitAllChildrenDragManager_InitWithGridParentTest
 * @tc.desc: Test InitAllChildrenDragManager init=true with Grid parent
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, InitAllChildrenDragManager_InitWithGridParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto gridParent = CreateFrameNode(V2::GRID_ETS_TAG);
    forEachNode->SetParent(gridParent);

    auto gridItem = CreateFrameNode(V2::GRID_ITEM_ETS_TAG);

    auto wrapperNode = AceType::MakeRefPtr<FrameNode>("wrapper", -1, AceType::MakeRefPtr<Pattern>());
    wrapperNode->AddChild(gridItem);
    forEachNode->AddChild(wrapperNode);

    forEachNode->InitAllChildrenDragManager(true);

    SUCCEED();
}

/**
 * @tc.name: InitAllChildrenDragManager_DeInitWithListParentTest
 * @tc.desc: Test InitAllChildrenDragManager init=false with List parent calls DeInitDragManager
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, InitAllChildrenDragManager_DeInitWithListParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto listParent = CreateFrameNode(V2::LIST_ETS_TAG);
    forEachNode->SetParent(listParent);

    auto listItem = CreateListItemNode();
    auto listItemPattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(listItemPattern, nullptr);

    auto wrapperNode = AceType::MakeRefPtr<FrameNode>("wrapper", -1, AceType::MakeRefPtr<Pattern>());
    wrapperNode->AddChild(listItem);
    forEachNode->AddChild(wrapperNode);

    forEachNode->InitAllChildrenDragManager(false);

    SUCCEED();
}

/**
 * @tc.name: InitAllChildrenDragManager_DeInitWithGridParentTest
 * @tc.desc: Test InitAllChildrenDragManager init=false with Grid parent calls DeInitDragManager
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, InitAllChildrenDragManager_DeInitWithGridParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto gridParent = CreateFrameNode(V2::GRID_ETS_TAG);
    forEachNode->SetParent(gridParent);

    auto gridItem = CreateFrameNode(V2::GRID_ITEM_ETS_TAG);

    auto wrapperNode = AceType::MakeRefPtr<FrameNode>("wrapper", -1, AceType::MakeRefPtr<Pattern>());
    wrapperNode->AddChild(gridItem);
    forEachNode->AddChild(wrapperNode);

    forEachNode->InitAllChildrenDragManager(false);

    SUCCEED();
}

/**
 * @tc.name: InitAllChildrenDragManager_WithNonListGridParentTest
 * @tc.desc: Test InitAllChildrenDragManager with non-List/Grid parent clears onMoveEvent_
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, InitAllChildrenDragManager_WithNonListGridParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto columnParent = CreateFrameNode(V2::COLUMN_ETS_TAG);
    forEachNode->SetParent(columnParent);

    forEachNode->onMoveEvent_ = [](int32_t, int32_t) {};

    forEachNode->InitAllChildrenDragManager(true);

    EXPECT_EQ(forEachNode->onMoveEvent_, nullptr);
}

/**
 * @tc.name: InitAllChildrenDragManager_ChildWithZeroChildrenTest
 * @tc.desc: Test InitAllChildrenDragManager skips child with zero children
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, InitAllChildrenDragManager_ChildWithZeroChildrenTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto listParent = CreateFrameNode(V2::LIST_ETS_TAG);
    forEachNode->SetParent(listParent);

    auto emptyWrapper = AceType::MakeRefPtr<FrameNode>("wrapper", -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->AddChild(emptyWrapper);

    forEachNode->InitAllChildrenDragManager(true);

    SUCCEED();
}

/**
 * @tc.name: InitAllChildrenDragManager_ChildWithMultipleChildrenTest
 * @tc.desc: Test InitAllChildrenDragManager skips child with multiple children
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, InitAllChildrenDragManager_ChildWithMultipleChildrenTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto listParent = CreateFrameNode(V2::LIST_ETS_TAG);
    forEachNode->SetParent(listParent);

    auto listItem1 = CreateListItemNode();
    auto listItem2 = CreateListItemNode();
    auto wrapperNode = AceType::MakeRefPtr<FrameNode>("wrapper", -1, AceType::MakeRefPtr<Pattern>());
    wrapperNode->AddChild(listItem1);
    wrapperNode->AddChild(listItem2);
    forEachNode->AddChild(wrapperNode);

    forEachNode->InitAllChildrenDragManager(true);

    SUCCEED();
}

/**
 * @tc.name: InitAllChildrenDragManager_NullChildInListTest
 * @tc.desc: Test InitAllChildrenDragManager handles null child in List parent
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, InitAllChildrenDragManager_NullChildInListTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto listParent = CreateFrameNode(V2::LIST_ETS_TAG);
    forEachNode->SetParent(listParent);

    auto emptyWrapper = AceType::MakeRefPtr<FrameNode>("wrapper", -1, AceType::MakeRefPtr<Pattern>());
    auto listItem = CreateListItemNode();
    emptyWrapper->AddChild(listItem);
    forEachNode->AddChild(emptyWrapper);

    forEachNode->InitAllChildrenDragManager(true);

    SUCCEED();
}

/**
 * @tc.name: MoveData_IsNeedUpdateTrueWithParentTest
 * @tc.desc: Test MoveData when isNeedUpdate=true and parent frame node exists
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, MoveData_IsNeedUpdateTrueWithParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto parentNode = CreateFrameNode(V2::COLUMN_ETS_TAG);
    forEachNode->SetParent(parentNode);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto child1 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto child2 = CreateFrameNode(V2::TEXT_ETS_TAG);

    forEachNode->AddChild(child0);
    forEachNode->AddChild(child1);
    forEachNode->AddChild(child2);

    forEachNode->MoveData(INDEX_0, INDEX_2, true);

    SUCCEED();
}

/**
 * @tc.name: MoveData_IsNeedUpdateFalseTest
 * @tc.desc: Test MoveData when isNeedUpdate=false skips ChildrenUpdatedFrom
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, MoveData_IsNeedUpdateFalseTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto parentNode = CreateFrameNode(V2::COLUMN_ETS_TAG);
    forEachNode->SetParent(parentNode);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto child1 = CreateFrameNode(V2::TEXT_ETS_TAG);

    forEachNode->AddChild(child0);
    forEachNode->AddChild(child1);

    forEachNode->MoveData(INDEX_0, INDEX_1, false);

    SUCCEED();
}

/**
 * @tc.name: MoveData_IsNeedUpdateTrueWithoutParentTest
 * @tc.desc: Test MoveData when isNeedUpdate=true but no parent frame node
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, MoveData_IsNeedUpdateTrueWithoutParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto child1 = CreateFrameNode(V2::TEXT_ETS_TAG);

    forEachNode->AddChild(child0);
    forEachNode->AddChild(child1);

    forEachNode->MoveData(INDEX_0, INDEX_1, true);

    SUCCEED();
}

/**
 * @tc.name: GetFrameNode_ReturnsFrameNodeTest
 * @tc.desc: Test GetFrameNode returns FrameNode by index
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, GetFrameNode_ReturnsFrameNodeTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    forEachNode->AddChild(child0);

    auto frameNode = forEachNode->GetFrameNode(INDEX_0);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: GetFrameNode_InvalidIndexTest
 * @tc.desc: Test GetFrameNode with invalid index returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaForEachTestNgAI, GetFrameNode_InvalidIndexTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto frameNode = forEachNode->GetFrameNode(INVALID_INDEX);
    EXPECT_EQ(frameNode, nullptr);
}

} // namespace OHOS::Ace::NG
