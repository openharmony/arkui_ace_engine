/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <optional>
#include <utility>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/components_ng/test/mock/syntax/mock_lazy_for_each_actuator.h"
#include "core/components_ng/test/mock/syntax/mock_lazy_for_each_builder.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::list<std::optional<std::string>> LAZY_FOR_EACH_NODE_IDS = { "0", "1", "2", "3", "4", "5", "6" };
const std::list<std::optional<int32_t>> LAZY_FOR_EACH_NODE_IDS_INT = { 0, 1, 2, 3, 4, 5, 6 };
const std::unordered_map<int32_t, std::optional<std::string>> LAZY_FOR_EACH_CACHED_ITEMS = { { 0, "0" }, { 1, "1" } };
const std::list<int32_t> LAZY_FOR_EACH_ITEMS = { 0, 1, 2, 3, 4, 5 };
constexpr bool IS_ATOMIC_NODE = false;
constexpr int32_t NEW_START_ID = 0;
constexpr int32_t NEW_END_ID = 6;
constexpr int32_t INDEX_MIDDLE = 3;
constexpr int32_t INDEX_MIDDLE_2 = 4;
constexpr int32_t INDEX_2 = 2;
constexpr int32_t INDEX_8 = 8;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t DEFAULT_INDEX = 0;
constexpr int32_t INDEX_4 = 4;
constexpr int32_t INDEX_3 = 3;
constexpr int32_t INDEX_5 = 5;
constexpr int32_t INDEX_0 = 0;
constexpr int32_t CACHE_COUNT = 5;
constexpr int32_t START_ID = 7;
constexpr int32_t INVALID_START_ID_LESS_THAN_0 = -1;
constexpr int32_t INVALID_START_ID_GREATER_THAN_TOTAL = 7;
constexpr int32_t INDEX_GREATER_THAN_END_INDEX = 20;
constexpr int32_t INDEX_LESS_THAN_START_INDEX = -1;
constexpr int32_t INDEX_EQUAL_WITH_START_INDEX = 1;
constexpr int32_t INDEX_EQUAL_WITH_START_INDEX_DELETED = -1;
constexpr int32_t LAZY_FOR_EACH_NODE_ID = 1;
} // namespace

class LazyForEachSyntaxTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;

    RefPtr<FrameNode> CreateNode(const std::string& tag);

    static void UpdateItems(
        const RefPtr<LazyForEachNode>& lazyForEachNode, const RefPtr<LazyForEachActuator>& mockLazyForEachActuator)
    {
        /**
         * @tc.steps: step1. Add child found in generatedItem_.
         */
        auto ids = LAZY_FOR_EACH_NODE_IDS;
        auto builder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);
        for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
            builder->GetChildByIndex(iter.value_or(0), true);
        }
    }

    static RefPtr<LazyForEachNode> CreateLazyForEachNode()
    {
        /**
         * @tc.steps: step1. Create Text and push it to view stack processor.
         * @tc.expected: Make Text as LazyForEach parent.
         */
        auto pattern = AceType::MakeRefPtr<Pattern>();
        auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, pattern);
        pattern->AttachToFrameNode(frameNode);
        ViewStackProcessor::GetInstance()->Push(frameNode);

        /**
         * @tc.steps: step2. Invoke lazyForEach Create function.
         * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
         */
        LazyForEachModelNG lazyForEach;
        const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
            AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
        lazyForEach.Create(mockLazyForEachActuator);
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
        /**
         * @tc.steps: step3. Add children items to lazyForEachNode.
         */
        UpdateItems(lazyForEachNode, mockLazyForEachActuator);
        return lazyForEachNode;
    }
};

void LazyForEachSyntaxTestNg::SetUp()
{
    MockPipelineBase::SetUp();
}

void LazyForEachSyntaxTestNg::TearDown()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> LazyForEachSyntaxTestNg::CreateNode(const std::string& tag)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    return frameNode;
}

/**
 * @tc.name: LazyForEachSyntaxCreateTest001
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachSyntaxCreateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as LazyForEach parent.
     */
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr && lazyForEachNode->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG);

    EXPECT_EQ(lazyForEachNode->IsAtomicNode(), IS_ATOMIC_NODE);
    EXPECT_EQ(lazyForEachNode->FrameCount(), 0);
}

/**
 * @tc.name: ForEachSyntaxCreateTest002
 * @tc.desc: Create LazyForEach and its parent node is Tabs.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxCreateTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs and push it to view stack processor.
     * @tc.expected: Make Tabs as LazyForEach parent.
     */
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: LazyForEachNode will not be created when its parent is Tabs.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(lazyForEachNode, nullptr);
}

/**
 * @tc.name: ForEachSyntaxUpdateTest003
 * @tc.desc: Create LazyForEach and its Update its Items.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxUpdateTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as LazyForEach parent.
     */
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr && lazyForEachNode->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG);
}

/**
 * @tc.name: ForEachSyntaxAddDataFunctionTest004
 * @tc.desc: Create LazyForEach, update its Items and invoke OnDataAdded function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxFunctionTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as LazyForEach parent.
     */
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr && lazyForEachNode->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG);

    UpdateItems(lazyForEachNode, mockLazyForEachActuator);

    /**
     * @tc.steps: step3. Add index which is less than start index.
     * @tc.expected: LazyForEachNode ids_ will not be added.
     */
    lazyForEachNode->OnDataAdded(INDEX_LESS_THAN_START_INDEX);
    EXPECT_EQ(lazyForEachNode->ids_.size(), LAZY_FOR_EACH_NODE_IDS.size());

    /**
     * @tc.steps: step4. Add index which is greater than end index.
     * @tc.expected: LazyForEachNode ids_ will not be added.
     */
    lazyForEachNode->OnDataAdded(INDEX_GREATER_THAN_END_INDEX);
    EXPECT_EQ(lazyForEachNode->ids_.size(), LAZY_FOR_EACH_NODE_IDS.size());

    /**
     * @tc.steps: step5. Add index which is equal with start index.
     * @tc.expected: LazyForEachNode ids_ will be added the item.
     */
    lazyForEachNode->OnDataAdded(INDEX_EQUAL_WITH_START_INDEX);
    auto newIdsSize = LAZY_FOR_EACH_NODE_IDS.size();
    EXPECT_EQ(lazyForEachNode->ids_.size(), newIdsSize);
}

/**
 * @tc.name: ForEachSyntaxReloadDataFunctionTest005
 * @tc.desc: Create LazyForEach, update its Items and invoke OnDataReloaded function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxReloadDataFunctionTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as LazyForEach parent.
     */
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr && lazyForEachNode->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG);

    UpdateItems(lazyForEachNode, mockLazyForEachActuator);

    /**
     * @tc.steps: step3. Invoke OnDataReloaded.
     * @tc.expected: LazyForEachNode ids_ will be cleared.
     */
    lazyForEachNode->OnDataReloaded();
    EXPECT_FALSE(lazyForEachNode->ids_.empty());
}

/**
 * @tc.name: ForEachSyntaxDeleteDataFunctionTest006
 * @tc.desc: Create LazyForEach, update its Items and invoke OnDataDeleted function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxDeleteDataFunctionTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as LazyForEach parent.
     */
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr && lazyForEachNode->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG);

    UpdateItems(lazyForEachNode, mockLazyForEachActuator);

    /**
     * @tc.steps: step3. Delete index which is greater than end index.
     * @tc.expected: LazyForEachNode ids_ will not be deleted.
     */
    lazyForEachNode->OnDataDeleted(INDEX_GREATER_THAN_END_INDEX);
    EXPECT_EQ(lazyForEachNode->ids_.size(), LAZY_FOR_EACH_NODE_IDS.size());

    /**
     * @tc.steps: step4. Delete index which is less than start index.
     * @tc.expected: LazyForEachNode ids_ will not be deleted.
     */
    lazyForEachNode->OnDataDeleted(INDEX_LESS_THAN_START_INDEX);
    EXPECT_EQ(lazyForEachNode->ids_.size(), LAZY_FOR_EACH_NODE_IDS.size());

    /**
     * @tc.steps: step5. Delete index which is equal with start index.
     * @tc.expected: LazyForEachNode ids_ will be deleted the item.
     */
    lazyForEachNode->OnDataDeleted(INDEX_EQUAL_WITH_START_INDEX_DELETED);
    auto newIdsSize = LAZY_FOR_EACH_NODE_IDS.size();
    EXPECT_EQ(lazyForEachNode->ids_.size(), newIdsSize);
}

/**
 * @tc.name: ForEachSyntaxChangeDataFunctionTest007
 * @tc.desc: Create LazyForEach, update its Items and invoke OnDataChanged function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxChangeDataFunctionTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as LazyForEach parent.
     */
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr && lazyForEachNode->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG);

    UpdateItems(lazyForEachNode, mockLazyForEachActuator);

    /**
     * @tc.steps: step3. Change index which is less than start index.
     * @tc.expected: changeIndex is out of range, ignored.
     */
    lazyForEachNode->OnDataChanged(INDEX_LESS_THAN_START_INDEX);
    EXPECT_EQ(lazyForEachNode->ids_.size(), LAZY_FOR_EACH_NODE_IDS.size());

    /**
     * @tc.steps: step4. Change index which is greater than end index.
     * @tc.expected: changeIndex is out of range, ignored.
     */
    lazyForEachNode->OnDataChanged(INDEX_GREATER_THAN_END_INDEX);
    EXPECT_EQ(lazyForEachNode->ids_.size(), LAZY_FOR_EACH_NODE_IDS.size());

    /**
     * @tc.steps: step5. Change index which is in the middle with start and end.
     * @tc.expected: changeIndex is not out of range, change the index data.
     */
    lazyForEachNode->OnDataChanged(INDEX_MIDDLE);
    EXPECT_EQ(lazyForEachNode->ids_.size(), LAZY_FOR_EACH_NODE_IDS.size());
}

/**
 * @tc.name: ForEachSyntaxMoveDataFunctionTest008
 * @tc.desc: Create LazyForEach, update its Items and invoke OnDataMoved function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxMoveDataFunctionTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as LazyForEach parent.
     */
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr && lazyForEachNode->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG);

    UpdateItems(lazyForEachNode, mockLazyForEachActuator);

    /**
     * @tc.steps: step3. From index is less than start index, and to index is greater than end index.
     * @tc.expected: Both out of range, ignored.
     */
    lazyForEachNode->OnDataMoved(INDEX_LESS_THAN_START_INDEX, INDEX_GREATER_THAN_END_INDEX);
    EXPECT_EQ(lazyForEachNode->ids_.size(), LAZY_FOR_EACH_NODE_IDS.size());

    /**
     * @tc.steps: step4. From index is in middle of range, and to index is greater than end index..
     */
    lazyForEachNode->OnDataMoved(INDEX_MIDDLE, INDEX_GREATER_THAN_END_INDEX);
    EXPECT_EQ(lazyForEachNode->ids_.size(), LAZY_FOR_EACH_NODE_IDS.size());

    /**
     * @tc.steps: step5. From index is in middle of range, and to index is in middle of range.
     */
    lazyForEachNode->OnDataMoved(INDEX_MIDDLE_2, INDEX_MIDDLE);
    EXPECT_EQ(lazyForEachNode->ids_.size(), LAZY_FOR_EACH_NODE_IDS.size());

    /**
     * @tc.steps: step6. From index is less than start index, and to index is in middle of range.
     */
    lazyForEachNode->OnDataMoved(INDEX_LESS_THAN_START_INDEX, INDEX_MIDDLE);
    EXPECT_EQ(lazyForEachNode->ids_.size(), LAZY_FOR_EACH_NODE_IDS.size());
}

/**
 * @tc.name: ForEachSyntaxWrapperBuilderTest009
 * @tc.desc: Create LazyForEach, update its Items and update LazyLayoutWrapperBuilder layout range.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxWrapperBuilderTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as LazyForEach parent.
     */
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr && lazyForEachNode->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG);

    UpdateItems(lazyForEachNode, mockLazyForEachActuator);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapper.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step4. Invoke AdjustLayoutWrapperTree, update lazyLayoutWrapperBuilder index range and its
     * currentChildCount_.
     * @tc.expected: lazyLayoutWrapperBuilder preNodeIds_ is equal with lazyForEachNode ids_.
     */
    lazyForEachNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);
    auto lazyLayoutWrapperBuilder =
        AceType::DynamicCast<LazyLayoutWrapperBuilder>(parentLayoutWrapper->layoutWrapperBuilder_);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), LAZY_FOR_EACH_NODE_IDS.size());
    EXPECT_EQ(lazyLayoutWrapperBuilder->preNodeIds_, LAZY_FOR_EACH_NODE_IDS);
}

/**
 * @tc.name: ForEachSyntaxWrapperBuilderTest010
 * @tc.desc: Create LazyForEach, update its Items and update LazyLayoutWrapperBuilder layout range.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxWrapperBuilderTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Swiper and push it to view stack processor.
     * @tc.expected: Make Swiper as LazyForEach parent.
     */
    auto frameNode = CreateNode(V2::SWIPER_ETS_TAG);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr && lazyForEachNode->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG);

    UpdateItems(lazyForEachNode, mockLazyForEachActuator);

    /**
     * @tc.steps: step3. Create Parent LayoutWrapper.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto parentLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step4. Invoke AdjustLayoutWrapperTree, update lazyLayoutWrapperBuilder index range and its
     * currentChildCount_.
     * @tc.expected: lazyLayoutWrapperBuilder preNodeIds_ is equal with lazyForEachNode ids_.
     */
    lazyForEachNode->AdjustLayoutWrapperTree(parentLayoutWrapper, false, false);

    auto lazyLayoutWrapperBuilder =
        AceType::DynamicCast<LazyLayoutWrapperBuilder>(parentLayoutWrapper->layoutWrapperBuilder_);
    EXPECT_EQ(parentLayoutWrapper->GetTotalChildCount(), static_cast<int32_t>(LAZY_FOR_EACH_NODE_IDS.size()));
    EXPECT_EQ(lazyLayoutWrapperBuilder->preNodeIds_, LAZY_FOR_EACH_NODE_IDS);
}

/**
 * @tc.name: ForEachSyntaxWrapperBuilderOnExpandChildLayoutWrapperTest001
 * @tc.desc: Create LazyForEach, and invoke OnExpandChildLayoutWrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxWrapperBuilderOnExpandChildLayoutWrapperTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyLayoutWrapperBuilder and invoke OnExpandChildLayoutWrapper when the childWrappers_
     * is empty.
     * @tc.expected: Create childWrapper and add it to childWrappers_.
     */
    auto lazyForEachNode = CreateLazyForEachNode();
    auto lazyLayoutWrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(
        lazyForEachNode->builder_, AceType::WeakClaim(AceType::RawPtr(lazyForEachNode)));
    lazyLayoutWrapperBuilder->OnExpandChildLayoutWrapper();
    lazyLayoutWrapperBuilder->AdjustGridOffset();
    EXPECT_EQ(lazyLayoutWrapperBuilder->childWrappers_.size(), LAZY_FOR_EACH_NODE_IDS.size());

    /**
     * @tc.steps: step2. Invoke OnExpandChildLayoutWrapper when the childWrappers_ is not empty.
     * @tc.expected: Return childWrappers_ directly.
     */
    EXPECT_EQ(lazyLayoutWrapperBuilder->OnExpandChildLayoutWrapper().size(), LAZY_FOR_EACH_NODE_IDS.size());
    EXPECT_FALSE(lazyLayoutWrapperBuilder->childWrappers_.empty());

    /**
     * @tc.steps: step3. Invoke OnExpandChildLayoutWrapper when the childWrappers_ size is not equal with total.
     * @tc.expected: Return childWrappers_ directly after clear it.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    lazyLayoutWrapperBuilder->childWrappers_.push_back(
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty()));
    lazyLayoutWrapperBuilder->OnExpandChildLayoutWrapper();
    EXPECT_TRUE(lazyLayoutWrapperBuilder->childWrappers_.empty());
}

/**
 * @tc.name: ForEachSyntaxWrapperBuilderOnGetOrCreateWrapperByIndexTest002
 * @tc.desc: Create LazyForEach, and invoke OnGetOrCreateWrapperByIndex.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxWrapperBuilderOnExpandChildLayoutWrapperTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyLayoutWrapperBuilder and invoke OnExpandChildLayoutWrapper when the childWrappers_
     * is empty.
     * @tc.expected: Create childWrapper and add it to childWrappers_.
     */
    auto lazyForEachNode = CreateLazyForEachNode();
    auto lazyLayoutWrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(
        lazyForEachNode->builder_, AceType::WeakClaim(AceType::RawPtr(lazyForEachNode)));
    lazyLayoutWrapperBuilder->OnExpandChildLayoutWrapper();

    /**
     * @tc.steps: step2. Invoke OnGetOrCreateWrapperByIndex when the index is invalid or not.
     * @tc.expected: Return nullptr when index is invalid and return the corresponding wrapper when it is valid.
     */
    EXPECT_EQ(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INVALID_START_ID_LESS_THAN_0), nullptr);
    EXPECT_EQ(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INVALID_START_ID_GREATER_THAN_TOTAL), nullptr);
    ASSERT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_2), nullptr);

    /**
     * @tc.steps: step3. Invoke OnGetOrCreateWrapperByIndex when the startIndex_ is null.
     */
    lazyLayoutWrapperBuilder->startIndex_ = std::nullopt;
    ASSERT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_2), nullptr);
    EXPECT_EQ(lazyLayoutWrapperBuilder->startIndex_.value_or(DEFAULT_INDEX), INDEX_2);
    EXPECT_EQ(lazyLayoutWrapperBuilder->endIndex_.value_or(DEFAULT_INDEX), INDEX_2);

    /**
     * @tc.steps: step4. Invoke OnGetOrCreateWrapperByIndex when the index is not in the range of the starIndex and
     * endIndex.
     */
    EXPECT_EQ(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_4), nullptr);
    EXPECT_EQ(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_0), nullptr);

    /**
     * @tc.steps: step5. Invoke OnGetOrCreateWrapperByIndex when the index is not in the range of the starIndex and
     * endIndex.
     */
    EXPECT_EQ(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_4), nullptr);
    EXPECT_EQ(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_0), nullptr);

    /**
     * @tc.steps: step6. Invoke OnGetOrCreateWrapperByIndex when the index is not in the range of the starIndex and
     * endIndex.
     */
    lazyLayoutWrapperBuilder->UpdateIndexRange(INDEX_2, INDEX_8, LAZY_FOR_EACH_NODE_IDS);
    lazyLayoutWrapperBuilder->startIndex_ = std::nullopt;
    ASSERT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_4), nullptr);
    lazyLayoutWrapperBuilder->UpdateIndexRange(INDEX_2, INDEX_8, LAZY_FOR_EACH_NODE_IDS);
    lazyLayoutWrapperBuilder->startIndex_ = std::nullopt;
    ASSERT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_1), nullptr);
    ASSERT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_0), nullptr);
}

/**
 * @tc.name: ForEachSyntaxWrapperBuilderSwapDirtyAndUpdateBuildCacheTest003
 * @tc.desc: Create LazyForEach, and invoke SwapDirtyAndUpdateBuildCache.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxWrapperBuilderSwapDirtyAndUpdateBuildCacheTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyLayoutWrapperBuilder and invoke SwapDirtyAndUpdateBuildCache when the childWrappers_
     * is empty or not.
     */
    auto lazyForEachNode = CreateLazyForEachNode();
    auto lazyLayoutWrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(
        lazyForEachNode->builder_, AceType::WeakClaim(AceType::RawPtr(lazyForEachNode)));
    EXPECT_EQ(lazyLayoutWrapperBuilder->startIndex_.value_or(DEFAULT_INDEX), NEW_START_ID);
    EXPECT_EQ(lazyLayoutWrapperBuilder->endIndex_.value_or(DEFAULT_INDEX), NEW_START_ID);

    lazyLayoutWrapperBuilder->OnExpandChildLayoutWrapper();
    lazyLayoutWrapperBuilder->SwapDirtyAndUpdateBuildCache();
    EXPECT_EQ(lazyLayoutWrapperBuilder->endIndex_.value_or(DEFAULT_INDEX), NEW_END_ID);

    /**
     * @tc.steps: step1. Create lazyLayoutWrapperBuilder and invoke SwapDirtyAndUpdateBuildCache when cacheCount is not
     * 0.
     */
    auto lazyForEachNode1 = CreateLazyForEachNode();
    auto lazyLayoutWrapperBuilder1 = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(
        lazyForEachNode1->builder_, AceType::WeakClaim(AceType::RawPtr(lazyForEachNode1)));
    lazyLayoutWrapperBuilder1->OnExpandChildLayoutWrapper();
    /**
     * @tc.steps: step2. Invoke SwapDirtyAndUpdateBuildCache when cacheCount is not empty and frontNodeIds is not empty
     * but backNodeIds is not empty.
     */
    lazyLayoutWrapperBuilder1->SetCacheCount(CACHE_COUNT);
    lazyLayoutWrapperBuilder1->SwapDirtyAndUpdateBuildCache();

    /**
     * @tc.steps: step3. Set  [3, 5] is active.
     */
    auto lazyForEachNode2 = CreateLazyForEachNode();
    auto lazyLayoutWrapperBuilder2 = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(
        lazyForEachNode2->builder_, AceType::WeakClaim(AceType::RawPtr(lazyForEachNode2)));
    lazyLayoutWrapperBuilder2->OnExpandChildLayoutWrapper();
    auto childWrapper = lazyLayoutWrapperBuilder2->childWrappers_;
    auto childWrapperIter = childWrapper.begin();
    int32_t index = 0;
    while (childWrapperIter != childWrapper.end()) {
        if (index >= INDEX_3 && index <= INDEX_5) {
            (*childWrapperIter)->SetActive(true);
        }
        index++;
        childWrapperIter++;
    }
    lazyLayoutWrapperBuilder2->SetCacheCount(CACHE_COUNT);
    lazyLayoutWrapperBuilder2->SwapDirtyAndUpdateBuildCache();
}

/**
 * @tc.name: ForEachSyntaxWrapperBuilderOnGetOrCreateWrapperByIndexTest004
 * @tc.desc: Create LazyForEach, and invoke OnGetOrCreateWrapperByIndex.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxWrapperBuilderOnGetOrCreateWrapperByIndexTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyLayoutWrapperBuilder and invoke OnExpandChildLayoutWrapper when the childWrappers_
     * is empty.
     * @tc.expected: Create childWrapper and add it to childWrappers_.
     */
    auto lazyForEachNode = CreateLazyForEachNode();
    auto lazyLayoutWrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(
        lazyForEachNode->builder_, AceType::WeakClaim(AceType::RawPtr(lazyForEachNode)));
    lazyLayoutWrapperBuilder->OnExpandChildLayoutWrapper();

    /**
     * @tc.steps: step2. Invoke OnGetOrCreateWrapperByIndex when the index is invalid or not.
     * @tc.expected: Return nullptr when index is invalid and return the corresponding wrapper when it is valid.
     */
    lazyLayoutWrapperBuilder->lazySwiper_ = false;
    lazyLayoutWrapperBuilder->startIndex_ = std::nullopt;
    EXPECT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_2), nullptr);

    /**
     * @tc.steps: step3. Invoke OnGetOrCreateWrapperByIndex when the startIndex_ is null.
     */
    lazyLayoutWrapperBuilder->startIndex_ = INDEX_2;
    EXPECT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_2), nullptr);
    EXPECT_EQ(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(DEFAULT_INDEX), nullptr);

    /**
     * @tc.steps: step4. Invoke OnGetOrCreateWrapperByIndex when the index is not in the range of the starIndex and
     * endIndex.
     */
    lazyLayoutWrapperBuilder->lazySwiper_ = true;
    lazyLayoutWrapperBuilder->startIndex_ = std::nullopt;
    EXPECT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_2), nullptr);
    EXPECT_EQ(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_0), nullptr);

    /**
     * @tc.steps: step5. Invoke OnGetOrCreateWrapperByIndex when the index is not in the range of the starIndex and
     * endIndex.
     */
    lazyLayoutWrapperBuilder->lazySwiper_ = true;
    lazyLayoutWrapperBuilder->startIndex_ = INDEX_2;
    EXPECT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_2), nullptr);
    EXPECT_EQ(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_0), nullptr);
}

/**
 * @tc.name: ForEachSyntaxWrapperBuilderGetKeyByIndexFromPreNodesTest005
 * @tc.desc: Create LazyForEach, and invoke GetKeyByIndexFromPreNodes.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, ForEachSyntaxWrapperBuilderGetKeyByIndexFromPreNodesTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyLayoutWrapperBuilder and invoke SwapDirtyAndUpdateBuildCache when the childWrappers_
     * is empty or not.
     */
    auto lazyForEachNode = CreateLazyForEachNode();
    auto lazyLayoutWrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(
        lazyForEachNode->builder_, AceType::WeakClaim(AceType::RawPtr(lazyForEachNode)));
    EXPECT_EQ(lazyLayoutWrapperBuilder->startIndex_.value_or(DEFAULT_INDEX), NEW_START_ID);
    EXPECT_EQ(lazyLayoutWrapperBuilder->endIndex_.value_or(DEFAULT_INDEX), NEW_START_ID);

    lazyLayoutWrapperBuilder->OnExpandChildLayoutWrapper();
    lazyLayoutWrapperBuilder->SwapDirtyAndUpdateBuildCache();
    EXPECT_EQ(lazyLayoutWrapperBuilder->endIndex_.value_or(DEFAULT_INDEX), NEW_END_ID);

    /**
     * @tc.steps: step1. Create lazyLayoutWrapperBuilder and invoke SwapDirtyAndUpdateBuildCache when cacheCount is not
     * 0.
     */
    lazyLayoutWrapperBuilder->preStartIndex_ = START_ID;
    lazyLayoutWrapperBuilder->preEndIndex_ = INDEX_5;
    auto key = lazyLayoutWrapperBuilder->GetKeyByIndexFromPreNodes(NEW_END_ID);
    EXPECT_EQ(key, std::nullopt);

    key = lazyLayoutWrapperBuilder->GetKeyByIndexFromPreNodes(INDEX_8);
    EXPECT_EQ(key, std::nullopt);

    lazyLayoutWrapperBuilder->preEndIndex_ = INDEX_8;
    key = lazyLayoutWrapperBuilder->GetKeyByIndexFromPreNodes(START_ID);
    key = lazyLayoutWrapperBuilder->GetKeyByIndexFromPreNodes(NEW_END_ID);
    EXPECT_EQ(key, std::nullopt);
}

/**
 * @tc.name: LazyForEachSyntaxAbnormalCreateTest001
 * @tc.desc: Create LazyForEach in abnormal condition.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachSyntaxAbnormalCreateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as LazyForEach parent.
     */
    const RefPtr<LazyForEachBuilder> mockLazyForEachBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    auto frameNode = LazyForEachNode::GetOrCreateLazyForEachNode(LAZY_FOR_EACH_NODE_ID, mockLazyForEachBuilder);
    auto firstrFrameNode = LazyForEachNode::GetOrCreateLazyForEachNode(LAZY_FOR_EACH_NODE_ID, mockLazyForEachBuilder);
    const RefPtr<LazyForEachBuilder> anothermockLazyForEachBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    auto secondFrameNode =
        LazyForEachNode::GetOrCreateLazyForEachNode(LAZY_FOR_EACH_NODE_ID, anothermockLazyForEachBuilder);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
     */
    EXPECT_TRUE(frameNode == firstrFrameNode);
    EXPECT_TRUE(frameNode == secondFrameNode);
}
} // namespace OHOS::Ace::NG
