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

#include "grid_test_ng.h"

#include "test/mock/frameworks/core/animation/mock_animation_manager.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"

#define private public
#define protected public
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_item_event_hub.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/shallow_builder.h"
#include "core/components_ng/pattern/grid/grid_item_drag_manager.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_ITEM_COUNT = 10;
constexpr float TEST_SCALE_FACTOR = 0.95f;
constexpr float SCALE_TOLERANCE = 0.001f;
constexpr int32_t TEST_INVALID_ROW = 100;
constexpr int32_t TEST_INVALID_COL = 50;
constexpr float TEST_DISTANCE_TOLERANCE = 0.001f;
} // namespace

class GridItemDragManagerTestNg : public GridTestNg {
public:
    void SetUp() override
    {
        GridTestNg::SetUp();
        MockAnimationManager::GetInstance().SetTicks(TICK);
    }
    void TearDown() override
    {
        GridTestNg::TearDown();
    }

    RefPtr<GridItemDragManager> CreateDragManager()
    {
        auto model = CreateGrid();
        model.SetColumnsTemplate("1fr 1fr");
        CreateFixedItems(TEST_ITEM_COUNT);
        CreateDone();
        auto host = pattern_->GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        auto gridItemNode = AceType::DynamicCast<FrameNode>(host->GetChildByIndex(0));
        CHECK_NULL_RETURN(gridItemNode, nullptr);
        auto itemPattern = gridItemNode->GetPattern<GridItemPattern>();
        CHECK_NULL_RETURN(itemPattern, nullptr);
        auto manager = AceType::MakeRefPtr<GridItemDragManager>(gridItemNode, nullptr);
        return manager;
    }

    RefPtr<GridItemDragManager> CreateDragManagerWithForEach()
    {
        auto model = CreateGrid();
        model.SetColumnsTemplate("1fr 1fr");
        CreateFixedItems(TEST_ITEM_COUNT);
        CreateDone();
        auto host = pattern_->GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        auto gridItemNode = AceType::DynamicCast<FrameNode>(host->GetChildByIndex(0));
        CHECK_NULL_RETURN(gridItemNode, nullptr);
        auto forEach = ForEachNode::GetOrCreateForEachNode(-1);
        CHECK_NULL_RETURN(forEach, nullptr);
        forEach->SetParent(AceType::WeakClaim(AceType::RawPtr(host)));
        host->AddChild(forEach);
        auto manager = AceType::MakeRefPtr<GridItemDragManager>(gridItemNode, forEach);
        return manager;
    }

    RefPtr<GridItemDragManager> CreateDragManagerWithForEachAndChildren()
    {
        auto model = CreateGrid();
        model.SetColumnsTemplate("1fr 1fr");
        CreateFixedItems(TEST_ITEM_COUNT);
        CreateDone();
        auto host = pattern_->GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        auto gridItemNode = AceType::DynamicCast<FrameNode>(host->GetChildByIndex(0));
        CHECK_NULL_RETURN(gridItemNode, nullptr);
        auto forEach = ForEachNode::GetOrCreateForEachNode(-1);
        CHECK_NULL_RETURN(forEach, nullptr);
        auto children = host->GetChildren();
        std::vector<RefPtr<UINode>> items(children.begin(), children.end());
        for (auto& child : items) {
            host->RemoveChild(child, true);
            forEach->AddChild(child);
        }
        forEach->SetParent(AceType::WeakClaim(AceType::RawPtr(host)));
        host->AddChild(forEach);
        auto manager = AceType::MakeRefPtr<GridItemDragManager>(gridItemNode, forEach);
        return manager;
    }

    GridLayoutInfo& GetLayoutInfo()
    {
        return pattern_->info_;
    }
};

// ============================================================
// ApplyMoveToArray
// ============================================================

/**
 * @tc.name: ApplyMoveToArrayForward001
 * @tc.desc: Test ApplyMoveToArray moving element forward (from < to)
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ApplyMoveToArrayForward001, TestSize.Level1)
{
    std::vector<int32_t> order = { 0, 1, 2, 3, 4 };
    GridItemDragManager::ApplyMoveToArray(order, 1, 3);
    EXPECT_EQ(order[0], 0);
    EXPECT_EQ(order[1], 2);
    EXPECT_EQ(order[2], 3);
    EXPECT_EQ(order[3], 1);
    EXPECT_EQ(order[4], 4);
}

/**
 * @tc.name: ApplyMoveToArrayBackward001
 * @tc.desc: Test ApplyMoveToArray moving element backward (from > to)
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ApplyMoveToArrayBackward001, TestSize.Level1)
{
    std::vector<int32_t> order = { 0, 1, 2, 3, 4 };
    GridItemDragManager::ApplyMoveToArray(order, 3, 1);
    EXPECT_EQ(order[0], 0);
    EXPECT_EQ(order[1], 3);
    EXPECT_EQ(order[2], 1);
    EXPECT_EQ(order[3], 2);
    EXPECT_EQ(order[4], 4);
}

/**
 * @tc.name: ApplyMoveToArraySameIndex001
 * @tc.desc: Test ApplyMoveToArray with from == to
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ApplyMoveToArraySameIndex001, TestSize.Level1)
{
    std::vector<int32_t> order = { 0, 1, 2, 3, 4 };
    GridItemDragManager::ApplyMoveToArray(order, 2, 2);
    EXPECT_EQ(order[0], 0);
    EXPECT_EQ(order[1], 1);
    EXPECT_EQ(order[2], 2);
    EXPECT_EQ(order[3], 3);
    EXPECT_EQ(order[4], 4);
}

/**
 * @tc.name: ApplyMoveToArrayFirstElement001
 * @tc.desc: Test ApplyMoveToArray moving first element
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ApplyMoveToArrayFirstElement001, TestSize.Level1)
{
    std::vector<int32_t> order = { 0, 1, 2, 3 };
    GridItemDragManager::ApplyMoveToArray(order, 0, 3);
    EXPECT_EQ(order[0], 1);
    EXPECT_EQ(order[1], 2);
    EXPECT_EQ(order[2], 3);
    EXPECT_EQ(order[3], 0);
}

/**
 * @tc.name: ApplyMoveToArrayLastElement001
 * @tc.desc: Test ApplyMoveToArray moving last element to front
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ApplyMoveToArrayLastElement001, TestSize.Level1)
{
    std::vector<int32_t> order = { 0, 1, 2, 3 };
    GridItemDragManager::ApplyMoveToArray(order, 3, 0);
    EXPECT_EQ(order[0], 3);
    EXPECT_EQ(order[1], 0);
    EXPECT_EQ(order[2], 1);
    EXPECT_EQ(order[3], 2);
}

/**
 * @tc.name: ApplyMoveToArrayTwoElements001
 * @tc.desc: Test ApplyMoveToArray with only two elements
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ApplyMoveToArrayTwoElements001, TestSize.Level1)
{
    std::vector<int32_t> order = { 10, 20 };
    GridItemDragManager::ApplyMoveToArray(order, 0, 1);
    EXPECT_EQ(order[0], 20);
    EXPECT_EQ(order[1], 10);
}

/**
 * @tc.name: ApplyMoveToArraySingleElement001
 * @tc.desc: Test ApplyMoveToArray with single element
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ApplyMoveToArraySingleElement001, TestSize.Level1)
{
    std::vector<int32_t> order = { 42 };
    GridItemDragManager::ApplyMoveToArray(order, 0, 0);
    EXPECT_EQ(order.size(), 1u);
    EXPECT_EQ(order[0], 42);
}

/**
 * @tc.name: ApplyMoveToArrayAdjacentForward001
 * @tc.desc: Test ApplyMoveToArray with adjacent elements forward
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ApplyMoveToArrayAdjacentForward001, TestSize.Level1)
{
    std::vector<int32_t> order = { 10, 20, 30, 40 };
    GridItemDragManager::ApplyMoveToArray(order, 1, 2);
    EXPECT_EQ(order[0], 10);
    EXPECT_EQ(order[1], 30);
    EXPECT_EQ(order[2], 20);
    EXPECT_EQ(order[3], 40);
}

/**
 * @tc.name: ApplyMoveToArrayAdjacentBackward001
 * @tc.desc: Test ApplyMoveToArray with adjacent elements backward
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ApplyMoveToArrayAdjacentBackward001, TestSize.Level1)
{
    std::vector<int32_t> order = { 10, 20, 30, 40 };
    GridItemDragManager::ApplyMoveToArray(order, 2, 1);
    EXPECT_EQ(order[0], 10);
    EXPECT_EQ(order[1], 30);
    EXPECT_EQ(order[2], 20);
    EXPECT_EQ(order[3], 40);
}

// ============================================================
// FindAvailableColumn
// ============================================================

/**
 * @tc.name: FindAvailableColumnEmptyRow001
 * @tc.desc: Test FindAvailableColumn with empty row
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindAvailableColumnEmptyRow001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    matrix[0] = {};
    int32_t col = manager->FindAvailableColumn(matrix, 0, 1, 4);
    EXPECT_EQ(col, 0);
}

/**
 * @tc.name: FindAvailableColumnNoSpace001
 * @tc.desc: Test FindAvailableColumn when row is full
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindAvailableColumnNoSpace001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    matrix[0] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 } };
    int32_t col = manager->FindAvailableColumn(matrix, 0, 1, 4);
    EXPECT_EQ(col, -1);
}

/**
 * @tc.name: FindAvailableColumnGapInMiddle001
 * @tc.desc: Test FindAvailableColumn with gap in middle
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindAvailableColumnGapInMiddle001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    matrix[0] = { { 0, 1 }, { 3, 2 } };
    int32_t col = manager->FindAvailableColumn(matrix, 0, 1, 4);
    EXPECT_EQ(col, 1);
}

/**
 * @tc.name: FindAvailableColumnMultiSpan001
 * @tc.desc: Test FindAvailableColumn with colSpan > 1
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindAvailableColumnMultiSpan001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    matrix[0] = { { 0, 1 }, { 3, 2 } };
    int32_t col = manager->FindAvailableColumn(matrix, 0, 2, 4);
    EXPECT_EQ(col, 1);
}

/**
 * @tc.name: FindAvailableColumnNonExistentRow001
 * @tc.desc: Test FindAvailableColumn with non-existent row
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindAvailableColumnNonExistentRow001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    int32_t col = manager->FindAvailableColumn(matrix, 0, 1, 4);
    EXPECT_EQ(col, 0);
}

/**
 * @tc.name: FindAvailableColumnSpanExceedsCrossCount001
 * @tc.desc: Test FindAvailableColumn when colSpan exceeds crossCount
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindAvailableColumnSpanExceedsCrossCount001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    matrix[0] = {};
    int32_t col = manager->FindAvailableColumn(matrix, 0, 5, 4);
    EXPECT_EQ(col, -1);
}

/**
 * @tc.name: FindAvailableColumnZeroSpan001
 * @tc.desc: Test FindAvailableColumn returns -1 when colSpan is zero
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindAvailableColumnZeroSpan001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    matrix[0] = {};
    int32_t col = manager->FindAvailableColumn(matrix, 0, 0, 4);
    EXPECT_EQ(col, -1);
}

/**
 * @tc.name: FindAvailableColumnNegativeSpan001
 * @tc.desc: Test FindAvailableColumn returns -1 when colSpan is negative
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindAvailableColumnNegativeSpan001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    matrix[0] = {};
    int32_t col = manager->FindAvailableColumn(matrix, 0, -1, 4);
    EXPECT_EQ(col, -1);
}

/**
 * @tc.name: FindAvailableColumnSpanEqualsCrossCount001
 * @tc.desc: Test FindAvailableColumn succeeds when colSpan equals crossCount on empty row
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindAvailableColumnSpanEqualsCrossCount001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    matrix[0] = {};
    int32_t col = manager->FindAvailableColumn(matrix, 0, 4, 4);
    EXPECT_EQ(col, 0);
}

// ============================================================
// PlaceItemInMatrix
// ============================================================

/**
 * @tc.name: PlaceItemInMatrixBasic001
 * @tc.desc: Test PlaceItemInMatrix with basic item
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, PlaceItemInMatrixBasic001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    GridItemDragManager::SimSpanInfo span = { 1, 1 };
    auto& info = GetLayoutInfo();
    auto [row, col] = manager->PlaceItemInMatrix(info, matrix, 0, span, 3, 100);
    EXPECT_EQ(row, 0);
    EXPECT_EQ(col, 0);
    EXPECT_EQ(matrix[0][0], 0);
}

/**
 * @tc.name: PlaceItemInMatrixSpanExceedsCrossCount001
 * @tc.desc: Test PlaceItemInMatrix when colSpan > crossCount
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, PlaceItemInMatrixSpanExceedsCrossCount001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    GridItemDragManager::SimSpanInfo span = { 1, 3 };
    auto& info = GetLayoutInfo();
    auto [row, col] = manager->PlaceItemInMatrix(info, matrix, 0, span, 2, 100);
    EXPECT_EQ(row, -1);
    EXPECT_EQ(col, -1);
}

/**
 * @tc.name: PlaceItemInMatrixMultiRowSpan001
 * @tc.desc: Test PlaceItemInMatrix with multi-row, multi-col span
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, PlaceItemInMatrixMultiRowSpan001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    GridItemDragManager::SimSpanInfo span = { 2, 2 };
    auto& info = GetLayoutInfo();
    auto [row, col] = manager->PlaceItemInMatrix(info, matrix, 5, span, 3, 100);
    EXPECT_EQ(row, 0);
    EXPECT_EQ(col, 0);
    EXPECT_EQ(matrix[0][0], 5);
    EXPECT_EQ(matrix[0][1], -5);
    EXPECT_EQ(matrix[1][0], -5);
    EXPECT_EQ(matrix[1][1], -5);
}

/**
 * @tc.name: PlaceItemInMatrixSecondItem001
 * @tc.desc: Test PlaceItemInMatrix with two items in one row
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, PlaceItemInMatrixSecondItem001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    GridItemDragManager::SimSpanInfo span = { 1, 1 };
    auto& info = GetLayoutInfo();
    auto [r1, c1] = manager->PlaceItemInMatrix(info, matrix, 0, span, 3, 100);
    EXPECT_EQ(r1, 0);
    EXPECT_EQ(c1, 0);
    auto [r2, c2] = manager->PlaceItemInMatrix(info, matrix, 1, span, 3, 100);
    EXPECT_EQ(r2, 0);
    EXPECT_EQ(c2, 1);
}

// ============================================================
// HandleDragEndAnimation
// ============================================================

/**
 * @tc.name: HandleDragEndAnimationNoHost001
 * @tc.desc: Test HandleDragEndAnimation with null host does not crash
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleDragEndAnimationNoHost001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    EXPECT_NO_FATAL_FAILURE(manager->HandleDragEndAnimation());
}

// ============================================================
// DeInitDragDropEvent
// ============================================================

/**
 * @tc.name: DeInitDragDropEventNullHost001
 * @tc.desc: Test DeInitDragDropEvent with null host does not crash
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, DeInitDragDropEventNullHost001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    manager->dragState_ = GridItemDragState::DRAGGING;
    manager->fromIndex_ = 3;
    EXPECT_NO_FATAL_FAILURE(manager->DeInitDragDropEvent());
}

// ============================================================
// HandleOnItemDragUpdate
// ============================================================

/**
 * @tc.name: HandleOnItemDragUpdateNotDragging001
 * @tc.desc: Test HandleOnItemDragUpdate returns early when not dragging
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleOnItemDragUpdateNotDragging001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    manager->dragState_ = GridItemDragState::IDLE;
    GestureEvent info;
    info.SetOffsetX(10.0f);
    info.SetOffsetY(20.0f);
    EXPECT_NO_FATAL_FAILURE(manager->HandleOnItemDragUpdate(info));
}

/**
 * @tc.name: HandleOnItemDragUpdateLongPressState001
 * @tc.desc: Test HandleOnItemDragUpdate returns early when in LONG_PRESS state
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleOnItemDragUpdateLongPressState001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    manager->dragState_ = GridItemDragState::LONG_PRESS;
    GestureEvent info;
    EXPECT_NO_FATAL_FAILURE(manager->HandleOnItemDragUpdate(info));
}

// ============================================================
// HandleOnItemDragCancel
// ============================================================

/**
 * @tc.name: HandleOnItemDragCancelFromDragging001
 * @tc.desc: Test HandleOnItemDragCancel resets state from DRAGGING
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleOnItemDragCancelFromDragging001, TestSize.Level1)
{
    auto gridNode = FrameNode::CreateFrameNode(V2::GRID_ETS_TAG, 1, AceType::MakeRefPtr<GridPattern>());
    ASSERT_NE(gridNode, nullptr);
    WeakPtr<FrameNode> weakGridNode = AceType::WeakClaim(AceType::RawPtr(gridNode));
    auto shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    auto host = FrameNode::CreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<GridItemPattern>(shallowBuilder));
    ASSERT_NE(host, nullptr);
    host->SetParent(weakGridNode);
    host->renderContext_ = RenderContext::Create();
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    int32_t onMoveEventCnt = 0;
    int32_t onDropCnt = 0;
    lazyForEachNode->onMoveEvent_ = [&onMoveEventCnt](int32_t from, int32_t to) { onMoveEventCnt++; };
    lazyForEachNode->onDropEvent_ = [&onDropCnt](int32_t index) { onDropCnt++; };
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(host, lazyForEachNode);
    manager->dragState_ = GridItemDragState::DRAGGING;
    manager->fromIndex_ = 0;
    manager->scrolling_ = true;

    manager->HandleOnItemDragCancel();

    EXPECT_EQ(onMoveEventCnt, 0);
    EXPECT_EQ(onDropCnt, 0);
    EXPECT_FALSE(manager->scrolling_);
    EXPECT_EQ(manager->dragState_, GridItemDragState::IDLE);
}

/**
 * @tc.name: HandleOnItemDragCancelFromIdle001
 * @tc.desc: Test HandleOnItemDragCancel from IDLE state
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleOnItemDragCancelFromIdle001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    manager->dragState_ = GridItemDragState::IDLE;
    EXPECT_NO_FATAL_FAILURE(manager->HandleOnItemDragCancel());
    EXPECT_EQ(manager->dragState_, GridItemDragState::IDLE);
}

// ============================================================
// HandleOnItemDragEnd
// ============================================================

/**
 * @tc.name: HandleOnItemDragEndResetsState001
 * @tc.desc: Test HandleOnItemDragEnd resets drag state to IDLE
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleOnItemDragEndResetsState001, TestSize.Level1)
{
    auto gridNode = FrameNode::CreateFrameNode(V2::GRID_ETS_TAG, 1, AceType::MakeRefPtr<GridPattern>());
    ASSERT_NE(gridNode, nullptr);
    WeakPtr<FrameNode> weakGridNode = AceType::WeakClaim(AceType::RawPtr(gridNode));
    auto shallowBuilder2 = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    auto host = FrameNode::CreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<GridItemPattern>(shallowBuilder2));
    ASSERT_NE(host, nullptr);
    host->SetParent(weakGridNode);
    host->renderContext_ = RenderContext::Create();
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    int32_t onMoveEventCnt = 0;
    int32_t onDropCnt = 0;
    lazyForEachNode->onMoveEvent_ = [&onMoveEventCnt](int32_t from, int32_t to) { onMoveEventCnt++; };
    lazyForEachNode->onDropEvent_ = [&onDropCnt](int32_t index) { onDropCnt++; };
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(host, lazyForEachNode);
    manager->dragState_ = GridItemDragState::DRAGGING;
    manager->fromIndex_ = 0;

    manager->HandleOnItemDragEnd(GestureEvent());

    EXPECT_EQ(onMoveEventCnt, 0);
    EXPECT_EQ(onDropCnt, 0);
    EXPECT_EQ(manager->dragState_, GridItemDragState::IDLE);
}

// ============================================================
// FindSwapTarget
// ============================================================

/**
 * @tc.name: FindSwapTargetNullGrid001
 * @tc.desc: Test FindSwapTarget returns current when grid is null
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindSwapTargetNullGrid001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    int32_t result = manager->FindSwapTarget(0, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: FindSwapTargetInvalidPosition001
 * @tc.desc: Test FindSwapTarget returns current when position invalid
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindSwapTargetInvalidPosition001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto& info = GetLayoutInfo();
    info.gridMatrix_.clear();
    int32_t result = manager->FindSwapTarget(0, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(result, 0);
}

// ============================================================
// GetGridFrameNode
// ============================================================

/**
 * @tc.name: GetGridFrameNodeNullHost001
 * @tc.desc: Test GetGridFrameNode with null host
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GetGridFrameNodeNullHost001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    auto grid = manager->GetGridFrameNode();
    EXPECT_EQ(grid, nullptr);
}

/**
 * @tc.name: GetGridFrameNodeValidGrid001
 * @tc.desc: Test GetGridFrameNode returns valid grid parent
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GetGridFrameNodeValidGrid001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto grid = manager->GetGridFrameNode();
    ASSERT_NE(grid, nullptr);
    EXPECT_EQ(grid->GetTag(), V2::GRID_ETS_TAG);
}

// ============================================================
// GetParentPaddingOffset
// ============================================================

/**
 * @tc.name: GetParentPaddingOffsetNullGrid001
 * @tc.desc: Test GetParentPaddingOffset with null grid
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GetParentPaddingOffsetNullGrid001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    auto offset = manager->GetParentPaddingOffset();
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: GetParentPaddingOffsetValidGrid001
 * @tc.desc: Test GetParentPaddingOffset with valid grid
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GetParentPaddingOffsetValidGrid001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto offset = manager->GetParentPaddingOffset();
    EXPECT_GE(offset.GetX(), 0.0f);
    EXPECT_GE(offset.GetY(), 0.0f);
}

// ============================================================
// GetIndex
// ============================================================

/**
 * @tc.name: GetIndexNullForEach001
 * @tc.desc: Test GetIndex with null forEach
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GetIndexNullForEach001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    int32_t index = manager->GetIndex();
    EXPECT_EQ(index, -1);
}

// ============================================================
// SetPosition
// ============================================================

/**
 * @tc.name: SetPositionNullHost001
 * @tc.desc: Test SetPosition with null host does not crash
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, SetPositionNullHost001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    EXPECT_NO_FATAL_FAILURE(manager->SetPosition(OffsetF(10.0f, 20.0f)));
}

/**
 * @tc.name: SetPositionValidHost001
 * @tc.desc: Test SetPosition updates render context position
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, SetPositionValidHost001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    EXPECT_NO_FATAL_FAILURE(manager->SetPosition(OffsetF(50.0f, 100.0f)));
}

// ============================================================
// IsInHotZone
// ============================================================

/**
 * @tc.name: IsInHotZoneNullGrid001
 * @tc.desc: Test IsInHotZone with null grid
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, IsInHotZoneNullGrid001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    RectF frameRect(0.0f, 0.0f, 100.0f, 100.0f);
    EXPECT_FALSE(manager->IsInHotZone(0, frameRect));
}

/**
 * @tc.name: IsInHotZoneMiddleItem001
 * @tc.desc: Test IsInHotZone with middle item (should be true)
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, IsInHotZoneMiddleItem001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto gridNode = manager->gridNode_.Upgrade();
    ASSERT_NE(gridNode, nullptr);
    auto gridGeometry = gridNode->GetGeometryNode();
    ASSERT_NE(gridGeometry, nullptr);
    RectF frameRect(0.0f, 50.0f, 100.0f, 100.0f);
    bool result = manager->IsInHotZone(5, frameRect);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsInHotZoneFirstItemAtStart001
 * @tc.desc: Test IsInHotZone with first item at very start
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, IsInHotZoneFirstItemAtStart001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    RectF frameRect(0.0f, 0.0f, 100.0f, 100.0f);
    bool result = manager->IsInHotZone(0, frameRect);
    EXPECT_TRUE(result);
}

// ============================================================
// GetItemMainSize
// ============================================================

/**
 * @tc.name: GetItemMainSizeNullForEach001
 * @tc.desc: Test GetItemMainSize with null forEach returns default
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GetItemMainSizeNullForEach001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    GridLayoutInfo info;
    float size = manager->GetItemMainSize(0, info);
    EXPECT_FLOAT_EQ(size, 100.0f);
}

/**
 * @tc.name: GetItemMainSizeWithRowHeight001
 * @tc.desc: Test GetItemMainSize falls back to row height when node is null
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GetItemMainSizeWithRowHeight001, TestSize.Level1)
{
    auto gridNode = FrameNode::CreateFrameNode(V2::GRID_ETS_TAG, 1, AceType::MakeRefPtr<GridPattern>());
    ASSERT_NE(gridNode, nullptr);
    WeakPtr<FrameNode> weakGridNode = AceType::WeakClaim(AceType::RawPtr(gridNode));
    auto shallowBuilder3 = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    auto host = FrameNode::CreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<GridItemPattern>(shallowBuilder3));
    ASSERT_NE(host, nullptr);
    host->SetParent(weakGridNode);
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(host, lazyForEachNode);
    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.lineHeightMap_[0] = 200.0f;
    info.gridMatrix_[0] = { { 0, 99 } };
    float size = manager->GetItemMainSize(99, info);
    EXPECT_FLOAT_EQ(size, 200.0f);
}

// ============================================================
// GetItemCrossSize
// ============================================================

/**
 * @tc.name: GetItemCrossSizeNullForEach001
 * @tc.desc: Test GetItemCrossSize with null forEach returns default
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GetItemCrossSizeNullForEach001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    GridLayoutInfo info;
    float size = manager->GetItemCrossSize(0, info);
    EXPECT_FLOAT_EQ(size, 100.0f);
}

// ============================================================
// CollectSwapCandidates
// ============================================================

/**
 * @tc.name: CollectSwapCandidatesNullForEach001
 * @tc.desc: Test CollectSwapCandidates with null forEach returns empty
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, CollectSwapCandidatesNullForEach001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    GridLayoutInfo info;
    auto candidates = manager->CollectSwapCandidates(0, OffsetF(0.0f, 0.0f), info);
    EXPECT_TRUE(candidates.empty());
}

// ============================================================
// CalculateFromNewPosition
// ============================================================

/**
 * @tc.name: CalculateFromNewPositionNullForEach001
 * @tc.desc: Test CalculateFromNewPosition with null forEach returns nullopt
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, CalculateFromNewPositionNullForEach001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    GridLayoutInfo info;
    std::vector<GridItemDragManager::SimSpanInfo> spans;
    std::vector<double> crossLens;
    float mainGap = 0.0f;
    float adjustedCrossGap = 0.0f;
    auto result = manager->CalculateFromNewPosition(0, 1, info, spans, mainGap, crossLens, adjustedCrossGap);
    EXPECT_FALSE(result.has_value());
}

// ============================================================
// HandleSwapAnimation
// ============================================================

/**
 * @tc.name: HandleSwapAnimationNullForEach001
 * @tc.desc: Test HandleSwapAnimation with null forEach does not crash
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleSwapAnimationNullForEach001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    EXPECT_NO_FATAL_FAILURE(manager->HandleSwapAnimation(0, 1));
}

// ============================================================
// InitDragDropEvent / DeInitDragDropEvent lifecycle
// ============================================================

/**
 * @tc.name: InitDragDropEventNullHost001
 * @tc.desc: Test InitDragDropEvent with null host does not crash
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, InitDragDropEventNullHost001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    EXPECT_NO_FATAL_FAILURE(manager->InitDragDropEvent());
}

/**
 * @tc.name: InitDragDropEventValidHost001
 * @tc.desc: Test InitDragDropEvent with valid host sets up gesture
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, InitDragDropEventValidHost001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    EXPECT_NO_FATAL_FAILURE(manager->InitDragDropEvent());
}

// ============================================================
// HandleAutoScroll
// ============================================================

/**
 * @tc.name: HandleAutoScrollNullGrid001
 * @tc.desc: Test HandleAutoScroll with null grid does not crash
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleAutoScrollNullGrid001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    RectF frameRect(0.0f, 0.0f, 100.0f, 100.0f);
    PointF point(50.0f, 50.0f);
    EXPECT_NO_FATAL_FAILURE(manager->HandleAutoScroll(0, point, frameRect));
}

// ============================================================
// HandleScrollCallback
// ============================================================

/**
 * @tc.name: HandleScrollCallbackNullHost001
 * @tc.desc: Test HandleScrollCallback with null host does not crash
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleScrollCallbackNullHost001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    EXPECT_NO_FATAL_FAILURE(manager->HandleScrollCallback());
}

// ============================================================
// HandleOnItemLongPress
// ============================================================

/**
 * @tc.name: HandleOnItemLongPressNullHost001
 * @tc.desc: Test HandleOnItemLongPress with null host does not crash
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleOnItemLongPressNullHost001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    GestureEvent info;
    EXPECT_NO_FATAL_FAILURE(manager->HandleOnItemLongPress(info));
}

/**
 * @tc.name: HandleOnItemLongPressSetsState001
 * @tc.desc: Test HandleOnItemLongPress sets state to LONG_PRESS
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleOnItemLongPressSetsState001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GestureEvent info;
    manager->HandleOnItemLongPress(info);
    EXPECT_EQ(manager->dragState_, GridItemDragState::LONG_PRESS);
}

// ============================================================
// HandleOnItemDragStart
// ============================================================

/**
 * @tc.name: HandleOnItemDragStartNullHost001
 * @tc.desc: Test HandleOnItemDragStart with null host does not crash
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleOnItemDragStartNullHost001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    GestureEvent info;
    EXPECT_NO_FATAL_FAILURE(manager->HandleOnItemDragStart(info));
}

/**
 * @tc.name: HandleOnItemDragStartSetsDraggingState001
 * @tc.desc: Test HandleOnItemDragStart sets state to DRAGGING
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HandleOnItemDragStartSetsDraggingState001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GestureEvent info;
    manager->HandleOnItemDragStart(info);
    EXPECT_EQ(manager->dragState_, GridItemDragState::DRAGGING);
}

// ============================================================
// GridItemPattern InitDragManager / DeInitDragManager
// ============================================================

/**
 * @tc.name: GridItemPatternInitDragManager001
 * @tc.desc: Test GridItemPattern::InitDragManager creates drag manager
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GridItemPatternInitDragManager001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridItemNode, nullptr);
    auto itemPattern = gridItemNode->GetPattern<GridItemPattern>();
    ASSERT_NE(itemPattern, nullptr);

    EXPECT_EQ(itemPattern->dragManager_, nullptr);

    auto forEach = AceType::DynamicCast<ForEachBaseNode>(gridItemNode->GetParent());
    if (forEach) {
        itemPattern->InitDragManager(forEach);
        EXPECT_NE(itemPattern->dragManager_, nullptr);
    }
}

/**
 * @tc.name: GridItemPatternDeInitDragManager001
 * @tc.desc: Test GridItemPattern::DeInitDragManager cleans up
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GridItemPatternDeInitDragManager001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridItemNode, nullptr);
    auto itemPattern = gridItemNode->GetPattern<GridItemPattern>();
    ASSERT_NE(itemPattern, nullptr);

    auto forEach = AceType::DynamicCast<ForEachBaseNode>(gridItemNode->GetParent());
    if (forEach) {
        itemPattern->InitDragManager(forEach);
        ASSERT_NE(itemPattern->dragManager_, nullptr);

        itemPattern->DeInitDragManager();
        EXPECT_EQ(itemPattern->dragManager_, nullptr);
    }
}

/**
 * @tc.name: GridItemPatternDeInitDragManagerNoCrash001
 * @tc.desc: Test GridItemPattern::DeInitDragManager with no drag manager
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GridItemPatternDeInitDragManagerNoCrash001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridItemNode, nullptr);
    auto itemPattern = gridItemNode->GetPattern<GridItemPattern>();
    ASSERT_NE(itemPattern, nullptr);

    EXPECT_NO_FATAL_FAILURE(itemPattern->DeInitDragManager());
    EXPECT_EQ(itemPattern->dragManager_, nullptr);
}

// ============================================================
// Constructor
// ============================================================

/**
 * @tc.name: ConstructorNullHost001
 * @tc.desc: Test GridItemDragManager constructor with null host
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ConstructorNullHost001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    EXPECT_EQ(manager->GetHost(), nullptr);
    EXPECT_EQ(manager->dragState_, GridItemDragState::IDLE);
    EXPECT_EQ(manager->currentIndex_, -1);
    EXPECT_EQ(manager->fromIndex_, -1);
    EXPECT_FALSE(manager->scrolling_);
    EXPECT_EQ(manager->totalCount_, -1);
}

/**
 * @tc.name: ConstructorValidHost001
 * @tc.desc: Test GridItemDragManager constructor with valid host sets grid
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ConstructorValidHost001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    EXPECT_NE(manager->GetHost(), nullptr);
    auto grid = manager->gridNode_.Upgrade();
    EXPECT_NE(grid, nullptr);
}

// ============================================================
// FindNeighborIndex
// ============================================================

/**
 * @tc.name: FindNeighborIndexRowNotFound001
 * @tc.desc: Test FindNeighborIndex with non-existent row returns -1
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindNeighborIndexRowNotFound001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto& info = GetLayoutInfo();
    int32_t result = manager->FindNeighborIndex(TEST_INVALID_ROW, 0, info);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: FindNeighborIndexColNotFound001
 * @tc.desc: Test FindNeighborIndex with non-existent col returns -1
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindNeighborIndexColNotFound001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto& info = GetLayoutInfo();
    int32_t result = manager->FindNeighborIndex(0, TEST_INVALID_COL, info);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: FindNeighborIndexValidPosition001
 * @tc.desc: Test FindNeighborIndex returns correct index for valid positions
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindNeighborIndexValidPosition001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto& info = GetLayoutInfo();
    EXPECT_EQ(manager->FindNeighborIndex(0, 0, info), 0);
    EXPECT_EQ(manager->FindNeighborIndex(0, 1, info), 1);
    EXPECT_EQ(manager->FindNeighborIndex(1, 0, info), 2);
    EXPECT_EQ(manager->FindNeighborIndex(1, 1, info), 3);
}

/**
 * @tc.name: FindNeighborIndexNegativeValue001
 * @tc.desc: Test FindNeighborIndex with negative value in matrix (span marker) returns abs value
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindNeighborIndexNegativeValue001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto& info = GetLayoutInfo();
    info.gridMatrix_[TEST_INVALID_ROW][0] = -5;
    int32_t result = manager->FindNeighborIndex(TEST_INVALID_ROW, 0, info);
    EXPECT_EQ(result, 5);
}

// ============================================================
// SetNearbyNodeScale
// ============================================================

/**
 * @tc.name: SetNearbyNodeScaleNullNode001
 * @tc.desc: Test SetNearbyNodeScale with null node does not crash and scaleNode_ stays empty
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, SetNearbyNodeScaleNullNode001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    EXPECT_NO_FATAL_FAILURE(manager->SetNearbyNodeScale(nullptr, TEST_SCALE_FACTOR));
    EXPECT_TRUE(manager->scaleNode_.empty());
}

/**
 * @tc.name: SetNearbyNodeScaleDefaultScale001
 * @tc.desc: Test SetNearbyNodeScale applies scale to node with default transform scale
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, SetNearbyNodeScaleDefaultScale001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    auto node = FrameNode::CreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<GridItemPattern>(shallowBuilder));
    ASSERT_NE(node, nullptr);
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    manager->SetNearbyNodeScale(node, TEST_SCALE_FACTOR);
    auto scale = renderContext->GetTransformScaleValue({1.0f, 1.0f});
    EXPECT_NEAR(scale.x, TEST_SCALE_FACTOR, SCALE_TOLERANCE);
    EXPECT_NEAR(scale.y, TEST_SCALE_FACTOR, SCALE_TOLERANCE);
}

/**
 * @tc.name: SetNearbyNodeScaleWithPrevScale001
 * @tc.desc: Test SetNearbyNodeScale uses prevScaleNode_ as base when present
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, SetNearbyNodeScaleWithPrevScale001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    auto node = FrameNode::CreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<GridItemPattern>(shallowBuilder));
    ASSERT_NE(node, nullptr);
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    VectorF prevScale{2.0f, 2.0f};
    manager->prevScaleNode_.emplace(WeakPtr<RenderContext>(renderContext), prevScale);
    manager->SetNearbyNodeScale(node, TEST_SCALE_FACTOR);

    auto scale = renderContext->GetTransformScaleValue({1.0f, 1.0f});
    EXPECT_NEAR(scale.x, 2.0f * TEST_SCALE_FACTOR, SCALE_TOLERANCE);
    EXPECT_NEAR(scale.y, 2.0f * TEST_SCALE_FACTOR, SCALE_TOLERANCE);
}

/**
 * @tc.name: SetNearbyNodeScaleRecordsInScaleNode001
 * @tc.desc: Test SetNearbyNodeScale records the original scale in scaleNode_
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, SetNearbyNodeScaleRecordsInScaleNode001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    auto node = FrameNode::CreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<GridItemPattern>(shallowBuilder));
    ASSERT_NE(node, nullptr);
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    manager->SetNearbyNodeScale(node, TEST_SCALE_FACTOR);
    EXPECT_EQ(manager->scaleNode_.size(), 1u);
    auto it = manager->scaleNode_.find(renderContext);
    EXPECT_NE(it, manager->scaleNode_.end());
    EXPECT_NEAR(it->second.x, 1.0f, SCALE_TOLERANCE);
    EXPECT_NEAR(it->second.y, 1.0f, SCALE_TOLERANCE);
}

// ============================================================
// ResetPrevScaleNode
// ============================================================

/**
 * @tc.name: ResetPrevScaleNodeEmptyMaps001
 * @tc.desc: Test ResetPrevScaleNode with empty maps does not crash
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ResetPrevScaleNodeEmptyMaps001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    EXPECT_NO_FATAL_FAILURE(manager->ResetPrevScaleNode());
    EXPECT_TRUE(manager->prevScaleNode_.empty());
    EXPECT_TRUE(manager->scaleNode_.empty());
}

/**
 * @tc.name: ResetPrevScaleNodeResetsOldNode001
 * @tc.desc: Test ResetPrevScaleNode restores node not in scaleNode_ to previous scale
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ResetPrevScaleNodeResetsOldNode001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    auto node = FrameNode::CreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<GridItemPattern>(shallowBuilder));
    ASSERT_NE(node, nullptr);
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    renderContext->UpdateTransformScale({TEST_SCALE_FACTOR, TEST_SCALE_FACTOR});
    VectorF originalScale{1.0f, 1.0f};
    manager->prevScaleNode_.emplace(WeakPtr<RenderContext>(renderContext), originalScale);

    manager->ResetPrevScaleNode();

    auto scale = renderContext->GetTransformScaleValue({0.0f, 0.0f});
    EXPECT_NEAR(scale.x, originalScale.x, SCALE_TOLERANCE);
    EXPECT_NEAR(scale.y, originalScale.y, SCALE_TOLERANCE);
}

/**
 * @tc.name: ResetPrevScaleNodeKeepsCurrentNode001
 * @tc.desc: Test ResetPrevScaleNode does not restore node present in scaleNode_
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ResetPrevScaleNodeKeepsCurrentNode001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    auto node = FrameNode::CreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<GridItemPattern>(shallowBuilder));
    ASSERT_NE(node, nullptr);
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    VectorF originalScale{1.0f, 1.0f};
    VectorF currentScale{TEST_SCALE_FACTOR, TEST_SCALE_FACTOR};
    WeakPtr<RenderContext> weakRender(renderContext);
    manager->prevScaleNode_.emplace(weakRender, originalScale);
    manager->scaleNode_.emplace(weakRender, originalScale);
    renderContext->UpdateTransformScale(currentScale);

    manager->ResetPrevScaleNode();

    auto scale = renderContext->GetTransformScaleValue({0.0f, 0.0f});
    EXPECT_NEAR(scale.x, currentScale.x, SCALE_TOLERANCE);
    EXPECT_NEAR(scale.y, currentScale.y, SCALE_TOLERANCE);
}

/**
 * @tc.name: ResetPrevScaleNodeSwapsMaps001
 * @tc.desc: Test ResetPrevScaleNode swaps scaleNode_ into prevScaleNode_ and clears scaleNode_
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ResetPrevScaleNodeSwapsMaps001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    auto node = FrameNode::CreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, 0, AceType::MakeRefPtr<GridItemPattern>(shallowBuilder));
    ASSERT_NE(node, nullptr);
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    VectorF prevScale{1.0f, 1.0f};
    VectorF currScale{2.0f, 2.0f};
    WeakPtr<RenderContext> weakRender(renderContext);
    manager->prevScaleNode_.emplace(weakRender, prevScale);
    manager->scaleNode_.emplace(weakRender, currScale);

    manager->ResetPrevScaleNode();

    EXPECT_EQ(manager->prevScaleNode_.size(), 1u);
    auto it = manager->prevScaleNode_.find(weakRender);
    EXPECT_NE(it, manager->prevScaleNode_.end());
    EXPECT_NEAR(it->second.x, currScale.x, SCALE_TOLERANCE);
    EXPECT_TRUE(manager->scaleNode_.empty());
}

// ============================================================
// ScaleNearbyItems
// ============================================================

/**
 * @tc.name: ScaleNearbyItemsNullGrid001
 * @tc.desc: Test ScaleNearbyItems with null grid does not crash
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleNearbyItemsNullGrid001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    RectF rect(0.0f, 0.0f, 100.0f, 100.0f);
    OffsetF delta(10.0f, 10.0f);
    EXPECT_NO_FATAL_FAILURE(manager->ScaleNearbyItems(0, rect, delta));
}

/**
 * @tc.name: ScaleNearbyItemsNullForEach001
 * @tc.desc: Test ScaleNearbyItems with null forEach returns early without crash
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleNearbyItemsNullForEach001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    RectF rect(0.0f, 0.0f, 100.0f, 100.0f);
    OffsetF delta(10.0f, 10.0f);
    EXPECT_NO_FATAL_FAILURE(manager->ScaleNearbyItems(0, rect, delta));
}

/**
 * @tc.name: ScaleNearbyItemsInvalidPosition001
 * @tc.desc: Test ScaleNearbyItems with invalid item position resets and returns early
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleNearbyItemsInvalidPosition001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto& info = GetLayoutInfo();
    info.gridMatrix_.clear();
    RectF rect(0.0f, 0.0f, 100.0f, 100.0f);
    OffsetF delta(10.0f, 10.0f);
    EXPECT_NO_FATAL_FAILURE(manager->ScaleNearbyItems(0, rect, delta));
}

/**
 * @tc.name: ScaleNearbyItemsZeroDelta001
 * @tc.desc: Test ScaleNearbyItems with zero delta performs no scaling
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleNearbyItemsZeroDelta001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEach();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    RectF rect(0.0f, 0.0f, 100.0f, 100.0f);
    OffsetF delta(0.0f, 0.0f);
    EXPECT_NO_FATAL_FAILURE(manager->ScaleNearbyItems(0, rect, delta));
    EXPECT_TRUE(manager->prevScaleNode_.empty());
}

/**
 * @tc.name: ScaleNearbyItemsPositiveMainDelta001
 * @tc.desc: Test ScaleNearbyItems with positive main delta scales main-axis neighbor
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleNearbyItemsPositiveMainDelta001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEachAndChildren();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto host = manager->GetHost();
    ASSERT_NE(host, nullptr);
    auto geometry = host->GetGeometryNode();
    ASSERT_NE(geometry, nullptr);
    auto rect = geometry->GetMarginFrameRect();
    OffsetF delta(0.0f, rect.Height());

    EXPECT_NO_FATAL_FAILURE(manager->ScaleNearbyItems(0, rect, delta));
    EXPECT_FALSE(manager->prevScaleNode_.empty());
}

/**
 * @tc.name: ScaleNearbyItemsPositiveCrossDelta001
 * @tc.desc: Test ScaleNearbyItems with positive cross delta scales cross-axis neighbor
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleNearbyItemsPositiveCrossDelta001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEachAndChildren();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto host = manager->GetHost();
    ASSERT_NE(host, nullptr);
    auto geometry = host->GetGeometryNode();
    ASSERT_NE(geometry, nullptr);
    auto rect = geometry->GetMarginFrameRect();
    OffsetF delta(rect.Width(), 0.0f);

    EXPECT_NO_FATAL_FAILURE(manager->ScaleNearbyItems(0, rect, delta));
    EXPECT_FALSE(manager->prevScaleNode_.empty());
}

// ============================================================
// CalculateDistance
// ============================================================

/**
 * @tc.name: CalculateDistanceBasic001
 * @tc.desc: Test CalculateDistance returns correct Euclidean distance (3-4-5 triangle)
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, CalculateDistanceBasic001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    OffsetF pos1(0.0f, 0.0f);
    OffsetF pos2(3.0f, 4.0f);
    float distance = manager->CalculateDistance(pos1, pos2);
    EXPECT_NEAR(distance, 5.0f, TEST_DISTANCE_TOLERANCE);
}

/**
 * @tc.name: CalculateDistanceZero001
 * @tc.desc: Test CalculateDistance returns zero for identical points
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, CalculateDistanceZero001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    OffsetF pos(5.0f, 5.0f);
    float distance = manager->CalculateDistance(pos, pos);
    EXPECT_NEAR(distance, 0.0f, TEST_DISTANCE_TOLERANCE);
}

// ============================================================
// SelectBestCandidate
// ============================================================

/**
 * @tc.name: SelectBestCandidateCloser001
 * @tc.desc: Test SelectBestCandidate returns candidate when it is closer
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, SelectBestCandidateCloser001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    int32_t result = manager->SelectBestCandidate(0, true, 1, 2, 5.0f, 10.0f);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: SelectBestCandidateFarther001
 * @tc.desc: Test SelectBestCandidate returns currentBest when candidate is farther
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, SelectBestCandidateFarther001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    int32_t result = manager->SelectBestCandidate(0, true, 1, 2, 15.0f, 10.0f);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: SelectBestCandidateEqualCandidateIsCurrent001
 * @tc.desc: Test SelectBestCandidate returns candidate when it equals currentIndex at tie
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, SelectBestCandidateEqualCandidateIsCurrent001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    float dist = 10.0f;
    int32_t result = manager->SelectBestCandidate(2, true, 1, 2, dist, dist);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: SelectBestCandidateEqualBestIsCurrent001
 * @tc.desc: Test SelectBestCandidate returns currentBest when it equals currentIndex at tie
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, SelectBestCandidateEqualBestIsCurrent001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    float dist = 10.0f;
    int32_t result = manager->SelectBestCandidate(1, true, 1, 3, dist, dist);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: SelectBestCandidateEqualMovingDown001
 * @tc.desc: Test SelectBestCandidate returns larger index when movingDown at tie
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, SelectBestCandidateEqualMovingDown001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    float dist = 10.0f;
    int32_t result = manager->SelectBestCandidate(0, true, 2, 5, dist, dist);
    EXPECT_EQ(result, 5);
}

/**
 * @tc.name: SelectBestCandidateEqualMovingUp001
 * @tc.desc: Test SelectBestCandidate returns smaller index when moving up at tie
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, SelectBestCandidateEqualMovingUp001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    float dist = 10.0f;
    int32_t result = manager->SelectBestCandidate(0, false, 5, 2, dist, dist);
    EXPECT_EQ(result, 2);
}

// ============================================================
// CalculateCrossPosition
// ============================================================

/**
 * @tc.name: CalculateCrossPositionColZero001
 * @tc.desc: Test CalculateCrossPosition returns zero for column 0
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, CalculateCrossPositionColZero001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    std::vector<double> crossLens = {100.0, 200.0};
    float crossPos = manager->CalculateCrossPosition(0, 10.0f, crossLens, nullptr);
    EXPECT_FLOAT_EQ(crossPos, 0.0f);
}

/**
 * @tc.name: CalculateCrossPositionColTwo001
 * @tc.desc: Test CalculateCrossPosition sums crossLens and gaps for column 2
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, CalculateCrossPositionColTwo001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    std::vector<double> crossLens = {100.0, 200.0};
    float adjustedCrossGap = 10.0f;
    float crossPos = manager->CalculateCrossPosition(2, adjustedCrossGap, crossLens, nullptr);
    EXPECT_FLOAT_EQ(crossPos, 100.0f + 200.0f + 2.0f * adjustedCrossGap);
}

// ============================================================
// FindMaxIndexRow
// ============================================================

/**
 * @tc.name: FindMaxIndexRowBasic001
 * @tc.desc: Test FindMaxIndexRow returns row containing the largest positive index
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindMaxIndexRowBasic001, TestSize.Level1)
{
    GridItemDragManager::SimMatrix matrix;
    matrix[0] = { {0, 5}, {1, 3} };
    matrix[2] = { {0, 10} };
    int32_t result = GridItemDragManager::FindMaxIndexRow(matrix);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: FindMaxIndexRowEmpty001
 * @tc.desc: Test FindMaxIndexRow returns 0 for empty matrix
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindMaxIndexRowEmpty001, TestSize.Level1)
{
    GridItemDragManager::SimMatrix matrix;
    int32_t result = GridItemDragManager::FindMaxIndexRow(matrix);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: FindMaxIndexRowNegativeOnly001
 * @tc.desc: Test FindMaxIndexRow skips negative values, returns 0 when only negatives exist
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindMaxIndexRowNegativeOnly001, TestSize.Level1)
{
    GridItemDragManager::SimMatrix matrix;
    matrix[3] = { {0, -1}, {1, -2} };
    int32_t result = GridItemDragManager::FindMaxIndexRow(matrix);
    EXPECT_EQ(result, 0);
}

// ============================================================
// FindPlacementStartRow
// ============================================================

/**
 * @tc.name: FindPlacementStartRowEmptyMatrix001
 * @tc.desc: Test FindPlacementStartRow with empty matrix and empty gridMatrix returns 0
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindPlacementStartRowEmptyMatrix001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    auto& info = GetLayoutInfo();
    info.gridMatrix_.clear();
    int32_t result = manager->FindPlacementStartRow(matrix, info);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: FindPlacementStartRowFromMatrix001
 * @tc.desc: Test FindPlacementStartRow uses matrix when non-empty
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, FindPlacementStartRowFromMatrix001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    GridItemDragManager::SimMatrix matrix;
    matrix[5] = { {0, 10} };
    auto& info = GetLayoutInfo();
    int32_t result = manager->FindPlacementStartRow(matrix, info);
    EXPECT_EQ(result, 5);
}

// ============================================================
// GetColSpanForIrregularItem
// ============================================================

/**
 * @tc.name: GetColSpanForIrregularItemNullGrid001
 * @tc.desc: Test GetColSpanForIrregularItem returns crossSpan when grid is null
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GetColSpanForIrregularItemNullGrid001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    EXPECT_EQ(manager->GetColSpanForIrregularItem(3), 3);
}

/**
 * @tc.name: GetColSpanForIrregularItemValidGrid001
 * @tc.desc: Test GetColSpanForIrregularItem returns crossSpan when crossCount > 1
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GetColSpanForIrregularItemValidGrid001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    EXPECT_EQ(manager->GetColSpanForIrregularItem(2), 2);
}

// ============================================================
// ComputeMovementBounds
// ============================================================

/**
 * @tc.name: ComputeMovementBoundsZeroMove001
 * @tc.desc: Test ComputeMovementBounds with zero delta sets zeroMove flag
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ComputeMovementBoundsZeroMove001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto& info = GetLayoutInfo();
    auto bounds = manager->ComputeMovementBounds(0, 0, 0, OffsetF(0.0f, 0.0f), info);
    EXPECT_TRUE(bounds.zeroMove);
}

/**
 * @tc.name: ComputeMovementBoundsPositiveDelta001
 * @tc.desc: Test ComputeMovementBounds with positive delta computes correct row range
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ComputeMovementBoundsPositiveDelta001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto& info = GetLayoutInfo();
    auto bounds = manager->ComputeMovementBounds(0, 0, 0, OffsetF(0.0f, 500.0f), info);
    EXPECT_FALSE(bounds.zeroMove);
    EXPECT_EQ(bounds.startRow, 0);
    EXPECT_GT(bounds.endRow, 0);
    EXPECT_EQ(bounds.startCol, 0);
    EXPECT_EQ(bounds.endCol, info.crossCount_ - 1);
}

/**
 * @tc.name: ComputeMovementBoundsNegativeDelta001
 * @tc.desc: Test ComputeMovementBounds with negative delta computes correct bounds
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ComputeMovementBoundsNegativeDelta001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto& info = GetLayoutInfo();
    auto bounds = manager->ComputeMovementBounds(4, 0, 2, OffsetF(0.0f, -500.0f), info);
    EXPECT_FALSE(bounds.zeroMove);
    EXPECT_EQ(bounds.endRow, 2);
    EXPECT_EQ(bounds.startRow, -3);
}

// ============================================================
// IsRowInViewport
// ============================================================

/**
 * @tc.name: IsRowInViewportNotInMap001
 * @tc.desc: Test IsRowInViewport returns false for row not in lineHeightMap_
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, IsRowInViewportNotInMap001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto& info = GetLayoutInfo();
    EXPECT_FALSE(manager->IsRowInViewport(TEST_INVALID_ROW, 0.0f, 1000.0f, info));
}

/**
 * @tc.name: IsRowInViewportVisibleRow001
 * @tc.desc: Test IsRowInViewport returns true for visible row after layout
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, IsRowInViewportVisibleRow001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    auto& info = GetLayoutInfo();
    auto grid = manager->gridNode_.Upgrade();
    ASSERT_NE(grid, nullptr);
    auto gridGeometry = grid->GetGeometryNode();
    ASSERT_NE(gridGeometry, nullptr);
    float mainSize = gridGeometry->GetFrameSize().MainSize(Axis::VERTICAL);
    EXPECT_TRUE(manager->IsRowInViewport(0, 0.0f, mainSize, info));
}

// ============================================================
// CancelDragOnGridChange
// ============================================================

/**
 * @tc.name: CancelDragOnGridChangeNullGrid001
 * @tc.desc: Test CancelDragOnGridChange returns false with null grid
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, CancelDragOnGridChangeNullGrid001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    EXPECT_FALSE(manager->CancelDragOnGridChange());
}

// ============================================================
// StopAutoScroll
// ============================================================

/**
 * @tc.name: StopAutoScrollNullGrid001
 * @tc.desc: Test StopAutoScroll does not crash with null grid
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, StopAutoScrollNullGrid001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    EXPECT_NO_FATAL_FAILURE(manager->StopAutoScroll());
}

// ============================================================
// IsItemInViewport (with non-null forEach)
// ============================================================

/**
 * @tc.name: IsItemInViewportVisibleItem001
 * @tc.desc: Test IsItemInViewport returns true for item in viewport with valid forEach
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, IsItemInViewportVisibleItem001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEach();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto& info = GetLayoutInfo();
    EXPECT_TRUE(manager->IsItemInViewport(0, info));
}

/**
 * @tc.name: IsItemInViewportOutOfRange001
 * @tc.desc: Test IsItemInViewport returns false for index outside startIndex_..endIndex_
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, IsItemInViewportOutOfRange001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEach();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto& info = GetLayoutInfo();
    int32_t outOfRange = info.endIndex_ - manager->forEachStartIndex_ + 1;
    EXPECT_FALSE(manager->IsItemInViewport(outOfRange, info));
}

// ============================================================
// GetRowRangeForItem (with non-null forEach)
// ============================================================

/**
 * @tc.name: GetRowRangeForItemFirstItem001
 * @tc.desc: Test GetRowRangeForItem returns correct row range for item 0 with valid forEach
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GetRowRangeForItemFirstItem001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEach();
    ASSERT_NE(manager, nullptr);
    auto& info = GetLayoutInfo();
    auto [startRow, endRow] = manager->GetRowRangeForItem(0, info);
    EXPECT_EQ(startRow, 0);
    EXPECT_EQ(endRow, 0);
}

/**
 * @tc.name: GetRowRangeForItemThirdItem001
 * @tc.desc: Test GetRowRangeForItem returns correct row range for item 2 (row 1 in 2-col grid)
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, GetRowRangeForItemThirdItem001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEach();
    ASSERT_NE(manager, nullptr);
    auto& info = GetLayoutInfo();
    auto [startRow, endRow] = manager->GetRowRangeForItem(2, info);
    EXPECT_EQ(startRow, 1);
    EXPECT_EQ(endRow, 1);
}

// ============================================================
// ScaleMainAxisNeighbor
// ============================================================

/**
 * @tc.name: ScaleMainAxisNeighborNeighborNotFound001
 * @tc.desc: Test ScaleMainAxisNeighbor returns false when neighbor row does not exist
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleMainAxisNeighborNeighborNotFound001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEach();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto forEach = AceType::DynamicCast<ForEachBaseNode>(manager->forEachNode_.Upgrade());
    ASSERT_NE(forEach, nullptr);
    auto& info = GetLayoutInfo();
    RectF rect(0.0f, 0.0f, 100.0f, 100.0f);
    // Row TEST_INVALID_ROW does not exist in gridMatrix_
    auto result = manager->ScaleMainAxisNeighbor(0, 0, 0, TEST_INVALID_ROW, 1,
        rect, 50.0f, 0, TEST_ITEM_COUNT - 1, info, forEach);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScaleMainAxisNeighborSelfIndex001
 * @tc.desc: Test ScaleMainAxisNeighbor returns false when neighbor equals currentIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleMainAxisNeighborSelfIndex001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEach();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto forEach = AceType::DynamicCast<ForEachBaseNode>(manager->forEachNode_.Upgrade());
    ASSERT_NE(forEach, nullptr);
    auto& info = GetLayoutInfo();
    RectF rect(0.0f, 0.0f, 100.0f, 100.0f);
    // mainRowStep=0, so FindNeighborIndex(0+0, 0) finds item 0 which == currentIndex 0
    auto result = manager->ScaleMainAxisNeighbor(0, 0, 0, 0, 1,
        rect, 50.0f, 0, TEST_ITEM_COUNT - 1, info, forEach);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScaleMainAxisNeighborScalesSuccessfully001
 * @tc.desc: Test ScaleMainAxisNeighbor scales neighbor and returns true
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleMainAxisNeighborScalesSuccessfully001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEachAndChildren();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto forEach = AceType::DynamicCast<ForEachBaseNode>(manager->forEachNode_.Upgrade());
    ASSERT_NE(forEach, nullptr);
    auto& info = GetLayoutInfo();
    auto host = manager->GetHost();
    ASSERT_NE(host, nullptr);
    auto geometry = host->GetGeometryNode();
    ASSERT_NE(geometry, nullptr);
    auto rect = geometry->GetMarginFrameRect();
    // Item 0 at row 0, step=1 finds item 2 at row 1 (different center)
    auto result = manager->ScaleMainAxisNeighbor(0, 0, 0, 1, 1,
        rect, rect.Height(), 0, TEST_ITEM_COUNT - 1, info, forEach);
    EXPECT_TRUE(result);
    EXPECT_FALSE(manager->scaleNode_.empty());
}

// ============================================================
// ScaleCrossAxisNeighbor
// ============================================================

/**
 * @tc.name: ScaleCrossAxisNeighborNeighborNotFound001
 * @tc.desc: Test ScaleCrossAxisNeighbor returns false when neighbor col does not exist
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleCrossAxisNeighborNeighborNotFound001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEach();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto forEach = AceType::DynamicCast<ForEachBaseNode>(manager->forEachNode_.Upgrade());
    ASSERT_NE(forEach, nullptr);
    auto& info = GetLayoutInfo();
    RectF rect(0.0f, 0.0f, 100.0f, 100.0f);
    // Cross step to TEST_INVALID_COL which does not exist
    auto result = manager->ScaleCrossAxisNeighbor(0, 0, 0, TEST_INVALID_COL, 1,
        rect, 50.0f, 0, TEST_ITEM_COUNT - 1, info, forEach);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScaleCrossAxisNeighborOutOfRange001
 * @tc.desc: Test ScaleCrossAxisNeighbor returns false when neighbor is out of range
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleCrossAxisNeighborOutOfRange001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEach();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto forEach = AceType::DynamicCast<ForEachBaseNode>(manager->forEachNode_.Upgrade());
    ASSERT_NE(forEach, nullptr);
    auto& info = GetLayoutInfo();
    RectF rect(0.0f, 0.0f, 100.0f, 100.0f);
    // endIdx=0 means only item 0 is valid; item 1 at col 1 is out of range
    auto result = manager->ScaleCrossAxisNeighbor(0, 0, 0, 1, 1,
        rect, 50.0f, 0, 0, info, forEach);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScaleCrossAxisNeighborScalesSuccessfully001
 * @tc.desc: Test ScaleCrossAxisNeighbor scales neighbor in same row and returns true
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleCrossAxisNeighborScalesSuccessfully001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEachAndChildren();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto forEach = AceType::DynamicCast<ForEachBaseNode>(manager->forEachNode_.Upgrade());
    ASSERT_NE(forEach, nullptr);
    auto& info = GetLayoutInfo();
    auto host = manager->GetHost();
    ASSERT_NE(host, nullptr);
    auto geometry = host->GetGeometryNode();
    ASSERT_NE(geometry, nullptr);
    auto rect = geometry->GetMarginFrameRect();
    // Item 0 at (row=0, col=0), step=1 finds item 1 at (row=0, col=1), same row
    auto result = manager->ScaleCrossAxisNeighbor(0, 0, 0, 1, 1,
        rect, rect.Width(), 0, TEST_ITEM_COUNT - 1, info, forEach);
    EXPECT_TRUE(result);
    EXPECT_FALSE(manager->scaleNode_.empty());
}

// ============================================================
// ScaleDiagonalNeighbor
// ============================================================

/**
 * @tc.name: ScaleDiagonalNeighborNeighborNotFound001
 * @tc.desc: Test ScaleDiagonalNeighbor does not crash when neighbor does not exist
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleDiagonalNeighborNeighborNotFound001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEach();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto forEach = AceType::DynamicCast<ForEachBaseNode>(manager->forEachNode_.Upgrade());
    ASSERT_NE(forEach, nullptr);
    auto& info = GetLayoutInfo();
    RectF rect(0.0f, 0.0f, 100.0f, 100.0f);
    OffsetF delta(10.0f, 10.0f);
    EXPECT_NO_FATAL_FAILURE(manager->ScaleDiagonalNeighbor(0, 0, 0, TEST_INVALID_ROW, TEST_INVALID_COL,
        rect, delta, 0, TEST_ITEM_COUNT - 1, info, forEach));
}

/**
 * @tc.name: ScaleDiagonalNeighborScalesSuccessfully001
 * @tc.desc: Test ScaleDiagonalNeighbor scales diagonal neighbor when main and cross both valid
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, ScaleDiagonalNeighborScalesSuccessfully001, TestSize.Level1)
{
    auto manager = CreateDragManagerWithForEachAndChildren();
    ASSERT_NE(manager, nullptr);
    manager->axis_ = Axis::VERTICAL;
    auto forEach = AceType::DynamicCast<ForEachBaseNode>(manager->forEachNode_.Upgrade());
    ASSERT_NE(forEach, nullptr);
    auto& info = GetLayoutInfo();
    auto host = manager->GetHost();
    ASSERT_NE(host, nullptr);
    auto geometry = host->GetGeometryNode();
    ASSERT_NE(geometry, nullptr);
    auto rect = geometry->GetMarginFrameRect();
    // Item 0 at (0,0), step (1,1) finds item 3 at (1,1)
    OffsetF delta(rect.Width(), rect.Height());
    EXPECT_NO_FATAL_FAILURE(manager->ScaleDiagonalNeighbor(0, 0, 0, 1, 1,
        rect, delta, 0, TEST_ITEM_COUNT - 1, info, forEach));
    EXPECT_FALSE(manager->scaleNode_.empty());
}

} // namespace OHOS::Ace::NG
