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
#include "core/pipeline/base/element_register.h"

#define private public
#define protected public
#include "mock_lazy_for_each_actuator.h"
#include "mock_lazy_for_each_builder.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::list<std::optional<std::string>> LAZY_FOR_EACH_NODE_IDS = { "0", "1", "2", "3", "4", "5", "6" };
const std::list<std::optional<std::string>> DEFAULT_LAZY_FOR_EACH_NODE_IDS = {};
const std::list<std::optional<int32_t>> LAZY_FOR_EACH_NODE_IDS_INT = { 0, 1, 2, 3, 4, 5, 6 };
const std::unordered_map<int32_t, std::optional<std::string>> LAZY_FOR_EACH_CACHED_ITEMS = { { 0, "0" }, { 1, "1" } };
const std::list<int32_t> LAZY_FOR_EACH_ITEMS = { 0, 1, 2, 3, 4, 5 };
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_7 = 7;
constexpr int32_t INDEX_EQUAL_WITH_START_INDEX_DELETED = -1;
constexpr size_t BUILDER_INDEX_ONDATADELETED_END = 4294967295;
} // namespace

class LazyForEachSyntaxTestNg2 : public testing::Test {
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

void LazyForEachSyntaxTestNg2::SetUp()
{
    MockPipelineContext::SetUp();
}

void LazyForEachSyntaxTestNg2::TearDown()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> LazyForEachSyntaxTestNg2::CreateNode(const std::string& tag)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    return frameNode;
}

/**
 * @tc.name: ForEachSyntaxDoSetActiveChildRangeTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :DoSetActiveChildRange function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, ForEachSyntaxDoSetActiveChildRangeTest001, TestSize.Level1)
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
     * @tc.steps: step3. Invoke DoSetActiveChildRange.
     * @tc.expected: LazyForEachNode ids_ will be cleared.
     */
    lazyForEachNode->DoSetActiveChildRange(0, 0, 0, 0);
    EXPECT_TRUE(lazyForEachNode->ids_.empty());

    /**
     * @tc.steps: step3. Invoke DoSetActiveChildRange.
     * @tc.expected: LazyForEachNode ids_ will be cleared.
     */
    lazyForEachNode->builder_ = nullptr;
    lazyForEachNode->DoSetActiveChildRange(0, 0, 0, 0);
    EXPECT_TRUE(lazyForEachNode->ids_.empty());
}

/**
 * @tc.name: ForEachSyntaxOnConfigurationUpdateTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :OnConfigurationUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, ForEachSyntaxOnConfigurationUpdateTest001, TestSize.Level1)
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
    ConfigurationChange configurationChange;

    auto lazyForEachBuilder = lazyForEachNode->builder_;

    UpdateItems(lazyForEachNode, mockLazyForEachActuator);

    /**
     * @tc.steps: step3. Invoke configurationChange.IsNeedUpdate() = true and builder_ is not null
     */
    lazyForEachBuilder->expiringItem_["0"] = LazyForEachCacheChild(0, nullptr);
    configurationChange.colorModeUpdate = true;
    lazyForEachNode->OnConfigurationUpdate(configurationChange);
    EXPECT_TRUE(lazyForEachNode->ids_.empty());


    /**
     * @tc.steps: step4. configurationChange.IsNeedUpdate() = false and builder_ is not null
     */
    configurationChange.colorModeUpdate = false;
    lazyForEachNode->OnConfigurationUpdate(configurationChange);
    EXPECT_TRUE(lazyForEachNode->ids_.empty());

    lazyForEachNode->builder_=nullptr;

    /**
     * @tc.steps: step5. configurationChange.IsNeedUpdate() = true and builder_ is null
     */
    configurationChange.colorModeUpdate = true;
    lazyForEachNode->OnConfigurationUpdate(configurationChange);
    EXPECT_TRUE(lazyForEachNode->ids_.empty());

    /**
     * @tc.steps: step6. configurationChange.IsNeedUpdate() = true and builder_ is null
     */
    configurationChange.colorModeUpdate = false;
    lazyForEachNode->OnConfigurationUpdate(configurationChange);
    EXPECT_TRUE(lazyForEachNode->ids_.empty());
}

/**
 * @tc.name: LazyForEachSyntaxOnDataReloadedTest001
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataReloadedTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
    lazyForEachBuilder->OnDataReloaded();
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 0);
}

/**
 * @tc.name: LazyForEachSyntaxOnDataReloadedTest002
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataReloadedTest002, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    std::list<V2::Operation> DataOperations;
    V2::Operation operation1 = {.type = "reload"};
    DataOperations.push_back(operation1);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 0);
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
}

/**
 * @tc.name: LazyForEachSyntaxOnDataAddedTest001
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataAddedTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    lazyForEachBuilder->useNewInterface_ = true;
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true, true);
    }
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
    lazyForEachBuilder->OnDataAdded(INDEX_0);
    EXPECT_NE(lazyForEachBuilder->GetChildByIndex(7, false, false).second, nullptr);
}

/**
 * @tc.name: LazyForEachSyntaxOnDataAddedTest002
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataAddedTest002, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    std::list<V2::Operation> DataOperations;
    V2::Operation operation1 = {.type = "add", .index = INDEX_0, .count = 1};
    DataOperations.push_back(operation1);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 8);
    DataOperations.clear();
    V2::Operation operation2 = {.type = "add", .index = INDEX_0, .count = 2};
    DataOperations.push_back(operation2);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 10);
}

/**
 * @tc.name: LazyForEachSyntaxOnDataBulkAddedTest001
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataBulkAddedTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
    lazyForEachBuilder->OnDataBulkAdded(INDEX_0, 2);
    EXPECT_NE(lazyForEachBuilder->GetChildByIndex(8, false, false).second, nullptr);
}

/**
 * @tc.name: LazyForEachSyntaxOnDataDeletedTest001
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataDeletedTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    lazyForEachBuilder->OnDataDeleted(INDEX_0);
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
    lazyForEachBuilder->OnDataDeleted(INDEX_0);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 6);
    lazyForEachBuilder->OnDataDeleted(BUILDER_INDEX_ONDATADELETED_END);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 6);
}

/**
 * @tc.name: LazyForEachSyntaxOnDataDeletedTest002
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataDeletedTest002, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    // init historicalTotalCount_
    lazyForEachBuilder->UpdateHistoricalTotalCount(lazyForEachBuilder->GetTotalCount());
    std::list<V2::Operation> DataOperations;
    V2::Operation operation1 = {.type = "delete", .index = INDEX_0, .count = 1};
    DataOperations.push_back(operation1);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 6);
    DataOperations.clear();
    // update historicalTotalCount_
    lazyForEachBuilder->UpdateHistoricalTotalCount(lazyForEachBuilder->GetTotalCount());
    V2::Operation operation2 = {.type = "delete", .index = INDEX_0, .count = 2};
    DataOperations.push_back(operation2);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 4);
}

/**
 * @tc.name: LazyForEachSyntaxOnDataBulkDeletedTest001
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataBulkDeletedTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);


    lazyForEachBuilder->OnDataBulkDeleted(INDEX_0, INDEX_0);
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
    lazyForEachBuilder->OnDataBulkDeleted(INDEX_0, 2);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 5);
}

/**
 * @tc.name: LazyForEachSyntaxOnDataChangedTest001
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataChangedTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    lazyForEachBuilder->OnDataChanged(INDEX_0);
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
    lazyForEachBuilder->OnDataChanged(INDEX_1);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 6);
    lazyForEachBuilder->OnDataChanged(INDEX_7);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 6);
}

/**
 * @tc.name: LazyForEachSyntaxOnDataChangedTest002
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataChangedTest002, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    std::list<V2::Operation> DataOperations;
    V2::Operation operation1 = {.type = "change", .index = INDEX_0};
    DataOperations.push_back(operation1);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
}

/**
 * @tc.name: LazyForEachSyntaxOnDataMovedTest001
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataMovedTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    lazyForEachBuilder->OnDataMoved(INDEX_0, INDEX_0);
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
    lazyForEachBuilder->OnDataMoved(INDEX_0, INDEX_1);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
    lazyForEachBuilder->OnDataMoved(INDEX_0, INDEX_7);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 6);
    lazyForEachBuilder->OnDataMoved(INDEX_7, INDEX_1);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 5);
    lazyForEachBuilder->OnDataMoved(INDEX_7, INDEX_EQUAL_WITH_START_INDEX_DELETED);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 5);
}

/**
 * @tc.name: LazyForEachSyntaxOnDataMovedTest002
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataMovedTest002, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    std::list<V2::Operation> DataOperations;
    V2::Operation operation1 = {.type = "move", .coupleIndex = std::pair(0, 2)};
    DataOperations.push_back(operation1);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
}

HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxOnDataExchangeTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    std::list<V2::Operation> DataOperations;
    V2::Operation operation1 = {.type = "exchange", .coupleIndex = std::pair(1, 3)};
    DataOperations.push_back(operation1);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
}

/**
 * @tc.name: LazyForEachSyntaxRecycleChildByIndexTest001
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachSyntaxRecycleChildByIndexTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    lazyForEachBuilder->RecycleChildByIndex(INDEX_0);
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    EXPECT_EQ(lazyForEachBuilder->OnGetTotalCount(), 7);
    lazyForEachBuilder->RecycleChildByIndex(INDEX_1);
}

/**
 * @tc.name: ForEachSyntaxInitDragManagerTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke InitDragManager function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, ForEachSyntaxInitDragManagerTest001, TestSize.Level1)
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
     * @tc.steps: step3. Invoke NotifyCountChange.
     * @tc.expected: LazyForEachNode ids_ will be cleared.
     */
    auto frameChild = AceType::DynamicCast<FrameNode>(lazyForEachNode->GetFrameChildByIndex(0, true));
    lazyForEachNode->InitDragManager(frameChild);
    EXPECT_TRUE(lazyForEachNode->ids_.empty());
}

/**
 * @tc.name: ForEachSyntaxGetFrameNodeIndexTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke GetFrameNodeIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, ForEachSyntaxGetFrameNodeIndexTest001, TestSize.Level1)
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
     * @tc.steps: step3. Invoke NotifyCountChange.
     * @tc.expected: LazyForEachNode ids_ will be cleared.
     */
    auto frameChild = AceType::DynamicCast<FrameNode>(lazyForEachNode->GetFrameChildByIndex(0, true));
    lazyForEachNode->GetFrameNodeIndex(frameChild, true);
    lazyForEachNode->GetFrameNodeIndex(frameChild, false);
    EXPECT_TRUE(lazyForEachNode->ids_.empty());
}

/**
 * @tc.name: ForEachSyntaxNotifyCountChangeTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke NotifyCountChange function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, ForEachSyntaxNotifyCountChangeTest001, TestSize.Level1)
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
     * @tc.steps: step3. Invoke NotifyCountChange.
     * @tc.expected: LazyForEachNode ids_ will be cleared.
     */
    lazyForEachNode->NotifyChangeWithCount(0, 0, UINode::NotificationType::END_CHANGE_POSITION);
    EXPECT_TRUE(lazyForEachNode->ids_.empty());
}

/**
 * @tc.name: LazyForEachNode OnDelete
 * @tc.desc: LazyForEachNode OnDelete
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg2, LazyForEachNode_OnDelete, TestSize.Level1)
{
    auto lazyForEachNode = CreateLazyForEachNode();
    lazyForEachNode->OnDelete();
    EXPECT_FALSE(lazyForEachNode->isRegisterListener_);
    lazyForEachNode->builder_ = nullptr;
    lazyForEachNode->OnDelete();
    EXPECT_FALSE(lazyForEachNode->isRegisterListener_);
}
}