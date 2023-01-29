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

constexpr int32_t NEW_START_ID = 0;
constexpr int32_t NEW_END_ID = 6;
constexpr int32_t INVALID_START_ID_LESS_THAN_0 = -1;
constexpr int32_t INVALID_START_ID_GREATER_THAN_TOTAL = 7;
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
} // namespace

class LazyLayoutWrapperSyntaxTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    static void UpdateItems(
        const RefPtr<LazyForEachNode>& lazyForEachNode, const RefPtr<LazyForEachActuator>& mockLazyForEachActuator)
    {
        /**
         * @tc.steps: step1. Add child found in generatedItem_.
         */
        auto ids = LAZY_FOR_EACH_NODE_IDS;
        auto builder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);
        for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
            builder->CreateChildByIndex(iter.value_or(0));
        }

        /**
         * @tc.steps: step2. Update item found in generatedItem_.
         */
        auto cacheItems = LAZY_FOR_EACH_CACHED_ITEMS;
        lazyForEachNode->UpdateLazyForEachItems(NEW_START_ID, NEW_END_ID, std::move(ids), std::move(cacheItems));
    }

    static RefPtr<LazyForEachNode> CreateLazyForEachNode()
    {
        /**
         * @tc.steps: step1. Create Text and push it to view stack processor.
         * @tc.expected: Make Text as LazyForEach parent.
         */
        auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
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

void LazyLayoutWrapperSyntaxTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "LazyLayoutWrapperSyntaxTestNg SetUpTestCase";
}

void LazyLayoutWrapperSyntaxTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "LazyLayoutWrapperSyntaxTestNg TearDownTestCase";
}

void LazyLayoutWrapperSyntaxTestNg::SetUp()
{
    MockPipelineBase::SetUp();
}

void LazyLayoutWrapperSyntaxTestNg::TearDown()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: ForEachSyntaxWrapperBuilderOnExpandChildLayoutWrapperTest001
 * @tc.desc: Create LazyForEach, and invoke OnExpandChildLayoutWrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LazyLayoutWrapperSyntaxTestNg, ForEachSyntaxWrapperBuilderOnExpandChildLayoutWrapperTest001, TestSize.Level1)
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
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty()));
    lazyLayoutWrapperBuilder->OnExpandChildLayoutWrapper();
    EXPECT_TRUE(lazyLayoutWrapperBuilder->childWrappers_.empty());
}

/**
 * @tc.name: ForEachSyntaxWrapperBuilderOnGetOrCreateWrapperByIndexTest002
 * @tc.desc: Create LazyForEach, and invoke OnGetOrCreateWrapperByIndex.
 * @tc.type: FUNC
 */
HWTEST_F(LazyLayoutWrapperSyntaxTestNg, ForEachSyntaxWrapperBuilderOnExpandChildLayoutWrapperTest002, TestSize.Level1)
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
    EXPECT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_2), nullptr);

    /**
     * @tc.steps: step3. Invoke OnGetOrCreateWrapperByIndex when the startIndex_ is null.
     */
    lazyLayoutWrapperBuilder->startIndex_ = std::nullopt;
    EXPECT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_2), nullptr);
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
    EXPECT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_4), nullptr);
    lazyLayoutWrapperBuilder->UpdateIndexRange(INDEX_2, INDEX_8, LAZY_FOR_EACH_NODE_IDS);
    lazyLayoutWrapperBuilder->startIndex_ = std::nullopt;
    EXPECT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_1), nullptr);
    EXPECT_NE(lazyLayoutWrapperBuilder->OnGetOrCreateWrapperByIndex(INDEX_0), nullptr);
}

/**
 * @tc.name: ForEachSyntaxWrapperBuilderSwapDirtyAndUpdateBuildCacheTest003
 * @tc.desc: Create LazyForEach, and invoke SwapDirtyAndUpdateBuildCache.
 * @tc.type: FUNC
 */
HWTEST_F(
    LazyLayoutWrapperSyntaxTestNg, ForEachSyntaxWrapperBuilderSwapDirtyAndUpdateBuildCacheTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create lazyLayoutWrapperBuilder and invoke SwapDirtyAndUpdateBuildCache when the childWrappers_
     * is empty or not.
     */
    auto lazyForEachNode = CreateLazyForEachNode();
    auto lazyLayoutWrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(
        lazyForEachNode->builder_, AceType::WeakClaim(AceType::RawPtr(lazyForEachNode)));
    lazyLayoutWrapperBuilder->SwapDirtyAndUpdateBuildCache();
    EXPECT_EQ(lazyLayoutWrapperBuilder->startIndex_.value_or(DEFAULT_INDEX), NEW_START_ID);
    EXPECT_EQ(lazyLayoutWrapperBuilder->endIndex_.value_or(DEFAULT_INDEX), NEW_START_ID);

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
    EXPECT_EQ(lazyLayoutWrapperBuilder1->startIndex_.value_or(DEFAULT_INDEX), START_ID);

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
    EXPECT_EQ(lazyLayoutWrapperBuilder2->startIndex_.value_or(DEFAULT_INDEX), INDEX_3);
}
} // namespace OHOS::Ace::NG
