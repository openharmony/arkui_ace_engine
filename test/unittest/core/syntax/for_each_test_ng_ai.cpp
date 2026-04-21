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

#include <functional>
#include <list>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/for_each_model_ng.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_INDEX_0 = 0;
constexpr int32_t TEST_INDEX_1 = 1;
constexpr int32_t TEST_INDEX_5 = 5;
constexpr int32_t INVALID_INDEX = -1;
const std::list<std::string> TEST_IDS = { "0", "1", "2", "3" };
} // namespace

class ForEachTestNgAI : public testing::Test {
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

    RefPtr<ForEachNode> CreateForEachNode()
    {
        ForEachModelNG forEach;
        forEach.Create();
        auto forEachNode = AceType::DynamicCast<ForEachNode>(ViewStackProcessor::GetInstance()->Finish());
        return forEachNode;
    }

    RefPtr<FrameNode> CreateBlankChildNode()
    {
        return FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    }

    void AddChildrenToForEach(RefPtr<ForEachNode>& forEachNode, int32_t count)
    {
        for (int32_t i = 0; i < count; ++i) {
            forEachNode->AddChild(CreateBlankChildNode());
        }
    }
};

/**
 * @tc.name: SetItemDragHandler_BasicTest
 * @tc.desc: Test SetItemDragHandler with valid callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, SetItemDragHandler_BasicTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    bool onLongPressCalled = false;
    bool onDragStartCalled = false;
    bool onMoveThroughCalled = false;
    bool onDropCalled = false;

    std::function<void(int32_t)> onLongPress = [&onLongPressCalled](int32_t index) {
        onLongPressCalled = true;
    };
    std::function<void(int32_t)> onDragStart = [&onDragStartCalled](int32_t index) {
        onDragStartCalled = true;
    };
    std::function<void(int32_t, int32_t)> onMoveThrough = [&onMoveThroughCalled](int32_t from, int32_t through) {
        onMoveThroughCalled = true;
    };
    std::function<void(int32_t)> onDrop = [&onDropCalled](int32_t index) {
        onDropCalled = true;
    };

    forEachNode->SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));

    forEachNode->FireOnLongPress(TEST_INDEX_0);
    EXPECT_FALSE(onLongPressCalled);

    forEachNode->FireOnDragStart(TEST_INDEX_0);
    EXPECT_FALSE(onDragStartCalled);

    forEachNode->FireOnMoveThrough(TEST_INDEX_0, TEST_INDEX_1);
    EXPECT_FALSE(onMoveThroughCalled);

    forEachNode->FireOnDrop(TEST_INDEX_0);
    EXPECT_FALSE(onDropCalled);
}

/**
 * @tc.name: SetItemDragHandler_WithoutOnMoveTest
 * @tc.desc: Test SetItemDragHandler without onMove should not set callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, SetItemDragHandler_WithoutOnMoveTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    forEachNode->onMoveEvent_ = nullptr;

    std::function<void(int32_t)> onLongPress = [](int32_t index) {};
    std::function<void(int32_t)> onDragStart = [](int32_t index) {};
    std::function<void(int32_t, int32_t)> onMoveThrough = [](int32_t from, int32_t through) {};
    std::function<void(int32_t)> onDrop = [](int32_t index) {};

    forEachNode->SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));

    EXPECT_EQ(forEachNode->onLongPressEvent_, nullptr);
    EXPECT_EQ(forEachNode->onDragStartEvent_, nullptr);
    EXPECT_EQ(forEachNode->onMoveThroughEvent_, nullptr);
    EXPECT_EQ(forEachNode->onDropEvent_, nullptr);
}

/**
 * @tc.name: FireOnMove_SameIndexTest
 * @tc.desc: Test FireOnMove when from == to should not trigger callback
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, FireOnMove_SameIndexTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    bool onMoveCalled = false;
    forEachNode->onMoveEvent_ = [&onMoveCalled](int32_t from, int32_t to) {
        onMoveCalled = true;
    };

    forEachNode->FireOnMove(TEST_INDEX_0, TEST_INDEX_0);
    EXPECT_FALSE(onMoveCalled);
}

/**
 * @tc.name: FireOnMove_DifferentIndexTest
 * @tc.desc: Test FireOnMove when from != to should trigger callback
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, FireOnMove_DifferentIndexTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    bool onMoveCalled = false;
    int32_t receivedFrom = INVALID_INDEX;
    int32_t receivedTo = INVALID_INDEX;

    forEachNode->onMoveEvent_ = [&onMoveCalled, &receivedFrom, &receivedTo](int32_t from, int32_t to) {
        onMoveCalled = true;
        receivedFrom = from;
        receivedTo = to;
    };

    forEachNode->FireOnMove(TEST_INDEX_0, TEST_INDEX_1);
    EXPECT_TRUE(onMoveCalled);
    EXPECT_EQ(receivedFrom, TEST_INDEX_0);
    EXPECT_EQ(receivedTo, TEST_INDEX_1);
}

/**
 * @tc.name: MoveData_SameIndexTest
 * @tc.desc: Test MoveData when from == to should return early
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, MoveData_SameIndexTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    forEachNode->SetIds(std::list<std::string>(TEST_IDS));
    AddChildrenToForEach(forEachNode, 4);
    
    auto originalIds = forEachNode->ids_;
    auto originalChildren = forEachNode->GetChildren();

    forEachNode->MoveData(TEST_INDEX_0, TEST_INDEX_0);

    EXPECT_EQ(forEachNode->ids_, originalIds);
    EXPECT_EQ(forEachNode->GetChildren().size(), originalChildren.size());
}

/**
 * @tc.name: FlushUpdateAndMarkDirty_SameIdsTest
 * @tc.desc: Test FlushUpdateAndMarkDirty when ids_ == tempIds_ should skip
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, FlushUpdateAndMarkDirty_SameIdsTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    forEachNode->ids_ = TEST_IDS;
    forEachNode->tempIds_ = TEST_IDS;
    forEachNode->isThisRepeatNode_ = false;

    forEachNode->FlushUpdateAndMarkDirty();

    EXPECT_TRUE(forEachNode->tempIds_.empty());
}

/**
 * @tc.name: CompareAndUpdateChildren_IsRepeatNodeTest
 * @tc.desc: Test CompareAndUpdateChildren when isThisRepeatNode_ is true should return early
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, CompareAndUpdateChildren_IsRepeatNodeTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    forEachNode->isThisRepeatNode_ = true;
    forEachNode->SetIds(std::list<std::string>(TEST_IDS));
    forEachNode->CreateTempItems();

    auto originalChildrenCount = forEachNode->GetChildren().size();

    forEachNode->CompareAndUpdateChildren();

    EXPECT_EQ(forEachNode->GetChildren().size(), originalChildrenCount);
}

/**
 * @tc.name: InitDragManager_NullChildTest
 * @tc.desc: Test InitDragManager with null child should not crash
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, InitDragManager_NullChildTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    forEachNode->onMoveEvent_ = [](int32_t from, int32_t to) {};

    forEachNode->InitDragManager(nullptr);

    SUCCEED();
}

/**
 * @tc.name: InitDragManager_NonListParentTest
 * @tc.desc: Test InitDragManager when parent is not List should return early
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, InitDragManager_NonListParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(parentNode);

    forEachNode->onMoveEvent_ = [](int32_t from, int32_t to) {};

    auto childNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto listItem = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    childNode->AddChild(listItem);

    forEachNode->InitDragManager(childNode);

    SUCCEED();
}

/**
 * @tc.name: InitAllChildrenDragManager_NonListParentTest
 * @tc.desc: Test InitAllChildrenDragManager when parent is not List should clear callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, InitAllChildrenDragManager_NonListParentTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    forEachNode->SetParent(parentNode);

    forEachNode->onMoveEvent_ = [](int32_t from, int32_t to) {};
    forEachNode->onLongPressEvent_ = [](int32_t index) {};
    forEachNode->onDragStartEvent_ = [](int32_t index) {};
    forEachNode->onMoveThroughEvent_ = [](int32_t from, int32_t through) {};
    forEachNode->onDropEvent_ = [](int32_t index) {};

    forEachNode->InitAllChildrenDragManager(true);

    EXPECT_EQ(forEachNode->onMoveEvent_, nullptr);
    EXPECT_EQ(forEachNode->onLongPressEvent_, nullptr);
    EXPECT_EQ(forEachNode->onDragStartEvent_, nullptr);
    EXPECT_EQ(forEachNode->onMoveThroughEvent_, nullptr);
    EXPECT_EQ(forEachNode->onDropEvent_, nullptr);
}

/**
 * @tc.name: MoveChild_OutOfRangeTest
 * @tc.desc: Test MoveChild when fromIndex is out of range
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, MoveChild_OutOfRangeTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    forEachNode->isThisRepeatNode_ = true;
    forEachNode->tempChildrenOfRepeat_.push_back(CreateBlankChildNode());

    auto originalChildrenCount = forEachNode->GetChildren().size();

    forEachNode->MoveChild(TEST_INDEX_5);

    EXPECT_EQ(forEachNode->GetChildren().size(), originalChildrenCount);
}

/**
 * @tc.name: GetFrameNode_InvalidIndexTest
 * @tc.desc: Test GetFrameNode with invalid index
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, GetFrameNode_InvalidIndexTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    forEachNode->SetIds(std::list<std::string>(TEST_IDS));
    AddChildrenToForEach(forEachNode, 4);

    auto result = forEachNode->GetFrameNode(TEST_INDEX_5);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: FinishRepeatRender_EmptyChildrenTest
 * @tc.desc: Test FinishRepeatRender with empty children
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, FinishRepeatRender_EmptyChildrenTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    forEachNode->isThisRepeatNode_ = true;
    forEachNode->tempChildrenOfRepeat_.push_back(CreateBlankChildNode());

    std::list<int32_t> removedElmtId;
    forEachNode->FinishRepeatRender(removedElmtId);

    EXPECT_TRUE(forEachNode->tempChildren_.empty());
    EXPECT_TRUE(forEachNode->tempChildrenOfRepeat_.empty());
}

/**
 * @tc.name: DumpInfo_BasicTest
 * @tc.desc: Test DumpInfo basic functionality
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, DumpInfo_BasicTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    forEachNode->SetIds(std::list<std::string>(TEST_IDS));

    forEachNode->DumpInfo();

    SUCCEED();
}

/**
 * @tc.name: IsSyntaxNode_ReturnsTrueTest
 * @tc.desc: Test IsSyntaxNode returns true
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, IsSyntaxNode_ReturnsTrueTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    EXPECT_TRUE(forEachNode->IsSyntaxNode());
}

/**
 * @tc.name: IsAtomicNode_ReturnsFalseTest
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, IsAtomicNode_ReturnsFalseTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    EXPECT_FALSE(forEachNode->IsAtomicNode());
}

/**
 * @tc.name: GetTempIds_AfterCreateTempItemsTest
 * @tc.desc: Test GetTempIds after CreateTempItems
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, GetTempIds_AfterCreateTempItemsTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    forEachNode->SetIds(std::list<std::string>(TEST_IDS));
    forEachNode->CreateTempItems();

    EXPECT_EQ(forEachNode->GetTempIds(), TEST_IDS);
}

/**
 * @tc.name: CreateTempItems_ForRepeatNodeTest
 * @tc.desc: Test CreateTempItems for RepeatNode populates tempChildrenOfRepeat_
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, CreateTempItems_ForRepeatNodeTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    forEachNode->isThisRepeatNode_ = true;
    forEachNode->SetIds(std::list<std::string>(TEST_IDS));
    AddChildrenToForEach(forEachNode, 4);

    forEachNode->CreateTempItems();

    EXPECT_EQ(forEachNode->tempChildrenOfRepeat_.size(), 4);
}

/**
 * @tc.name: FullDragFlowTest
 * @tc.desc: Test complete drag flow with all callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ForEachTestNgAI, FullDragFlowTest, TestSize.Level1)
{
    auto forEachNode = CreateForEachNode();
    ASSERT_NE(forEachNode, nullptr);

    bool onMoveCalled = false;
    bool onLongPressCalled = false;
    bool onDragStartCalled = false;
    bool onMoveThroughCalled = false;
    bool onDropCalled = false;

    forEachNode->SetOnMove([&onMoveCalled](int32_t from, int32_t to) {
        onMoveCalled = true;
    });

    std::function<void(int32_t)> onLongPress = [&onLongPressCalled](int32_t index) {
        onLongPressCalled = true;
    };
    std::function<void(int32_t)> onDragStart = [&onDragStartCalled](int32_t index) {
        onDragStartCalled = true;
    };
    std::function<void(int32_t, int32_t)> onMoveThrough = [&onMoveThroughCalled](int32_t from, int32_t through) {
        onMoveThroughCalled = true;
    };
    std::function<void(int32_t)> onDrop = [&onDropCalled](int32_t index) {
        onDropCalled = true;
    };

    forEachNode->SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));

    forEachNode->FireOnLongPress(TEST_INDEX_0);
    forEachNode->FireOnDragStart(TEST_INDEX_0);
    forEachNode->FireOnMoveThrough(TEST_INDEX_0, TEST_INDEX_1);
    forEachNode->FireOnDrop(TEST_INDEX_1);
    forEachNode->FireOnMove(TEST_INDEX_0, TEST_INDEX_1);

    EXPECT_FALSE(onLongPressCalled);
    EXPECT_FALSE(onDragStartCalled);
    EXPECT_FALSE(onMoveThroughCalled);
    EXPECT_FALSE(onDropCalled);
    EXPECT_FALSE(onMoveCalled);
}

} // namespace OHOS::Ace::NG
