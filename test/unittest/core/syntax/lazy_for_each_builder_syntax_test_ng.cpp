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
    lazyForEachNode->OnDataMoveToNewPlace(INDEX_EQUAL_WITH_START_INDEX, INDEX_EQUAL_WITH_START_INDEX);
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

/**
 * @tc.name: LazyForEachBuilder01
 * @tc.desc: LazyForEachBuilder::GetChildByIndex
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachBuilder01, TestSize.Level1)
{
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    /**
     * @tc.steps: step1. iter->second.second == nullptr;
     */
    std::string str0 = "0";
    lazyForEachBuilder->cachedItems_[0] = LazyForEachChild(str0, nullptr);
    auto step1 = lazyForEachBuilder->GetChildByIndex(0, true);
    EXPECT_EQ(step1.first.size(), 1);

    /**
     * @tc.steps: step2. keyIter != expiringItem_.end(), keyIter->second.second == nullptr;
     */
    std::string str1 = "1";
    lazyForEachBuilder->cachedItems_[1] = LazyForEachChild(str1, nullptr);
    lazyForEachBuilder->expiringItem_[str1] = LazyForEachCacheChild(1, nullptr);
    auto step2 = lazyForEachBuilder->GetChildByIndex(1, true);
    EXPECT_EQ(step2.first.size(), 1);

    /**
     * @tc.steps: step3. keyIter != expiringItem_.end(), keyIter->second.second != nullptr;
     */
    auto iter02 = lazyForEachBuilder->cachedItems_.find(0);
    std::string str2 = "2";
    lazyForEachBuilder->cachedItems_[2] = LazyForEachChild(str2, nullptr);
    lazyForEachBuilder->expiringItem_[str2] = LazyForEachCacheChild(2, iter02->second.second);
    auto step3 = lazyForEachBuilder->GetChildByIndex(2, true);
    EXPECT_EQ(step3.first.size(), 1);

    /**
     * @tc.steps: step4. isCache == true;
     */
    auto iter03 = lazyForEachBuilder->cachedItems_.find(0);
    std::string str3 = "3";
    lazyForEachBuilder->cachedItems_[3] = LazyForEachChild(str3, nullptr);
    lazyForEachBuilder->expiringItem_[str3] = LazyForEachCacheChild(3, iter03->second.second);
    auto step4 = lazyForEachBuilder->GetChildByIndex(3, true, true);
    EXPECT_EQ(step4.first.size(), 1);

    /**
     * @tc.steps: step5. needBuild == false;
     */
    std::string str4 = "4";
    lazyForEachBuilder->cachedItems_[4] = LazyForEachChild(str4, nullptr);
    auto step5 = lazyForEachBuilder->GetChildByIndex(4, false);
    EXPECT_EQ(step5.first.size(), 0);

    /**
     * @tc.steps: step6. useNewInterface_ == true, isCache == true;
     */
    std::string str5 = "5";
    lazyForEachBuilder->cachedItems_[5] = LazyForEachChild(str5, nullptr);
    lazyForEachBuilder->useNewInterface_ = true;
    auto step6 = lazyForEachBuilder->GetChildByIndex(5, true, true);
    EXPECT_EQ(step6.first.size(), 1);
}

/**
 * @tc.name: LazyForEachBuilder02
 * @tc.desc: LazyForEachBuilder::ConvertFormToIndex
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachBuilder02, TestSize.Level1)
{
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    /**
     * @tc.steps: step1. !moveFromTo_;
     */
    auto step1 = lazyForEachBuilder->ConvertFormToIndex(0);
    EXPECT_EQ(step1, 0);

    /**
     * @tc.steps: step2. (1, 1);
     */
    lazyForEachBuilder->moveFromTo_.emplace(1, 1);
    auto step2 = lazyForEachBuilder->ConvertFormToIndex(0);
    EXPECT_EQ(step2, 0);

    /**
     * @tc.steps: step3. moveFromTo_.value().second == index;
     */
    lazyForEachBuilder->moveFromTo_.value().second = 0;
    auto step3 = lazyForEachBuilder->ConvertFormToIndex(0);
    EXPECT_EQ(step3, 1);

    /**
     * @tc.steps: step4. (0, 0);
     */
    lazyForEachBuilder->moveFromTo_.value().first = 0;
    lazyForEachBuilder->moveFromTo_.value().second = 0;
    auto step4 = lazyForEachBuilder->ConvertFormToIndex(1);
    EXPECT_EQ(step4, 1);

    /**
     * @tc.steps: step5. (0, 2);
     */
    lazyForEachBuilder->moveFromTo_.value().first = 0;
    lazyForEachBuilder->moveFromTo_.value().second = 2;
    auto step5 = lazyForEachBuilder->ConvertFormToIndex(1);
    EXPECT_EQ(step5, 2);

    /**
     * @tc.steps: step6. (2, 0);
     */
    lazyForEachBuilder->moveFromTo_.value().first = 2;
    lazyForEachBuilder->moveFromTo_.value().second = 0;
    auto step6 = lazyForEachBuilder->ConvertFormToIndex(1);
    EXPECT_EQ(step6, 0);
}

/**
 * @tc.name: LazyForEachBuilder03
 * @tc.desc: LazyForEachBuilder::PreBuild
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachBuilder03, TestSize.Level1)
{
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);
    LayoutConstraintF layoutConstraint;

    /**
     * @tc.steps: step1. all == false;
     */
    auto step1 = lazyForEachBuilder->PreBuild(10, layoutConstraint, true);
    EXPECT_TRUE(step1);

    /**
     * @tc.steps: step2. itemConstraint, startIndex_ != -1;
     */
    layoutConstraint.parentIdealSize = OptionalSizeF(768, 1024);
    layoutConstraint.selfIdealSize = OptionalSizeF(480, 960);
    lazyForEachBuilder->startIndex_ = 3;
    auto step2 = lazyForEachBuilder->PreBuild(10, layoutConstraint, true);
    EXPECT_TRUE(step2);

    /**
     * @tc.steps: step3. startIndex_ != -1 && endIndex_ != -1;
     */
    lazyForEachBuilder->endIndex_ = 1;
    auto step3 = lazyForEachBuilder->PreBuild(10, layoutConstraint, true);
    EXPECT_TRUE(step3);

    /**
     * @tc.steps: step4. !canRunLongPredictTask;
     */
    auto step4 = lazyForEachBuilder->PreBuild(10, layoutConstraint, false);
    EXPECT_FALSE(step4);
}

/**
 * @tc.name: LazyForEachBuilder04
 * @tc.desc: LazyForEachBuilder::OnDataBulkChanged
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachBuilder04, TestSize.Level1)
{
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    /**
     * @tc.steps: step1. cachedItems_.empty();
     */
    auto step1 = lazyForEachBuilder->OnDataBulkChanged(0, 0);
    EXPECT_EQ(step1.size(), 0);

    /**
     * @tc.steps: step1. node.first;
     */
    std::string str0 = "0";
    lazyForEachBuilder->cachedItems_[0] = LazyForEachChild(str0, nullptr);
    lazyForEachBuilder->expiringItem_[str0] = LazyForEachCacheChild(2, nullptr);
    std::string str1 = "1";
    lazyForEachBuilder->cachedItems_[1] = LazyForEachChild(str1, nullptr);
    lazyForEachBuilder->expiringItem_[str1] = LazyForEachCacheChild(7, nullptr);
    std::string str2 = "2";
    lazyForEachBuilder->cachedItems_[2] = LazyForEachChild(str2, nullptr);
    lazyForEachBuilder->expiringItem_[str2] = LazyForEachCacheChild(0, nullptr);
    lazyForEachBuilder->OnDataBulkChanged(1, 5);
    EXPECT_EQ(lazyForEachBuilder->expiringItem_[str0].first, -1);
    EXPECT_EQ(lazyForEachBuilder->expiringItem_[str1].first, 7);
    EXPECT_EQ(lazyForEachBuilder->expiringItem_[str2].first, 0);
}

/**
 * @tc.name: LazyForEachBuilder05
 * @tc.desc: LazyForEachBuilder::RecycleChildByIndex
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachBuilder05, TestSize.Level1)
{
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    /**
     * @tc.steps: step1. !iter->second.second;
     */
    std::string str0 = "0";
    lazyForEachBuilder->cachedItems_[0] = LazyForEachChild(str0, nullptr);
    lazyForEachBuilder->RecycleChildByIndex(0);
    EXPECT_EQ(lazyForEachBuilder->cachedItems_.size(), 1);

    /**
     * @tc.steps: step2. !dummyNode;
     */
    std::string str1 = "1";
    lazyForEachBuilder->cachedItems_[1] = LazyForEachChild(str1, nullptr);
    lazyForEachBuilder->GetChildByIndex(1, true);
    lazyForEachBuilder->RecycleChildByIndex(1);
    EXPECT_EQ(lazyForEachBuilder->cachedItems_.size(), 2);

    /**
     * @tc.steps: step3. dummyNode;
     */
    std::string str2 = "2";
    lazyForEachBuilder->cachedItems_[2] = LazyForEachChild(str2, nullptr);
    lazyForEachBuilder->GetChildByIndex(2, true);
    auto iter = lazyForEachBuilder->cachedItems_.find(2);
    iter->second.second->SetNeedCallChildrenUpdate(true);
    iter->second.second->debugLine_ = str2;
    lazyForEachBuilder->RecycleChildByIndex(2);
    EXPECT_EQ(lazyForEachBuilder->cachedItems_.size(), 3);
}

/**
 * @tc.name: LazyForEachBuilder06
 * @tc.desc: LazyForEachBuilder::OnDataBulkDeleted
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachBuilder06, TestSize.Level1)
{
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    /**
     * @tc.steps: step1. Override the branch of the judgment expiringItem_;
     */
    std::string str1 = "1";
    std::string str2 = "3";
    lazyForEachBuilder->cachedItems_[1] = LazyForEachChild(str1, nullptr);
    lazyForEachBuilder->expiringItem_[str1] = LazyForEachCacheChild(1, nullptr);
    lazyForEachBuilder->expiringItem_[str2] = LazyForEachCacheChild(3, nullptr);
    lazyForEachBuilder->OnDataBulkDeleted(2, 5);
    EXPECT_EQ(lazyForEachBuilder->nodeList_.size(), 0);

    /**
     * @tc.steps: step1. Override the branch of the judgment cachedItems_;
     */
    lazyForEachBuilder->cachedItems_[3] = LazyForEachChild(str2, nullptr);
    lazyForEachBuilder->OnDataBulkDeleted(2, 5);
    EXPECT_NE(lazyForEachBuilder->nodeList_.size(), 0);
}

/**
 * @tc.name: LazyForEachBuilder07
 * @tc.desc: LazyForEachBuilder::OnDataBulkDeleted
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachSyntaxTestNg, LazyForEachBuilder07, TestSize.Level1)
{
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);

    /**
     * @tc.steps: step1. operation.index >= totalCountOfOriginalDataset_;
     */
    V2::Operation operation;
    operation.index = 0;
    int32_t initialIndex = 0;
    std::map<int32_t, LazyForEachChild> cachedTemp;
    std::map<int32_t, LazyForEachChild> expiringTemp;
    lazyForEachBuilder->OperateChange(operation, initialIndex, cachedTemp, expiringTemp);
    EXPECT_EQ(lazyForEachBuilder->operationList_.size(), 0);

    /**
     * @tc.steps: step2. !indexExist == operationList_.end();
     */
    lazyForEachBuilder->totalCountOfOriginalDataset_ = 1;
    OperationInfo operationinfo;
    lazyForEachBuilder->operationList_[1] = operationinfo;
    lazyForEachBuilder->OperateChange(operation, initialIndex, cachedTemp, expiringTemp);
    EXPECT_EQ(lazyForEachBuilder->operationList_.size(), 1);

    /**
     * @tc.steps: step3. !operation.key.empty();
     */
    std::string str0 = "0";
    expiringTemp[0] = LazyForEachChild(str0, nullptr);
    cachedTemp[0] = LazyForEachChild(str0, nullptr);
    operation.key = "0";
    lazyForEachBuilder->OperateChange(operation, initialIndex, cachedTemp, expiringTemp);
    EXPECT_EQ(lazyForEachBuilder->operationList_.size(), 2);

    /**
     * @tc.steps: step4. !indexExist == operationList_.end();
     */
    lazyForEachBuilder->operationList_[0] = operationinfo;
    lazyForEachBuilder->OperateChange(operation, initialIndex, cachedTemp, expiringTemp);
    EXPECT_EQ(lazyForEachBuilder->operationList_.size(), 2);
}
} // namespace OHOS::Ace::NG
