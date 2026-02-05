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
#include "core/components_ng/base/inspector.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_2 = 2;
constexpr int32_t INDEX_5 = 5;
constexpr int32_t INDEX_10 = 10;
constexpr int32_t INDEX_NEGATIVE = -1;
constexpr int32_t INDEX_LARGE = 100;
constexpr int32_t COUNT_2 = 2;
constexpr int32_t COUNT_5 = 5;
constexpr int32_t COUNT_10 = 10;
} // namespace

class LazyForEachBuilderAdvancedTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;

    RefPtr<FrameNode> CreateNode(const std::string& tag);

    static RefPtr<LazyForEachBuilder> CreateLazyForEachBuilder(bool deleteExpiringItemImmediately = false)
    {
        auto pattern = AceType::MakeRefPtr<Pattern>();
        if (!pattern) {
            return nullptr;
        }
        auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, pattern);
        if (!frameNode) {
            return nullptr;
        }
        pattern->AttachToFrameNode(frameNode);
        ViewStackProcessor::GetInstance()->Push(frameNode);

        LazyForEachModelNG lazyForEach;
        const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
            AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>(deleteExpiringItemImmediately);
        if (!mockLazyForEachActuator) {
            return nullptr;
        }
        lazyForEach.Create(mockLazyForEachActuator);
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
        auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);
        return lazyForEachBuilder;
    }
};

void LazyForEachBuilderAdvancedTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void LazyForEachBuilderAdvancedTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> LazyForEachBuilderAdvancedTestNg::CreateNode(const std::string& tag)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    return frameNode;
}

/**
 * @tc.name: LazyForEachBuilderGetChildByIndexTest001
 * @tc.desc: Test GetChildByIndex with various indices and needBuild flag
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderGetChildByIndexTest001, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->GetChildByIndex(INDEX_0, true);
    (void)lazyForEachBuilder->GetChildByIndex(INDEX_1, false);
    (void)lazyForEachBuilder->GetChildByIndex(INDEX_2, true);
}

/**
 * @tc.name: LazyForEachBuilderGetChildByIndexNegativeTest002
 * @tc.desc: Test GetChildByIndex with negative index
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderGetChildByIndexNegativeTest002, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    auto child = lazyForEachBuilder->GetChildByIndex(INDEX_NEGATIVE, true);
}

/**
 * @tc.name: LazyForEachBuilderGetChildByIndexLargeTest003
 * @tc.desc: Test GetChildByIndex with large index
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderGetChildByIndexLargeTest003, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    auto child = lazyForEachBuilder->GetChildByIndex(INDEX_LARGE, true);
}

/**
 * @tc.name: LazyForEachBuilderGetChildByIndexNoBuildTest004
 * @tc.desc: Test GetChildByIndex with needBuild = false
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderGetChildByIndexNoBuildTest004, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    auto child = lazyForEachBuilder->GetChildByIndex(INDEX_1, false);
}

/**
 * @tc.name: LazyForEachBuilderOnDataAddedTest005
 * @tc.desc: Test OnDataAdded with various indices
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderOnDataAddedTest005, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->OnDataAdded(INDEX_0);
    (void)lazyForEachBuilder->OnDataAdded(INDEX_5);
    (void)lazyForEachBuilder->OnDataAdded(INDEX_10);
}

/**
 * @tc.name: LazyForEachBuilderOnDataDeletedTest006
 * @tc.desc: Test OnDataDeleted with various indices
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderOnDataDeletedTest006, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->OnDataDeleted(INDEX_0);
    (void)lazyForEachBuilder->OnDataDeleted(INDEX_2);
    (void)lazyForEachBuilder->OnDataDeleted(INDEX_5);
}

/**
 * @tc.name: LazyForEachBuilderOnDataChangedTest007
 * @tc.desc: Test OnDataChanged with various indices
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderOnDataChangedTest007, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->OnDataChanged(INDEX_0);
    (void)lazyForEachBuilder->OnDataChanged(INDEX_1);
    (void)lazyForEachBuilder->OnDataChanged(INDEX_2);
}

/**
 * @tc.name: LazyForEachBuilderOnDataBulkAddedTest008
 * @tc.desc: Test OnDataBulkAdded with various ranges
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderOnDataBulkAddedTest008, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->OnDataBulkAdded(INDEX_0, COUNT_2);
    (void)lazyForEachBuilder->OnDataBulkAdded(INDEX_5, COUNT_5);
}

/**
 * @tc.name: LazyForEachBuilderOnDataBulkDeletedTest009
 * @tc.desc: Test OnDataBulkDeleted with various ranges
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderOnDataBulkDeletedTest009, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->OnDataBulkDeleted(INDEX_0, COUNT_2);
    (void)lazyForEachBuilder->OnDataBulkDeleted(INDEX_5, COUNT_5);
}

/**
 * @tc.name: LazyForEachBuilderOnDataReloadedTest010
 * @tc.desc: Test OnDataReloaded clears cached items
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderOnDataReloadedTest010, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->OnDataReloaded();
}

/**
 * @tc.name: LazyForEachBuilderOnDataMovedTest011
 * @tc.desc: Test OnDataMoved with various from/to combinations
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderOnDataMovedTest011, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->OnDataMoved(INDEX_0, INDEX_2);
    (void)lazyForEachBuilder->OnDataMoved(INDEX_1, INDEX_5);
    (void)lazyForEachBuilder->OnDataMoved(INDEX_NEGATIVE, INDEX_1);
}

/**
 * @tc.name: LazyForEachBuilderGetTotalCountTest012
 * @tc.desc: Test GetTotalCount returns correct count
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderGetTotalCountTest012, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    auto count = lazyForEachBuilder->GetTotalCount();
    EXPECT_GE(count, 0);
}

/**
 * @tc.name: LazyForEachBuilderGetTotalCountOfOriginalDatasetTest013
 * @tc.desc: Test GetTotalCountOfOriginalDataset
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderGetTotalCountOfOriginalDatasetTest013, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    auto count = lazyForEachBuilder->GetTotalCountOfOriginalDataset();
    EXPECT_GE(count, 0);
}

/**
 * @tc.name: LazyForEachBuilderUpdateHistoricalTotalCountTest014
 * @tc.desc: Test UpdateHistoricalTotalCount
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderUpdateHistoricalTotalCountTest014, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->UpdateHistoricalTotalCount(COUNT_5);
    auto count = lazyForEachBuilder->GetHistoryTotalCount();
    EXPECT_EQ(count, COUNT_5);
}

/**
 * @tc.name: LazyForEachBuilderSetActiveChildRangeTest015
 * @tc.desc: Test SetActiveChildRange
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderSetActiveChildRangeTest015, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->SetActiveChildRange(INDEX_0, INDEX_5);
    (void)lazyForEachBuilder->SetActiveChildRange(INDEX_5, INDEX_10);
}

/**
 * @tc.name: LazyForEachBuilderGetChildIndexTest016
 * @tc.desc: Test GetChildIndex
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderGetChildIndexTest016, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    auto frameNode = CreateNode(V2::TEXT_ETS_TAG);
    auto index = lazyForEachBuilder->GetChildIndex(frameNode);
    EXPECT_GE(index, -1);
}

/**
 * @tc.name: LazyForEachBuilderSetCacheCountTest017
 * @tc.desc: Test SetCacheCount
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderSetCacheCountTest017, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->SetCacheCount(COUNT_5);
    lazyForEachBuilder->SetCacheCount(COUNT_10);
}

/**
 * @tc.name: LazyForEachBuilderSetIsLoopTest018
 * @tc.desc: Test SetIsLoop
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderSetIsLoopTest018, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->SetIsLoop(true);
    lazyForEachBuilder->SetIsLoop(false);
}

/**
 * @tc.name: LazyForEachBuilderSetShowCachedTest019
 * @tc.desc: Test SetShowCached
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderSetShowCachedTest019, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->SetShowCached(INDEX_0, INDEX_5);
    lazyForEachBuilder->SetShowCached(INDEX_2, INDEX_10);
}

/**
 * @tc.name: LazyForEachBuilderSetJSViewActiveTest020
 * @tc.desc: Test SetJSViewActive
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderSetJSViewActiveTest020, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->SetJSViewActive(true);
    lazyForEachBuilder->SetJSViewActive(false);
}

/**
 * @tc.name: LazyForEachBuilderSetDestroyingTest021
 * @tc.desc: Test SetDestroying
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderSetDestroyingTest021, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->SetDestroying(true, true);
    lazyForEachBuilder->SetDestroying(false, false);
}

/**
 * @tc.name: LazyForEachBuilderNotifyColorModeChangeTest022
 * @tc.desc: Test NotifyColorModeChange
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderNotifyColorModeChangeTest022, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->NotifyColorModeChange(0, true);
    lazyForEachBuilder->NotifyColorModeChange(1, false);
}

/**
 * @tc.name: LazyForEachBuilderEnablePreBuildTest023
 * @tc.desc: Test EnablePreBuild
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderEnablePreBuildTest023, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->EnablePreBuild(true);
    lazyForEachBuilder->EnablePreBuild(false);
}

/**
 * @tc.name: LazyForEachBuilderOnDatasetChangeTest024
 * @tc.desc: Test OnDatasetChange with operation list
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderOnDatasetChangeTest024, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    std::list<V2::Operation> operations;
    V2::Operation op1 = {.type = "add", .index = 0};
    V2::Operation op2 = {.type = "remove", .index = 1};
    operations.push_back(op1);
    operations.push_back(op2);

    (void)lazyForEachBuilder->OnDatasetChange(operations);
}

/**
 * @tc.name: LazyForEachBuilderOnDataBulkChangedTest025
 * @tc.desc: Test OnDataBulkChanged with various ranges
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderOnDataBulkChangedTest025, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->OnDataBulkChanged(INDEX_0, COUNT_5);
    (void)lazyForEachBuilder->OnDataBulkChanged(INDEX_10, COUNT_10);
}

/**
 * @tc.name: LazyForEachBuilderOnDataMoveToNewPlaceTest026
 * @tc.desc: Test OnDataMoveToNewPlace with various indices
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderOnDataMoveToNewPlaceTest026, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->OnDataMoveToNewPlace(INDEX_0, INDEX_2);
    lazyForEachBuilder->OnDataMoveToNewPlace(INDEX_1, INDEX_5);
}

/**
 * @tc.name: LazyForEachBuilderGetChildByIndexZeroTest027
 * @tc.desc: Test GetChildByIndex with index 0
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderGetChildByIndexZeroTest027, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->GetChildByIndex(INDEX_0, true);
    (void)lazyForEachBuilder->GetChildByIndex(INDEX_0, false);
}

/**
 * @tc.name: LazyForEachBuilderGetChildByIndexConsecutiveTest028
 * @tc.desc: Test GetChildByIndex with consecutive indices
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderGetChildByIndexConsecutiveTest028, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->GetChildByIndex(INDEX_0, true);
    (void)lazyForEachBuilder->GetChildByIndex(INDEX_1, true);
    (void)lazyForEachBuilder->GetChildByIndex(INDEX_2, true);
}

/**
 * @tc.name: LazyForEachBuilderExpandChildrenOnInitialTest029
 * @tc.desc: Test ExpandChildrenOnInitial
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderExpandChildrenOnInitialTest029, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->ExpandChildrenOnInitial();
}

/**
 * @tc.name: LazyForEachBuilderRemoveAllChildTest030
 * @tc.desc: Test RemoveAllChild
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderRemoveAllChildTest030, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->RemoveAllChild();
}

/**
 * @tc.name: LazyForEachBuilderGetCachedUINodeMapTest031
 * @tc.desc: Test GetCachedUINodeMap
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderGetCachedUINodeMapTest031, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->GetCachedUINodeMap();
}

/**
 * @tc.name: LazyForEachBuilderGetAllChildrenTest032
 * @tc.desc: Test GetAllChildren
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderGetAllChildrenTest032, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->GetAllChildren();
}

/**
 * @tc.name: LazyForEachBuilderClearDeletedNodesTest033
 * @tc.desc: Test clearDeletedNodes
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderClearDeletedNodesTest033, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->clearDeletedNodes();
}

/**
 * @tc.name: LazyForEachBuilderSetUseNewInterfaceTest034
 * @tc.desc: Test SetUseNewInterface
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderSetUseNewInterfaceTest034, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->SetUseNewInterface(true);
    lazyForEachBuilder->SetUseNewInterface(false);
}

/**
 * @tc.name: LazyForEachBuilderPaintDebugBoundaryTreeAllTest035
 * @tc.desc: Test PaintDebugBoundaryTreeAll
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderPaintDebugBoundaryTreeAllTest035, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->PaintDebugBoundaryTreeAll(true);
    lazyForEachBuilder->PaintDebugBoundaryTreeAll(false);
}

/**
 * @tc.name: LazyForEachBuilderUpdateMoveFromToTest036
 * @tc.desc: Test UpdateMoveFromTo
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderUpdateMoveFromToTest036, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->UpdateMoveFromTo(INDEX_0, INDEX_5);
    lazyForEachBuilder->UpdateMoveFromTo(INDEX_1, INDEX_10);
}

/**
 * @tc.name: LazyForEachBuilderResetMoveFromToTest037
 * @tc.desc: Test ResetMoveFromTo
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderResetMoveFromToTest037, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    lazyForEachBuilder->UpdateMoveFromTo(INDEX_0, INDEX_5);
    lazyForEachBuilder->ResetMoveFromTo();
}

/**
 * @tc.name: LazyForEachBuilderConvertFromToIndexTest038
 * @tc.desc: Test ConvertFromToIndex
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderConvertFromToIndexTest038, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->ConvertFromToIndex(INDEX_5);
}

/**
 * @tc.name: LazyForEachBuilderGetChildByIndexWithCacheTest039
 * @tc.desc: Test GetChildByIndex with isCache parameter
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderGetChildByIndexWithCacheTest039, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder();
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->GetChildByIndex(INDEX_1, true, true);
    (void)lazyForEachBuilder->GetChildByIndex(INDEX_2, false, true);
}

/**
 * @tc.name: LazyForEachBuilderDeleteExpiringItemImmediatelyTest040
 * @tc.desc: Test builder with deleteExpiringItemImmediately flag
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachBuilderAdvancedTestNg, LazyForEachBuilderDeleteExpiringItemImmediatelyTest040, TestSize.Level1)
{
    auto lazyForEachBuilder = CreateLazyForEachBuilder(true);
    ASSERT_NE(lazyForEachBuilder, nullptr);

    (void)lazyForEachBuilder->GetChildByIndex(INDEX_0, true);
    (void)lazyForEachBuilder->GetChildByIndex(INDEX_1, true);

    lazyForEachBuilder->OnDataDeleted(INDEX_0);
    lazyForEachBuilder->OnDataDeleted(INDEX_1);
}

} // namespace OHOS::Ace::NG
