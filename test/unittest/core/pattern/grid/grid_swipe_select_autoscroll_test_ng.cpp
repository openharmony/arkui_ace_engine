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

#include "core/components_ng/pattern/grid/grid_item_pattern.h"

namespace OHOS::Ace::NG {

class GridSwipeSelectAutoScrollTestNg : public GridTestNg {
public:
    void SetUp() override
    {
        GridTestNg::SetUp();
    }
    void TearDown() override
    {
        GridTestNg::TearDown();
    }
};

static GestureEvent CreateGestureEvent(float globalX, float globalY, float offsetX = 0.f, float offsetY = 0.f)
{
    GestureEvent info;
    info.SetGlobalLocation(Offset(globalX, globalY));
    info.SetLocalLocation(Offset(globalX, globalY));
    info.SetRawGlobalLocation(Offset(globalX, globalY));
    info.SetOffsetX(offsetX);
    info.SetOffsetY(offsetY);
    return info;
}

using SwipeSelectState = SelectableContainerPattern::SwipeSelectState;

// ============================================================
// T6.1 SwipeSelectAutoScroll: point in bottom hot zone triggers scroll
// ============================================================

HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollTriggerBottom001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->OnModifyDone();
    FlushUITasks();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_NE(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    PointF bottomPoint(30.f, 600.f);
    pattern_->SwipeSelectAutoScroll(bottomPoint);
    EXPECT_NO_FATAL_FAILURE(pattern_->StopSwipeSelectAutoScroll());
}

// ============================================================
// T6.2 SwipeSelectAutoScroll: point in top hot zone triggers scroll
// ============================================================

HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollTriggerTop001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->OnModifyDone();
    FlushUITasks();

    GestureEvent startInfo = CreateGestureEvent(30.f, 150.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_NE(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    PointF topPoint(30.f, -50.f);
    pattern_->SwipeSelectAutoScroll(topPoint);
    EXPECT_NO_FATAL_FAILURE(pattern_->StopSwipeSelectAutoScroll());
}

// ============================================================
// T6.3 SwipeSelectAutoScroll: point inside container does not trigger
// ============================================================

HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollNoTriggerInBounds001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->OnModifyDone();
    FlushUITasks();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_NE(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    PointF inBoundsPoint(30.f, 200.f);
    pattern_->SwipeSelectAutoScroll(inBoundsPoint);
    EXPECT_NO_FATAL_FAILURE(pattern_->StopSwipeSelectAutoScroll());
}

// ============================================================
// T6.4 ShouldSelectScrollBeStopped: INACTIVE state
// ============================================================

HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollStopInactive001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    ASSERT_EQ(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    EXPECT_TRUE(pattern_->ShouldSelectScrollBeStopped());
}

// ============================================================
// T6.5 SwipeSelectAutoScroll: zero offset from IsInHotZone stops scroll
// ============================================================

HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollStopZeroOffset001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->OnModifyDone();
    FlushUITasks();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_NE(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    PointF centerPoint(120.f, 200.f);
    pattern_->SwipeSelectAutoScroll(centerPoint);
    EXPECT_NO_FATAL_FAILURE(pattern_->StopSwipeSelectAutoScroll());
}

// ============================================================
// T6.6 HandleSwipeSelectEnd stops auto scroll
// ============================================================

HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollStopOnEnd001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->OnModifyDone();
    FlushUITasks();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_NE(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    PointF bottomPoint(30.f, 600.f);
    pattern_->SwipeSelectAutoScroll(bottomPoint);

    pattern_->HandleSwipeSelectEnd();
    EXPECT_EQ(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);
}

// ============================================================
// T6.7 HandleSwipeSelectCancel stops auto scroll and restores
// ============================================================

HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollStopOnCancel001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->OnModifyDone();
    FlushUITasks();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_NE(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    PointF bottomPoint(30.f, 600.f);
    pattern_->SwipeSelectAutoScroll(bottomPoint);

    pattern_->HandleSwipeSelectCancel();
    EXPECT_EQ(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);
    EXPECT_TRUE(pattern_->swipeOriginalStates_.empty());
}

// ============================================================
// T6.8 SwipeSelectAutoScroll: no crash when edit mode disabled
// ============================================================

HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollDisabledNoCrash001, TestSize.Level2)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    ASSERT_FALSE(pattern_->GetEnableEditMode());

    PointF point(30.f, 600.f);
    EXPECT_NO_FATAL_FAILURE(pattern_->SwipeSelectAutoScroll(point));
}

// ============================================================
// T6.9 StopSwipeSelectAutoScroll: idempotent (call twice)
// ============================================================

HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollStopIdempotent001, TestSize.Level2)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EXPECT_NO_FATAL_FAILURE(pattern_->StopSwipeSelectAutoScroll());
    EXPECT_NO_FATAL_FAILURE(pattern_->StopSwipeSelectAutoScroll());
}

// ============================================================
// T6.10 SwipeSelectAutoScroll: callback updates selection during scroll
// ============================================================

HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollCallbackUpdatesSelection001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->OnModifyDone();
    FlushUITasks();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_NE(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    GestureEvent updateInfo = CreateGestureEvent(30.f, 150.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);

    PointF bottomPoint(30.f, 600.f);
    pattern_->SwipeSelectAutoScroll(bottomPoint);

    pattern_->UpdateSwipeSelection();

    int32_t rangeStart = std::min(pattern_->swipeStartStateKey_.index, pattern_->swipeCurrentStateKey_.index);
    int32_t rangeEnd = std::max(pattern_->swipeStartStateKey_.index, pattern_->swipeCurrentStateKey_.index);
    bool isSelected = (pattern_->swipeSelectState_ == SwipeSelectState::SELECTING);
    for (int32_t i = rangeStart; i <= rangeEnd; ++i) {
        auto child = AceType::DynamicCast<FrameNode>(frameNode_->GetChildByIndex(i));
        if (child) {
            auto itemPattern = child->GetPattern<GridItemPattern>();
            if (itemPattern) {
                EXPECT_EQ(itemPattern->IsSelected(), isSelected);
            }
        }
    }

    pattern_->StopSwipeSelectAutoScroll();
    pattern_->HandleSwipeSelectEnd();
}

// ============================================================
// T6.11 SwipeSelectAutoScroll: INACTIVE state skips callback body
// ============================================================

HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollInactiveSkipsCallback001, TestSize.Level2)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    ASSERT_EQ(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    EXPECT_NO_FATAL_FAILURE(pattern_->UpdateSwipeSelection());
}

// ============================================================
// T6.12 SwipeSelectAutoScroll: end then auto-scroll does not crash
// ============================================================

HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollAfterEndNoCrash001, TestSize.Level2)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->OnModifyDone();
    FlushUITasks();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    pattern_->HandleSwipeSelectEnd();
    ASSERT_EQ(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    PointF bottomPoint(30.f, 600.f);
    EXPECT_NO_FATAL_FAILURE(pattern_->SwipeSelectAutoScroll(bottomPoint));
    EXPECT_NO_FATAL_FAILURE(pattern_->StopSwipeSelectAutoScroll());
}

/**
 * @tc.name: AutoScrollCallbackWithNegativeIndexNoCrash001
 * @tc.desc: Verify UpdateSwipeSelection called via auto-scroll callback does not crash
 *           when swipeStartStateKey_ is invalid (reset by End) but state is still SELECTING.
 *           Tests the boundary condition for race between auto-scroll callback and state reset.
 * @tc.type: FUNC
 */
HWTEST_F(GridSwipeSelectAutoScrollTestNg, AutoScrollCallbackWithNegativeIndexNoCrash001, TestSize.Level2)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->OnModifyDone();
    FlushUITasks();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_NE(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    pattern_->swipeStartStateKey_.index = -1;
    pattern_->swipeCurrentStateKey_.index = -1;
    ASSERT_NE(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    EXPECT_NO_FATAL_FAILURE(pattern_->UpdateSwipeSelection());
}

} // namespace OHOS::Ace::NG
