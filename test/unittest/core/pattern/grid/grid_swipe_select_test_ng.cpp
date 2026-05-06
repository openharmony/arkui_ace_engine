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
#include "core/components_ng/pattern/grid/grid_model_ng.h"

namespace OHOS::Ace::NG {

class GridSwipeSelectTestNg : public GridTestNg {
public:
    void SetUp() override
    {
        GridTestNg::SetUp();
    }
    void TearDown() override
    {
        GridTestNg::TearDown();
    }

    void EnableSwipeSelect()
    {
        pattern_->enableEditMode_ = true;
        pattern_->multiSelectable_ = false;
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

static RefPtr<GridItemPattern> GetGridItemPattern(const RefPtr<FrameNode>& gridFrameNode, int32_t index)
{
    auto host = AceType::DynamicCast<FrameNode>(gridFrameNode->GetChildByIndex(index));
    CHECK_NULL_RETURN(host, nullptr);
    return host->GetPattern<GridItemPattern>();
}

static void SetItemSelected(const RefPtr<FrameNode>& gridFrameNode, int32_t index, bool selected)
{
    auto itemPattern = GetGridItemPattern(gridFrameNode, index);
    if (itemPattern) {
        itemPattern->MarkIsSelected(selected);
    }
}

static bool IsItemSelected(const RefPtr<FrameNode>& gridFrameNode, int32_t index)
{
    auto itemPattern = GetGridItemPattern(gridFrameNode, index);
    return itemPattern ? itemPattern->IsSelected() : false;
}

using SwipeSelectState = SelectableContainerPattern::SwipeSelectState;

static SelectableContainerPattern::SwipeSelectStateKey MakeStateKey(int32_t index)
{
    return { index, -1 };
}

// ============================================================
// 7.1 HandleSwipeSelectStart
// ============================================================

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectStartOnUnselectedItem001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent info = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(info);

    EXPECT_EQ(pattern_->swipeSelectState_, SwipeSelectState::SELECTING);
    EXPECT_EQ(pattern_->swipeStartStateKey_.index, 0);
    EXPECT_EQ(pattern_->swipeCurrentStateKey_.index, 0);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectStartOnSelectedItem001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();
    SetItemSelected(frameNode_, 0, true);

    GestureEvent info = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(info);

    EXPECT_EQ(pattern_->swipeSelectState_, SwipeSelectState::DESELECTING);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectStartRecordIndex001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent info = CreateGestureEvent(30.f, 150.f);
    pattern_->HandleSwipeSelectStart(info);

    EXPECT_EQ(pattern_->swipeStartStateKey_.index, pattern_->swipeCurrentStateKey_.index);
    EXPECT_GE(pattern_->swipeStartStateKey_.index, 0);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectStartRecordOriginalState001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent info = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(info);

    EXPECT_FALSE(pattern_->swipeOriginalStates_.empty());
    EXPECT_EQ(pattern_->swipeOriginalStates_.count(pattern_->swipeStartStateKey_), 1);
    EXPECT_FALSE(pattern_->swipeOriginalStates_[pattern_->swipeStartStateKey_]);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectStartNoItem001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent info = CreateGestureEvent(30.f, 500.f);
    pattern_->HandleSwipeSelectStart(info);

    EXPECT_EQ(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);
    EXPECT_EQ(pattern_->swipeStartStateKey_.index, -1);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectStartRecordSelectedOriginal001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();
    SetItemSelected(frameNode_, 0, true);

    GestureEvent info = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(info);

    EXPECT_EQ(pattern_->swipeOriginalStates_[MakeStateKey(0)], true);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectStartDisabled001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    ASSERT_FALSE(pattern_->GetEnableEditMode());
    EXPECT_EQ(pattern_->swipeSelectPanEvent_, nullptr);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectStartMultiSelectableBlocks001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    pattern_->enableEditMode_ = true;
    pattern_->multiSelectable_ = true;

    GestureEvent info = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(info);

    EXPECT_EQ(pattern_->swipeSelectState_, SwipeSelectState::SELECTING);
}

// ============================================================
// 7.2 HandleSwipeSelectUpdate
// ============================================================

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectUpdateForward001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_EQ(pattern_->swipeSelectState_, SwipeSelectState::SELECTING);

    GestureEvent updateInfo = CreateGestureEvent(150.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);

    EXPECT_TRUE(IsItemSelected(frameNode_, 0));
    EXPECT_TRUE(IsItemSelected(frameNode_, 1));
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectUpdateForward002, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);

    GestureEvent updateInfo1 = CreateGestureEvent(150.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo1);

    GestureEvent updateInfo2 = CreateGestureEvent(30.f, 150.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo2);

    EXPECT_TRUE(IsItemSelected(frameNode_, 0));
    EXPECT_TRUE(IsItemSelected(frameNode_, 1));
    EXPECT_TRUE(IsItemSelected(frameNode_, 2));
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectUpdateDeselecting001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();
    SetItemSelected(frameNode_, 0, true);
    SetItemSelected(frameNode_, 1, true);

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_EQ(pattern_->swipeSelectState_, SwipeSelectState::DESELECTING);

    GestureEvent updateInfo = CreateGestureEvent(150.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);

    EXPECT_FALSE(IsItemSelected(frameNode_, 0));
    EXPECT_FALSE(IsItemSelected(frameNode_, 1));
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectUpdateSwipeBackRestore001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);

    GestureEvent updateInfo1 = CreateGestureEvent(150.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo1);
    ASSERT_TRUE(IsItemSelected(frameNode_, 0));
    ASSERT_TRUE(IsItemSelected(frameNode_, 1));

    GestureEvent updateInfo2 = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo2);

    EXPECT_TRUE(IsItemSelected(frameNode_, 0));
    EXPECT_FALSE(IsItemSelected(frameNode_, 1));
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectUpdateInactive001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();
    ASSERT_EQ(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    GestureEvent updateInfo = CreateGestureEvent(150.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);

    EXPECT_EQ(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectUpdateSameIndex001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_EQ(pattern_->swipeCurrentStateKey_.index, pattern_->swipeStartStateKey_.index);

    GestureEvent updateInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);

    EXPECT_EQ(pattern_->swipeCurrentStateKey_.index, pattern_->swipeStartStateKey_.index);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectUpdateNewOriginalState001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();
    SetItemSelected(frameNode_, 1, true);

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_EQ(pattern_->swipeOriginalStates_.count(MakeStateKey(0)), 1);

    GestureEvent updateInfo = CreateGestureEvent(150.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);

    EXPECT_EQ(pattern_->swipeOriginalStates_.count(MakeStateKey(1)), 1);
    EXPECT_TRUE(pattern_->swipeOriginalStates_[MakeStateKey(1)]);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectUpdateBackward001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 250.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_EQ(pattern_->swipeSelectState_, SwipeSelectState::SELECTING);

    GestureEvent updateInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);

    int32_t startIdx = pattern_->swipeStartStateKey_.index;
    int32_t curIdx = pattern_->swipeCurrentStateKey_.index;
    int32_t rangeStart = std::min(startIdx, curIdx);
    int32_t rangeEnd = std::max(startIdx, curIdx);
    for (int32_t i = rangeStart; i <= rangeEnd; ++i) {
        EXPECT_TRUE(IsItemSelected(frameNode_, i)) << "item " << i << " should be selected";
    }
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectUpdateSwipeBackRestore002, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(8);
    CreateDone();

    EnableSwipeSelect();
    SetItemSelected(frameNode_, 2, true);
    SetItemSelected(frameNode_, 3, true);

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_EQ(pattern_->swipeSelectState_, SwipeSelectState::SELECTING);

    GestureEvent updateInfo1 = CreateGestureEvent(30.f, 250.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo1);

    GestureEvent updateInfo2 = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo2);

    EXPECT_TRUE(IsItemSelected(frameNode_, 0));
    EXPECT_FALSE(IsItemSelected(frameNode_, 1));
    EXPECT_TRUE(IsItemSelected(frameNode_, 2));
    EXPECT_TRUE(IsItemSelected(frameNode_, 3));
}

// ============================================================
// 7.3 HandleSwipeSelectEnd/Cancel
// ============================================================

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectEnd001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_NE(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);

    pattern_->HandleSwipeSelectEnd();

    EXPECT_EQ(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectEnd002, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_FALSE(pattern_->swipeOriginalStates_.empty());

    pattern_->HandleSwipeSelectEnd();

    EXPECT_TRUE(pattern_->swipeOriginalStates_.empty());
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectEnd003, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);

    pattern_->HandleSwipeSelectEnd();

    EXPECT_EQ(pattern_->swipeStartStateKey_.index, -1);
    EXPECT_EQ(pattern_->swipeCurrentStateKey_.index, -1);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectEndKeepsSelection001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);

    GestureEvent updateInfo = CreateGestureEvent(150.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);
    ASSERT_TRUE(IsItemSelected(frameNode_, 0));
    ASSERT_TRUE(IsItemSelected(frameNode_, 1));

    pattern_->HandleSwipeSelectEnd();

    EXPECT_TRUE(IsItemSelected(frameNode_, 0));
    EXPECT_TRUE(IsItemSelected(frameNode_, 1));
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectCancel001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);

    GestureEvent updateInfo = CreateGestureEvent(150.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);
    ASSERT_TRUE(IsItemSelected(frameNode_, 0));
    ASSERT_TRUE(IsItemSelected(frameNode_, 1));

    pattern_->HandleSwipeSelectCancel();

    EXPECT_FALSE(IsItemSelected(frameNode_, 0));
    EXPECT_FALSE(IsItemSelected(frameNode_, 1));
    EXPECT_EQ(pattern_->swipeSelectState_, SwipeSelectState::INACTIVE);
    EXPECT_EQ(pattern_->swipeStartStateKey_.index, -1);
    EXPECT_EQ(pattern_->swipeCurrentStateKey_.index, -1);
}

HWTEST_F(GridSwipeSelectTestNg, SwipeSelectCancelRestoreOriginal001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();
    SetItemSelected(frameNode_, 0, true);
    SetItemSelected(frameNode_, 1, false);

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_EQ(pattern_->swipeSelectState_, SwipeSelectState::DESELECTING);

    GestureEvent updateInfo = CreateGestureEvent(150.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);
    ASSERT_FALSE(IsItemSelected(frameNode_, 0));
    ASSERT_FALSE(IsItemSelected(frameNode_, 1));

    pattern_->HandleSwipeSelectCancel();

    EXPECT_TRUE(IsItemSelected(frameNode_, 0));
    EXPECT_FALSE(IsItemSelected(frameNode_, 1));
}

// ============================================================
// 7.4 UpdateSwipeSelection (range tracking)
// ============================================================

HWTEST_F(GridSwipeSelectTestNg, UpdateSwipeSelectionRange001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_EQ(pattern_->swipeStartStateKey_.index, 0);

    GestureEvent updateInfo = CreateGestureEvent(30.f, 250.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);

    int32_t rangeStart = std::min(pattern_->swipeStartStateKey_.index, pattern_->swipeCurrentStateKey_.index);
    int32_t rangeEnd = std::max(pattern_->swipeStartStateKey_.index, pattern_->swipeCurrentStateKey_.index);
    for (int32_t i = rangeStart; i <= rangeEnd; ++i) {
        EXPECT_TRUE(IsItemSelected(frameNode_, i));
    }
}

HWTEST_F(GridSwipeSelectTestNg, UpdateSwipeSelectionOutOfRange001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(8);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);

    GestureEvent updateInfo1 = CreateGestureEvent(30.f, 250.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo1);

    GestureEvent updateInfo2 = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo2);

    EXPECT_TRUE(IsItemSelected(frameNode_, 0));
    for (int32_t i = 1; i <= 4; ++i) {
        EXPECT_FALSE(IsItemSelected(frameNode_, i)) << "item " << i << " should be restored";
    }
}

HWTEST_F(GridSwipeSelectTestNg, UpdateSwipeSelectionDeselecting001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();
    SetItemSelected(frameNode_, 0, true);
    SetItemSelected(frameNode_, 1, true);

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_EQ(pattern_->swipeSelectState_, SwipeSelectState::DESELECTING);

    GestureEvent updateInfo = CreateGestureEvent(150.f, 30.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);

    EXPECT_FALSE(IsItemSelected(frameNode_, 0));
    EXPECT_FALSE(IsItemSelected(frameNode_, 1));
}

HWTEST_F(GridSwipeSelectTestNg, UpdateSwipeSelectionSingleItem001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_EQ(pattern_->swipeStartStateKey_.index, 0);
    ASSERT_EQ(pattern_->swipeStartStateKey_.index, pattern_->swipeCurrentStateKey_.index);

    EXPECT_TRUE(IsItemSelected(frameNode_, 0));
}

HWTEST_F(GridSwipeSelectTestNg, UpdateSwipeSelectionSelecting001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EnableSwipeSelect();

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_EQ(pattern_->swipeSelectState_, SwipeSelectState::SELECTING);

    GestureEvent updateInfo = CreateGestureEvent(30.f, 250.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);

    int32_t rangeStart = std::min(pattern_->swipeStartStateKey_.index, pattern_->swipeCurrentStateKey_.index);
    int32_t rangeEnd = std::max(pattern_->swipeStartStateKey_.index, pattern_->swipeCurrentStateKey_.index);
    for (int32_t i = rangeStart; i <= rangeEnd; ++i) {
        EXPECT_TRUE(IsItemSelected(frameNode_, i)) << "SELECTING: item " << i << " should be selected";
    }
}

HWTEST_F(GridSwipeSelectTestNg, UpdateSwipeSelectionRecordNew001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(8);
    CreateDone();

    EnableSwipeSelect();
    SetItemSelected(frameNode_, 3, true);
    SetItemSelected(frameNode_, 4, true);

    GestureEvent startInfo = CreateGestureEvent(30.f, 30.f);
    pattern_->HandleSwipeSelectStart(startInfo);
    ASSERT_EQ(pattern_->swipeOriginalStates_.count(MakeStateKey(0)), 1);
    ASSERT_FALSE(pattern_->swipeOriginalStates_[MakeStateKey(0)]);

    GestureEvent updateInfo = CreateGestureEvent(30.f, 350.f);
    pattern_->HandleSwipeSelectUpdate(updateInfo);

    EXPECT_EQ(pattern_->swipeOriginalStates_.count(MakeStateKey(3)), 1);
    EXPECT_TRUE(pattern_->swipeOriginalStates_[MakeStateKey(3)]);
    EXPECT_EQ(pattern_->swipeOriginalStates_.count(MakeStateKey(4)), 1);
    EXPECT_TRUE(pattern_->swipeOriginalStates_[MakeStateKey(4)]);
}

// ============================================================
// 7.5 Grid subclass override
// ============================================================

HWTEST_F(GridSwipeSelectTestNg, GridGetItemAtPositionValid001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    int32_t index = pattern_->GetItemAtPosition(30.f, 30.f);
    EXPECT_EQ(index, 0);

    index = pattern_->GetItemAtPosition(150.f, 30.f);
    EXPECT_EQ(index, 1);

    index = pattern_->GetItemAtPosition(30.f, 150.f);
    EXPECT_EQ(index, 2);
}

HWTEST_F(GridSwipeSelectTestNg, GridGetItemAtPositionEmpty001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    int32_t index = pattern_->GetItemAtPosition(30.f, 500.f);
    EXPECT_EQ(index, -1);

    index = pattern_->GetItemAtPosition(500.f, 30.f);
    EXPECT_EQ(index, -1);
}

HWTEST_F(GridSwipeSelectTestNg, GridGetItemAtPositionMultiColumn001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(12);
    CreateDone();

    EXPECT_EQ(pattern_->GetItemAtPosition(30.f, 30.f), 0);
    EXPECT_EQ(pattern_->GetItemAtPosition(90.f, 30.f), 1);
    EXPECT_EQ(pattern_->GetItemAtPosition(150.f, 30.f), 2);
    EXPECT_EQ(pattern_->GetItemAtPosition(210.f, 30.f), 3);
    EXPECT_EQ(pattern_->GetItemAtPosition(30.f, 150.f), 4);
}

HWTEST_F(GridSwipeSelectTestNg, GridMarkSwipeItemSelected001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    ASSERT_FALSE(IsItemSelected(frameNode_, 0));

    pattern_->MarkSwipeItemSelected(0, true);
    EXPECT_TRUE(IsItemSelected(frameNode_, 0));
}

HWTEST_F(GridSwipeSelectTestNg, GridMarkSwipeItemDeselected001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    SetItemSelected(frameNode_, 0, true);
    ASSERT_TRUE(IsItemSelected(frameNode_, 0));

    pattern_->MarkSwipeItemSelected(0, false);
    EXPECT_FALSE(IsItemSelected(frameNode_, 0));
}

HWTEST_F(GridSwipeSelectTestNg, GridMarkSwipeItemInvalidIndex001, TestSize.Level2)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EXPECT_NO_FATAL_FAILURE(pattern_->MarkSwipeItemSelected(-1, true));
    EXPECT_NO_FATAL_FAILURE(pattern_->MarkSwipeItemSelected(999, true));
}

} // namespace OHOS::Ace::NG
