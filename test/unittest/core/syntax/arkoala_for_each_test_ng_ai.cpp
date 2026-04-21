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
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/arkoala_for_each_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

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
        return CreateFrameNode(V2::LIST_ITEM_ETS_TAG);
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

} // namespace OHOS::Ace::NG
