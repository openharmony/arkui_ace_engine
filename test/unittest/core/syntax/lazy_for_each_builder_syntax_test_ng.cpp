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

#include <optional>
#include <utility>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#define PRIVATE public
#define PROTECTED public
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
constexpr int32_t INDEX_8 = 8;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_3 = 3;
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_GREATER_THAN_END_INDEX = 20;
constexpr int32_t INDEX_EQUAL_WITH_START_INDEX = 1;
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
    MockPipelineContext::SetUp();
}

void LazyForEachSyntaxTestNg::TearDown()
{
    MockPipelineContext::TearDown();
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
 * @tc.name: LazyForEachOnDataBulkChangedTest001
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachOnDataBulkChangedTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }

    lazyForEachNode->OnDataAdded(INDEX_GREATER_THAN_END_INDEX);
    lazyForEachNode->OnDataBulkChanged(INDEX_EQUAL_WITH_START_INDEX, INDEX_GREATER_THAN_END_INDEX);

    lazyForEachNode->builder_ = nullptr;
    lazyForEachNode->OnDataAdded(INDEX_EQUAL_WITH_START_INDEX);
    lazyForEachNode->OnDataBulkChanged(INDEX_EQUAL_WITH_START_INDEX, INDEX_GREATER_THAN_END_INDEX);
}

/**
 * @tc.name: LazyForEachOnDataMoveToNewPlaceTest001
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachOnDataMoveToNewPlaceTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }

    lazyForEachNode->OnDataAdded(INDEX_GREATER_THAN_END_INDEX);
    lazyForEachNode->OnDataMoveToNewPlace(INDEX_EQUAL_WITH_START_INDEX, INDEX_GREATER_THAN_END_INDEX);

    lazyForEachNode->builder_ = nullptr;
    lazyForEachNode->OnDataAdded(INDEX_EQUAL_WITH_START_INDEX);
    lazyForEachNode->OnDataMoveToNewPlace(INDEX_EQUAL_WITH_START_INDEX, INDEX_GREATER_THAN_END_INDEX);
}

/**
 * @tc.name: LazyForEachOnDatasetChangeTest001
 * @tc.desc: Create LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachOnDatasetChangeTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);
    
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        lazyForEachBuilder->GetChildByIndex(iter.value_or(0), true);
    }
    lazyForEachBuilder->OnDataAdded(INDEX_0);
    std::list<V2::Operation> DataOperations;
    V2::Operation operation1 = {.type = "text"};
    DataOperations.push_back(operation1);
    UpdateItems(lazyForEachNode, mockLazyForEachActuator);
    lazyForEachNode->OnDataAdded(INDEX_GREATER_THAN_END_INDEX);
    lazyForEachNode->OnDatasetChange(DataOperations);
    lazyForEachNode->builder_ = nullptr;
    lazyForEachNode->OnDatasetChange(DataOperations);
}

/**
 * @tc.name: LazyForEachGetFrameChildByIndexTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :GetFrameChildByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachGetFrameChildByIndexTest001, TestSize.Level1)
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
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);
    EXPECT_TRUE(lazyForEachNode != nullptr && lazyForEachNode->GetTag() == V2::JS_LAZY_FOR_EACH_ETS_TAG);

    UpdateItems(lazyForEachNode, mockLazyForEachActuator);

    lazyForEachNode->GetFrameChildByIndex(0, true, true);
    EXPECT_TRUE(lazyForEachNode->ids_.empty());
}

/**
 * @tc.name: LazyForEachOnDataBulkChangedTest002
 * @tc.desc: Create LazyForEach, update its Items and invoke :GetFrameChildByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachOnDataBulkChangedTest002, TestSize.Level1)
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

    lazyForEachBuilder->OnDataBulkChanged(0, 5);

    lazyForEachBuilder->OnDataBulkChanged(10, 20);
}

/**
 * @tc.name: LazyForEachCollectIndexChangedCountTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :GetFrameChildByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachCollectIndexChangedCountTest001, TestSize.Level1)
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

    std::map<int32_t, OperationInfo> operationList;
    OperationInfo itemInfo;
    operationList[1] = itemInfo;
    operationList[2] = itemInfo;

    std::map<int32_t, int32_t> indexChangedMap;
    indexChangedMap[1] = 1;
    indexChangedMap[2] = 2;
    indexChangedMap[3] = 3;
    indexChangedMap[4] = 4;
    indexChangedMap[5] = 5;
    indexChangedMap[6] = 6;

    lazyForEachBuilder->operationList_ = operationList;
    lazyForEachBuilder->CollectIndexChangedCount(indexChangedMap);
}

/**
 * @tc.name: LazyForEachOperateDeleteTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :GetFrameChildByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachOperateDeleteTest001, TestSize.Level1)
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

    V2::Operation operation1 = {.type = "delete", .index = INDEX_0, .count = INDEX_8};
    int32_t num;
    num = 1;
    lazyForEachBuilder->OperateDelete(operation1, num);

    V2::Operation operation2 = {.type = "delete", .index = INDEX_8, .count = INDEX_8};
    lazyForEachBuilder->OperateDelete(operation2, num);
}

/**
 * @tc.name: LazyForEachOperateChangeTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :GetFrameChildByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachOperateChangeTest001, TestSize.Level1)
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
    V2::Operation operation1 = {.type = "change", .index = INDEX_0, .count = INDEX_8};
    DataOperations.push_back(operation1);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
}

/**
 * @tc.name: LazyForEachOperateMoveTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :GetFrameChildByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachOperateMoveTest001, TestSize.Level1)
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
    V2::Operation operation1 = {.type = "move", .index = INDEX_0, .count = INDEX_8, .coupleIndex = std::pair(8, 8)};
    DataOperations.push_back(operation1);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
    
    std::list<V2::Operation> DataOperations1;
    V2::Operation operation2 = {.type = "move", .index = INDEX_0, .count = INDEX_8, .coupleIndex = std::pair(0, 8)};
    DataOperations1.push_back(operation2);
    lazyForEachBuilder->OnDatasetChange(DataOperations1);

    std::list<V2::Operation> DataOperations2;
    V2::Operation operation3 = {.type = "move", .index = INDEX_3, .key = "", .coupleIndex = std::pair(0, 1)};
    DataOperations2.push_back(operation3);
    lazyForEachBuilder->OnDatasetChange(DataOperations2);
}

/**
 * @tc.name: LazyForEachOperateExchangeTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :GetFrameChildByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachOperateExchangeTest001, TestSize.Level1)
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
    V2::Operation operation1 = {.type = "exchange", .index = INDEX_0, .count = INDEX_8,
     .coupleIndex = std::pair(1, 3)};
    DataOperations.push_back(operation1);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
    
    std::list<V2::Operation> DataOperations1;
    V2::Operation operation2 = {.type = "exchange", .index = INDEX_0, .count = INDEX_8,
     .coupleIndex = std::pair(20, 3)};
    DataOperations1.push_back(operation2);
    lazyForEachBuilder->OnDatasetChange(DataOperations1);

    std::list<V2::Operation> DataOperations2;
    V2::Operation operation3 = {.type = "exchange", .index = INDEX_3, .coupleKey = std::pair("", ""),
     .coupleIndex = std::pair(0, 20)};
    DataOperations2.push_back(operation3);
    lazyForEachBuilder->OnDatasetChange(DataOperations2);

    std::list<V2::Operation> DataOperations3;
    V2::Operation operation4 = {.type = "exchange", .index = INDEX_3, .coupleKey = std::pair("1", "1"),
     .coupleIndex = std::pair(0, 20)};
    DataOperations3.push_back(operation4);
    lazyForEachBuilder->OnDatasetChange(DataOperations3);
}

/**
 * @tc.name: LazyForEachOperateReloadTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :GetFrameChildByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachOperateReloadTest001, TestSize.Level1)
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
    V2::Operation operation1 = {.type = "reload", .index = INDEX_0, .count = INDEX_8, .coupleIndex = std::pair(1, 3)};
    DataOperations.push_back(operation1);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
}

/**
 * @tc.name: LazyForEachThrowRepeatOperationErrorTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :GetFrameChildByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachThrowRepeatOperationErrorTest001, TestSize.Level1)
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

    lazyForEachBuilder->ThrowRepeatOperationError(INDEX_0);
}

/**
 * @tc.name: LazyForEachRecycleChildByIndexTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :GetFrameChildByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachRecycleChildByIndexTest001, TestSize.Level1)
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
    V2::Operation operation1 = {.type = "add", .index = INDEX_0, .count = INDEX_8, .coupleIndex = std::pair(1, 3)};
    DataOperations.push_back(operation1);
    lazyForEachBuilder->OnDatasetChange(DataOperations);
    lazyForEachBuilder->OnDataAdded(INDEX_GREATER_THAN_END_INDEX);

    lazyForEachBuilder->RecycleChildByIndex(INDEX_1);

    lazyForEachBuilder->RecycleChildByIndex(8);
}

/**
 * @tc.name: LazyForEachRecordOutOfBoundaryNodesTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :GetFrameChildByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachRecordOutOfBoundaryNodesTest001, TestSize.Level1)
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

    lazyForEachBuilder->RecordOutOfBoundaryNodes(INDEX_0);
}

/**
 * @tc.name: LazyForEachRecycleItemsOutOfBoundaryTest001
 * @tc.desc: Create LazyForEach, update its Items and invoke :GetFrameChildByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachRecycleItemsOutOfBoundaryTest001, TestSize.Level1)
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

    lazyForEachBuilder->outOfBoundaryNodes_ = LAZY_FOR_EACH_ITEMS;
    lazyForEachBuilder->RecycleItemsOutOfBoundary();
}
} // namespace OHOS::Ace::NG
