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

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "frameworks/core/components_ng/syntax/arkoala_lazy_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class TestUINode : public UINode {
    DECLARE_ACE_TYPE(TestUINode, UINode);

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestUINode(int32_t nodeId) : UINode("TestUINode", nodeId) {}

    ~TestUINode() override = default;
};

class ComponentPatternTestNg : public TestNG {
public:
    RefPtr<ArkoalaLazyNode> CreateLazyForEachNode(int32_t nodeId)
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto lazyForEachNode = AceType::MakeRefPtr<ArkoalaLazyNode>(nodeId);
        stack->Push(lazyForEachNode);
        lazyForEachNode->SetCallbacks(createItemCb_, updateRangeCb_);
        return lazyForEachNode;
    }

    RefPtr<ArkoalaLazyNode> CreateRepeatNode(int32_t nodeId)
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto repeatNode = AceType::MakeRefPtr<ArkoalaLazyNode>(nodeId, true);
        stack->Push(repeatNode);
        repeatNode->SetCallbacks(createItemCb_, updateRangeCb_);
        return repeatNode;
    }

    void CreateChildren(RefPtr<ArkoalaLazyNode>& lazyNode, int32_t totalCount)
    {
        for (int i = 0; i < totalCount; ++i) {
            lazyNode->GetFrameChildByIndex(i, true, false, true);
        }
        lazyNode->SetTotalCount(totalCount);
    }

    RefPtr<TestUINode> CreateTestUINode(int32_t nodeId)
    {
        return AceType::MakeRefPtr<TestUINode>(nodeId);
    }

    RefPtr<FrameNode> CreateFrameNode(int32_t nodeId)
    {
        return ColumnModelNG::CreateFrameNode(nodeId);
    }

    std::string DumpUINode(const RefPtr<UINode>& node) const
    {
        return (node == nullptr) ? "null" : node->GetTag() + "(" + std::to_string(node->GetId()) + ")";
    }

    int32_t GetNextId()
    {
        return ++nodeId_;
    }

    int32_t nodeId_ = 0;

    ArkoalaLazyNode::CreateItemCb createItemCb_ = [this](int32_t idx) {
        RefPtr<TestUINode> uiNode = CreateTestUINode(GetNextId());
        auto columnNode = ColumnModelNG::CreateFrameNode(GetNextId());
        uiNode->AddChild(columnNode);
        return uiNode;
    };
    ArkoalaLazyNode::UpdateRangeCb updateRangeCb_ = [](
        int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool isLoop) {};
};

using UpdateRangeCb = std::function<void(int32_t, int32_t, int32_t, int32_t, bool)>;

const int32_t INDEX_0 = 0;
const int32_t INDEX_1 = 1;
const int32_t INDEX_2 = 2;
const int32_t INDEX_8 = 8;
const int32_t INDEX_9 = 9;

/**
 * @tc.name: ComponentPatternTestNg_DoSetActiveChildRange001
 * @tc.desc: Test ArkoalaLazyNode DoSetActiveChildRange.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_DoSetActiveChildRange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);
    lazyNode->activeRangeParam_ = { INDEX_2, INDEX_2, totalCount, totalCount };

    /**
     * @tc.steps: step2. DoSetActiveChildRange
     * @tc.expected: lazyNode->activeRangeParam_ is as the same as newParam
     */
    int32_t cachedCount = 1;
    int32_t result_start = INDEX_1 - cachedCount;
    int32_t result_end = INDEX_9 + cachedCount;
    int32_t result_Count = INDEX_0;
    ActiveRangeParam newParam = { result_start, result_end, result_Count, result_Count };
    lazyNode->DoSetActiveChildRange(INDEX_1, INDEX_9, cachedCount, cachedCount, true);
    EXPECT_EQ(lazyNode->activeRangeParam_, newParam);
}

/**
 * @tc.name: ComponentPatternTestNg_DoSetActiveChildRange002
 * @tc.desc: Test ArkoalaLazyNode DoSetActiveChildRange.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_DoSetActiveChildRange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);
    int32_t cachedCount = 1;
    int32_t result_start = INDEX_1 - cachedCount;
    int32_t result_end = INDEX_9 + cachedCount;
    int32_t result_Count = INDEX_0;
    ActiveRangeParam activeRangeParam = { result_start, result_end, result_Count, result_Count };
    lazyNode->activeRangeParam_ = activeRangeParam;
    lazyNode->needBuildAll_ = true;

    /**
     * @tc.steps: step2. DoSetActiveChildRange
     * @tc.expected: DoSetActiveChildRange early returns, that causes lazyNode->needBuildAll_ is not false
     */
    lazyNode->DoSetActiveChildRange(INDEX_1, INDEX_9, cachedCount, cachedCount, true);
    EXPECT_TRUE(lazyNode->needBuildAll_);
}

/**
 * @tc.name: ComponentPatternTestNg_DoSetActiveChildRange001
 * @tc.desc: Test ArkoalaLazyNode DoSetActiveChildRange.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_DoSetActiveChildRange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);
    lazyNode->activeRangeParam_ = { INDEX_2, INDEX_2, totalCount, totalCount };
    lazyNode->SetIsLoop(false);

    /**
     * @tc.steps: step2. assign updateRange_
     * @tc.expected: updateRange_ assign successfully
     */
    UpdateRangeCb updateRange = nullptr;
    lazyNode->updateRange_ = std::move(updateRange);

    /**
     * @tc.steps: step3. DoSetActiveChildRange
     * @tc.expected: lazyNode->updateRange_ is nullptr
     */
    int32_t cachedCount = 1;
    lazyNode->DoSetActiveChildRange(INDEX_1, INDEX_9, cachedCount, cachedCount, true);
    EXPECT_EQ(lazyNode->updateRange_, nullptr);
}

/**
 * @tc.name: ComponentPatternTestNg_UpdateMoveFromTo001
 * @tc.desc: Test ArkoalaLazyNode UpdateMoveFromTo.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_UpdateMoveFromTo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);

    /**
     * @tc.steps: step2. assign moveFromTo_
     * @tc.expected: moveFromTo_ assign successfully
     */
    lazyNode->moveFromTo_ = { INDEX_8, INDEX_9 };
    std::pair<int32_t, int32_t> movePair = { INDEX_8, INDEX_2 };
    std::optional<std::pair<int32_t, int32_t>> resultMoveFromTo = movePair;

    /**
     * @tc.steps: step3. UpdateMoveFromTo
     * @tc.expected: lazyNode->moveFromTo_ is not reset
     */
    lazyNode->UpdateMoveFromTo(INDEX_1, INDEX_2);
    EXPECT_EQ(lazyNode->moveFromTo_, resultMoveFromTo);
}

/**
 * @tc.name: ComponentPatternTestNg_UpdateMoveFromTo002
 * @tc.desc: Test ArkoalaLazyNode UpdateMoveFromTo.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_UpdateMoveFromTo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);

    /**
     * @tc.steps: step2. assign moveFromTo_
     * @tc.expected: moveFromTo_ assign successfully
     */
    lazyNode->moveFromTo_ = { INDEX_8, INDEX_9 };

    /**
     * @tc.steps: step3. UpdateMoveFromTo
     * @tc.expected: lazyNode->moveFromTo_ is reset
     */
    lazyNode->UpdateMoveFromTo(INDEX_1, INDEX_8);
    EXPECT_FALSE(lazyNode->moveFromTo_);
}

/**
 * @tc.name: ComponentPatternTestNg_UpdateItemsForOnMove001
 * @tc.desc: Test ArkoalaLazyNode UpdateItemsForOnMove.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_UpdateItemsForOnMove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);

    /**
     * @tc.steps: step2. assign node4Index_
     * @tc.expected: node4Index_ assign successfully
     */
    lazyNode->node4Index_.Clear();
    auto repeatNode = CreateRepeatNode(GetNextId());
    lazyNode->node4Index_.Put(0, repeatNode);

    /**
     * @tc.steps: step3. reset moveFromTo_
     * @tc.expected: moveFromTo_ reset successfully
     */
    lazyNode->moveFromTo_.reset();

    /**
     * @tc.steps: step4. UpdateItemsForOnMove
     * @tc.expected: moveFromTo_ is false
     */
    lazyNode->UpdateItemsForOnMove();
    EXPECT_NE(lazyNode->node4Index_.Size(), 0);
}

/**
 * @tc.name: ComponentPatternTestNg_UpdateItemsForOnMove002
 * @tc.desc: Test ArkoalaLazyNode UpdateItemsForOnMove.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_UpdateItemsForOnMove002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);

    /**
     * @tc.steps: step2. assign node4Index_
     * @tc.expected: node4Index_ assign successfully
     */
    lazyNode->node4Index_.Clear();
    auto repeatNode = CreateRepeatNode(GetNextId());
    lazyNode->node4Index_.Put(0, repeatNode);

    /**
     * @tc.steps: step3. assign moveFromTo_
     * @tc.expected: moveFromTo_ assign successfully
     */
    lazyNode->moveFromTo_ = { INDEX_1, INDEX_1 };

    /**
     * @tc.steps: step4. UpdateItemsForOnMove
     * @tc.expected: from == to
     */
    lazyNode->UpdateItemsForOnMove();
    EXPECT_NE(lazyNode->node4Index_.Size(), 0);
}

/**
 * @tc.name: ComponentPatternTestNg_UpdateItemsForOnMove003
 * @tc.desc: Test ArkoalaLazyNode UpdateItemsForOnMove.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_UpdateItemsForOnMove003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);

    /**
     * @tc.steps: step2. assign node4Index_
     * @tc.expected: node4Index_ assign successfully
     */
    lazyNode->node4Index_.Clear();
    lazyNode->node4Index_.Put(0, nullptr);

    /**
     * @tc.steps: step3. assign moveFromTo_
     * @tc.expected: moveFromTo_ assign successfully
     */
    lazyNode->moveFromTo_ = { INDEX_1, INDEX_8 };

    /**
     * @tc.steps: step4. UpdateItemsForOnMove
     * @tc.expected: node is nullptr
     */
    lazyNode->UpdateItemsForOnMove();
    EXPECT_EQ(lazyNode->node4Index_.Size(), 0);
}

/**
 * @tc.name: ComponentPatternTestNg_UpdateItemsForOnMove004
 * @tc.desc: Test ArkoalaLazyNode UpdateMoveFromTo.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_UpdateItemsForOnMove004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);

    /**
     * @tc.steps: step2. assign node4Index_
     * @tc.expected: node4Index_ assign successfully
     */
    lazyNode->node4Index_.Clear();
    auto repeatNode = CreateRepeatNode(GetNextId());
    lazyNode->node4Index_.Put(0, repeatNode);

    /**
     * @tc.steps: step3. assign moveFromTo_
     * @tc.expected: moveFromTo_ assign successfully
     */
    lazyNode->moveFromTo_ = { INDEX_1, INDEX_8 };

    /**
     * @tc.steps: step4. UpdateItemsForOnMove
     * @tc.expected: index < rangeStart
     */
    lazyNode->UpdateItemsForOnMove();
    EXPECT_EQ(lazyNode->node4Index_.begin()->first, 0);
}

/**
 * @tc.name: ComponentPatternTestNg_UpdateItemsForOnMove005
 * @tc.desc: Test ArkoalaLazyNode UpdateItemsForOnMove.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_UpdateItemsForOnMove005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);

    /**
     * @tc.steps: step2. assign node4Index_
     * @tc.expected: node4Index_ assign successfully
     */
    lazyNode->node4Index_.Clear();
    auto repeatNode = CreateRepeatNode(GetNextId());
    lazyNode->node4Index_.Put(INDEX_9, repeatNode);

    /**
     * @tc.steps: step3. assign moveFromTo_
     * @tc.expected: moveFromTo_ assign successfully
     */
    lazyNode->moveFromTo_ = { INDEX_1, INDEX_8 };

    /**
     * @tc.steps: step4. UpdateItemsForOnMove
     * @tc.expected: index > rangeEnd
     */
    lazyNode->UpdateItemsForOnMove();
    EXPECT_EQ(lazyNode->node4Index_.begin()->first, INDEX_9);
}

/**
 * @tc.name: ComponentPatternTestNg_UpdateItemsForOnMove006
 * @tc.desc: Test ArkoalaLazyNode UpdateMoveFromTo.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_UpdateItemsForOnMove006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);

    /**
     * @tc.steps: step2. assign node4Index_
     * @tc.expected: node4Index_ assign successfully
     */
    lazyNode->node4Index_.Clear();
    auto repeatNode = CreateRepeatNode(GetNextId());
    lazyNode->node4Index_.Put(INDEX_2, repeatNode);

    /**
     * @tc.steps: step3. assign moveFromTo_
     * @tc.expected: moveFromTo_ assign successfully
     */
    lazyNode->moveFromTo_ = { INDEX_2, INDEX_8 };

    /**
     * @tc.steps: step4. UpdateItemsForOnMove
     * @tc.expected: lazyNode->node4Index_ put newIndex
     */
    lazyNode->UpdateItemsForOnMove();
    EXPECT_NE(lazyNode->node4Index_.begin()->first, INDEX_2);
}

/**
 * @tc.name: ComponentPatternTestNg_ConvertFromToIndex001
 * @tc.desc: Test ArkoalaLazyNode ConvertFromToIndex.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_ConvertFromToIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);

    /**
     * @tc.steps: step2. assign moveFromTo_
     * @tc.expected: moveFromTo_ assign successfully
     */
    lazyNode->moveFromTo_ = { INDEX_1, INDEX_8 };

    /**
     * @tc.steps: step3. ConvertFromToIndex
     * @tc.expected: moveFromTo_.value().second == index
     */
    auto result = lazyNode->ConvertFromToIndex(INDEX_8);
    EXPECT_EQ(result, INDEX_1);
}

/**
 * @tc.name: ComponentPatternTestNg_ConvertFromToIndex002
 * @tc.desc: Test ArkoalaLazyNode ConvertFromToIndex.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPatternTestNg_ConvertFromToIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyNode
     * @tc.expected: lazyNode create successfully
     */
    int32_t totalCount = 50;
    auto lazyNode = CreateLazyForEachNode(GetNextId());
    CreateChildren(lazyNode, totalCount);

    /**
     * @tc.steps: step2. assign moveFromTo_
     * @tc.expected: moveFromTo_ assign successfully
     */
    lazyNode->moveFromTo_ = { INDEX_1, INDEX_8 };

    /**
     * @tc.steps: step3. ConvertFromToIndex
     * @tc.expected: moveFromTo_.value().first <= index && index < moveFromTo_.value().second
     */
    auto result = lazyNode->ConvertFromToIndex(INDEX_1);
    EXPECT_EQ(result, INDEX_2);
}

}