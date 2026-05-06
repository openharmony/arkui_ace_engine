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
#include "core/components_ng/pattern/grid/grid_item_drag_manager.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_ITEM_COUNT = 10;
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
    auto [row, col] = manager->PlaceItemInMatrix(GetLayoutInfo(), matrix, 0, span, 3);
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
    auto [row, col] = manager->PlaceItemInMatrix(GetLayoutInfo(), matrix, 0, span, 2);
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
    auto [row, col] = manager->PlaceItemInMatrix(GetLayoutInfo(), matrix, 5, span, 3);
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
    auto [r1, c1] = manager->PlaceItemInMatrix(GetLayoutInfo(), matrix, 0, span, 3);
    EXPECT_EQ(r1, 0);
    EXPECT_EQ(c1, 0);
    auto [r2, c2] = manager->PlaceItemInMatrix(GetLayoutInfo(), matrix, 1, span, 3);
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
 * @tc.name: DeInitDragDropEventResetState001
 * @tc.desc: Test DeInitDragDropEvent resets internal state
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, DeInitDragDropEventResetState001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    manager->dragState_ = GridItemDragState::DRAGGING;
    manager->fromIndex_ = 5;
    manager->scrolling_ = true;
    manager->dragOffset_ = OffsetF(10.0f, 20.0f);
    manager->realOffset_ = OffsetF(30.0f, 40.0f);

    manager->DeInitDragDropEvent();

    EXPECT_EQ(manager->dragState_, GridItemDragState::IDLE);
    EXPECT_EQ(manager->fromIndex_, -1);
    EXPECT_FALSE(manager->scrolling_);
    EXPECT_EQ(manager->dragOffset_, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(manager->realOffset_, OffsetF(0.0f, 0.0f));
}

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

    EXPECT_EQ(onMoveEventCnt, 1);
    EXPECT_EQ(onDropCnt, 1);
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

    EXPECT_EQ(onMoveEventCnt, 1);
    EXPECT_EQ(onDropCnt, 1);
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
    auto result = manager->CalculateFromNewPosition(0, 1, info);
    EXPECT_FALSE(result.has_value());
}

// ============================================================
// HasIrregularItemInRange
// ============================================================

/**
 * @tc.name: HasIrregularItemInRangeNullForEach001
 * @tc.desc: Test HasIrregularItemInRange with null forEach returns false
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, HasIrregularItemInRangeNullForEach001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<GridItemDragManager>(nullptr, nullptr);
    ASSERT_NE(manager, nullptr);
    EXPECT_FALSE(manager->HasIrregularItemInRange(0, 5));
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

/**
 * @tc.name: DragDropEventLifecycle001
 * @tc.desc: Test full lifecycle: Init -> DeInit resets state
 * @tc.type: FUNC
 */
HWTEST_F(GridItemDragManagerTestNg, DragDropEventLifecycle001, TestSize.Level1)
{
    auto manager = CreateDragManager();
    ASSERT_NE(manager, nullptr);
    manager->InitDragDropEvent();
    manager->dragState_ = GridItemDragState::DRAGGING;
    manager->fromIndex_ = 3;
    manager->scrolling_ = true;

    manager->DeInitDragDropEvent();

    EXPECT_EQ(manager->dragState_, GridItemDragState::IDLE);
    EXPECT_EQ(manager->fromIndex_, -1);
    EXPECT_FALSE(manager->scrolling_);
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

} // namespace OHOS::Ace::NG
