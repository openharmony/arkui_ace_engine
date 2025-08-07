/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "grid_test_ng.h"
#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/manager/focus/focus_manager.h"
#include "core/components_ng/pattern/grid/grid_focus.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class GridFocusTestNg : public GridTestNg {
public:
};

/**
 * @tc.name: GetFocusNodeIndex001
 * @tc.desc: Test GridFocus GetFocusNodeIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, GetFocusNodeIndex001, TestSize.Level1)
{
    GridPattern grid;
    GridLayoutInfo info;
    GridFocus gridFocus(grid, info);
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(shallowBuilder, GridItemStyle::PLAIN);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    gridItemPattern->frameNode_ = frameNode;
    auto gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->propMainIndex_ = 0;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    RefPtr<FocusHub> focusNode = AceType::MakeRefPtr<FocusHub>(node);
    auto result = gridFocus.GetFocusNodeIndex(focusNode);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: GetFocusNodeIndex002
 * @tc.desc: Test GridFocus GetFocusNodeIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, GetFocusNodeIndex002, TestSize.Level1)
{
    GridPattern grid;
    GridLayoutInfo info;
    info.gridMatrix_[0] = { { 1, 2 }, { 3, 4 } };
    info.gridMatrix_[1] = { { 5, 6 }, { 7, 8 } };
    info.firstRepeatCount_ = 4;
    info.childrenCount_ = 1;
    GridFocus gridFocus(grid, info);
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(shallowBuilder, GridItemStyle::PLAIN);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    gridItemPattern->frameNode_ = frameNode;
    auto gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->propMainIndex_ = 2;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    RefPtr<FocusHub> focusNode = AceType::MakeRefPtr<FocusHub>(node);
    auto result = gridFocus.GetFocusNodeIndex(focusNode);
    EXPECT_EQ(result, 3);
}

/**
 * @tc.name: GetFocusNodeIndex003
 * @tc.desc: Test GridFocus GetFocusNodeIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, GetFocusNodeIndex003, TestSize.Level1)
{
    GridPattern grid;
    GridLayoutInfo info;
    info.gridMatrix_[0] = { { 1, 2 }, { 3, 4 } };
    info.gridMatrix_[1] = { { 5, 6 }, { 7, 8 } };
    GridFocus gridFocus(grid, info);
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(shallowBuilder, GridItemStyle::PLAIN);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    gridItemPattern->frameNode_ = frameNode;
    auto gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->propMainIndex_ = 0;
    gridItemLayoutProperty->propCrossIndex_ = 2;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    RefPtr<FocusHub> focusNode = AceType::MakeRefPtr<FocusHub>(node);
    auto result = gridFocus.GetFocusNodeIndex(focusNode);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: GetFocusNodeIndex004
 * @tc.desc: Test GridFocus GetFocusNodeIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, GetFocusNodeIndex004, TestSize.Level1)
{
    GridPattern grid;
    GridLayoutInfo info;
    info.gridMatrix_[0] = { { 1, 2 }, { 3, 4 } };
    info.gridMatrix_[1] = { { 5, 6 }, { 7, 8 } };
    info.firstRepeatCount_ = 0;
    info.childrenCount_ = 2;
    GridFocus gridFocus(grid, info);
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(shallowBuilder, GridItemStyle::PLAIN);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    gridItemPattern->frameNode_ = frameNode;
    auto gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->propMainIndex_ = 1;
    gridItemLayoutProperty->propCrossIndex_ = 2;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    RefPtr<FocusHub> focusNode = AceType::MakeRefPtr<FocusHub>(node);
    auto result = gridFocus.GetFocusNodeIndex(focusNode);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: ProcessFocusEvent001
 * @tc.desc: Test GridFocus ProcessFocusEvent
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, ProcessFocusEvent001, TestSize.Level1)
{
    GridPattern grid;
    GridLayoutInfo info;
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(shallowBuilder, GridItemStyle::PLAIN);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    gridItemPattern->frameNode_ = frameNode;
    grid.frameNode_ = frameNode;
    RefPtr<FocusHub> focusNode = AceType::MakeRefPtr<FocusHub>(node);
    focusNode->currentFocus_ = true;
    frameNode->focusHub_ = focusNode;
    KeyEvent event;
    GridFocus gridFocus(grid, info);
    gridFocus.needTriggerFocus_ = true;
    gridFocus.triggerFocus_ = true;
    gridFocus.ProcessFocusEvent(event, true);
    EXPECT_FALSE(gridFocus.triggerFocus_);
}

/**
 * @tc.name: ProcessFocusEvent002
 * @tc.desc: Test GridFocus ProcessFocusEvent
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, ProcessFocusEvent002, TestSize.Level1)
{
    GridPattern grid;
    GridLayoutInfo info;
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(shallowBuilder, GridItemStyle::PLAIN);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    gridItemPattern->frameNode_ = frameNode;
    grid.frameNode_ = frameNode;
    RefPtr<FocusHub> focusNode = AceType::MakeRefPtr<FocusHub>(node);
    focusNode->currentFocus_ = true;
    frameNode->focusHub_ = focusNode;
    KeyEvent event;
    GridFocus gridFocus(grid, info);
    gridFocus.needTriggerFocus_ = true;
    gridFocus.focusIndex_ = std::nullopt;
    gridFocus.ProcessFocusEvent(event, true);
    EXPECT_FALSE(gridFocus.needTriggerFocus_);
}

/**
 * @tc.name: ProcessFocusEvent003
 * @tc.desc: Test GridFocus ProcessFocusEvent
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, ProcessFocusEvent003, TestSize.Level1)
{
    GridPattern grid;
    GridLayoutInfo info;
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(shallowBuilder, GridItemStyle::PLAIN);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    gridItemPattern->frameNode_ = frameNode;
    grid.frameNode_ = frameNode;
    RefPtr<FocusHub> focusNode = AceType::MakeRefPtr<FocusHub>(node);
    focusNode->currentFocus_ = true;
    frameNode->focusHub_ = focusNode;
    KeyEvent event;
    GridFocus gridFocus(grid, info);
    gridFocus.needTriggerFocus_ = true;
    gridFocus.focusIndex_ = 2;
    gridFocus.ProcessFocusEvent(event, true);
    EXPECT_TRUE(gridFocus.triggerFocus_);
}

/**
 * @tc.name: ScrollToLastFocusIndex001
 * @tc.desc: Test GridFocus ScrollToLastFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, ScrollToLastFocusIndex001, TestSize.Level1)
{
    GridPattern grid;
    GridLayoutInfo info;
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(shallowBuilder, GridItemStyle::PLAIN);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridItemPattern);
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    RefPtr<FocusManager> focusManager = AceType::MakeRefPtr<FocusManager>(pipe);
    focusManager->isFocusActive_ = true;
    pipe->focusManager_ = focusManager;
    frameNode->context_ = AceType::RawPtr(pipe);
    WeakPtr<FrameNode> node = frameNode;
    gridItemPattern->frameNode_ = frameNode;
    grid.frameNode_ = frameNode;
    RefPtr<FocusHub> focusNode = AceType::MakeRefPtr<FocusHub>(node);
    focusNode->currentFocus_ = true;
    frameNode->focusHub_ = focusNode;
    GridFocus gridFocus(grid, info);
    gridFocus.needTriggerFocus_ = true;
    gridFocus.focusIndex_ = 2;
    auto result = gridFocus.ScrollToLastFocusIndex(KeyCode::KEY_DPAD_UP);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScrollToLastFocusIndex002
 * @tc.desc: Test GridFocus ScrollToLastFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, ScrollToLastFocusIndex002, TestSize.Level1)
{
    GridPattern grid;
    grid.isConfigScrollable_ = true;
    GridLayoutInfo info;
    info.defCachedCount_ = 0;
    info.crossCount_ = 1;
    info.startIndex_ = 3;
    info.endIndex_ = 1;
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(shallowBuilder, GridItemStyle::PLAIN);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridItemPattern);
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    RefPtr<FocusManager> focusManager = AceType::MakeRefPtr<FocusManager>(pipe);
    focusManager->isFocusActive_ = true;
    pipe->focusManager_ = focusManager;
    frameNode->context_ = AceType::RawPtr(pipe);
    WeakPtr<FrameNode> node = frameNode;
    gridItemPattern->frameNode_ = frameNode;
    grid.frameNode_ = frameNode;
    RefPtr<FocusHub> focusNode = AceType::MakeRefPtr<FocusHub>(node);
    focusNode->currentFocus_ = true;
    frameNode->focusHub_ = focusNode;
    auto gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    GridFocus gridFocus(grid, info);
    gridFocus.needTriggerFocus_ = true;
    gridFocus.focusIndex_ = 2;
    gridFocus.ScrollToLastFocusIndex(KeyCode::KEY_DPAD_UP);
    EXPECT_EQ(grid.scrollSource_, 3);
}

/**
 * @tc.name: ScrollToLastFocusIndex003
 * @tc.desc: Test GridFocus ScrollToLastFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, ScrollToLastFocusIndex003, TestSize.Level1)
{
    GridPattern grid;
    grid.isConfigScrollable_ = true;
    GridLayoutInfo info;
    info.defCachedCount_ = 0;
    info.crossCount_ = 3;
    info.startIndex_ = 0;
    info.endIndex_ = 1;
    info.firstRepeatCount_ = 6;
    info.childrenCount_ = 1;
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(shallowBuilder, GridItemStyle::PLAIN);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridItemPattern);
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    RefPtr<FocusManager> focusManager = AceType::MakeRefPtr<FocusManager>(pipe);
    focusManager->isFocusActive_ = true;
    pipe->focusManager_ = focusManager;
    frameNode->context_ = AceType::RawPtr(pipe);
    WeakPtr<FrameNode> node = frameNode;
    gridItemPattern->frameNode_ = frameNode;
    grid.frameNode_ = frameNode;
    RefPtr<FocusHub> focusNode = AceType::MakeRefPtr<FocusHub>(node);
    focusNode->currentFocus_ = true;
    frameNode->focusHub_ = focusNode;
    auto gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    GridFocus gridFocus(grid, info);
    gridFocus.needTriggerFocus_ = true;
    gridFocus.focusIndex_ = 2;
    gridFocus.ScrollToLastFocusIndex(KeyCode::KEY_DPAD_DOWN);
    EXPECT_EQ(grid.scrollSource_, 3);
}

/**
 * @tc.name: ScrollToLastFocusIndex004
 * @tc.desc: Test GridFocus ScrollToLastFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, ScrollToLastFocusIndex004, TestSize.Level1)
{
    GridPattern grid;
    grid.isConfigScrollable_ = true;
    GridLayoutInfo info;
    info.defCachedCount_ = 0;
    info.crossCount_ = 3;
    info.startIndex_ = 3;
    info.endIndex_ = 1;
    info.firstRepeatCount_ = 6;
    info.childrenCount_ = 1;
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(shallowBuilder, GridItemStyle::PLAIN);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridItemPattern);
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    RefPtr<FocusManager> focusManager = AceType::MakeRefPtr<FocusManager>(pipe);
    focusManager->isFocusActive_ = true;
    pipe->focusManager_ = focusManager;
    frameNode->context_ = AceType::RawPtr(pipe);
    WeakPtr<FrameNode> node = frameNode;
    gridItemPattern->frameNode_ = frameNode;
    grid.frameNode_ = frameNode;
    RefPtr<FocusHub> focusNode = AceType::MakeRefPtr<FocusHub>(node);
    focusNode->currentFocus_ = true;
    frameNode->focusHub_ = focusNode;
    auto gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    GridFocus gridFocus(grid, info);
    gridFocus.needTriggerFocus_ = true;
    gridFocus.focusIndex_ = 2;
    gridFocus.ScrollToLastFocusIndex(KeyCode::KEY_DPAD_UP);
    EXPECT_EQ(grid.scrollSource_, 3);
}

/**
 * @tc.name: ScrollToLastFocusIndex005
 * @tc.desc: Test GridFocus ScrollToLastFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, ScrollToLastFocusIndex005, TestSize.Level1)
{
    GridPattern grid;
    grid.isConfigScrollable_ = true;
    GridLayoutInfo info;
    info.defCachedCount_ = 0;
    info.crossCount_ = 3;
    info.startIndex_ = 3;
    info.endIndex_ = 1;
    info.firstRepeatCount_ = 6;
    info.childrenCount_ = 1;
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(shallowBuilder, GridItemStyle::PLAIN);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridItemPattern);
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    RefPtr<FocusManager> focusManager = AceType::MakeRefPtr<FocusManager>(pipe);
    focusManager->isFocusActive_ = true;
    pipe->focusManager_ = focusManager;
    frameNode->context_ = AceType::RawPtr(pipe);
    WeakPtr<FrameNode> node = frameNode;
    gridItemPattern->frameNode_ = frameNode;
    grid.frameNode_ = frameNode;
    RefPtr<FocusHub> focusNode = AceType::MakeRefPtr<FocusHub>(node);
    focusNode->currentFocus_ = true;
    frameNode->focusHub_ = focusNode;
    auto gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    GridFocus gridFocus(grid, info);
    gridFocus.needTriggerFocus_ = true;
    gridFocus.focusIndex_ = 2;
    gridFocus.ScrollToLastFocusIndex(KeyCode::KEY_DPAD_LEFT);
    EXPECT_EQ(grid.scrollSource_, 3);
}

/**
 * @tc.name: GetNextFocusSimplified
 * @tc.desc: Test GridFocus ScrollToLastFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, GetNextFocusSimplified, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    WeakPtr<FrameNode> weakFrameNode = std::move(frameNode_);
    auto current = AceType::MakeRefPtr<FocusHub>(weakFrameNode);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    frameNode_->context_ = AceType::RawPtr(context);
    auto grid = AceType::RawPtr(pattern_);

    /**
     * @tc.steps: step2. Set GridLayoutInfo
     * and set the GridFocus
     */
    GridLayoutInfo info = { .defCachedCount_ = 0,
        .crossCount_ = 3,
        .startIndex_ = 3,
        .endIndex_ = 1,
        .firstRepeatCount_ = 6,
        .childrenCount_ = 1 };
    GridFocus gridFocus(*grid, info);
    gridFocus.needTriggerFocus_ = true;
    gridFocus.focusIndex_ = 2;

    /**
     * @tc.steps: step3. Set step is not equal to TAB or SHIFT_TAB
     * @tc.expected: The result of calling the function return nullptr
     */
    auto result = gridFocus.GetNextFocusSimplified(FocusStep::NONE, current);
    frameNode_->context_ = nullptr;
    EXPECT_EQ(result.Upgrade(), nullptr);
}

/**
 * @tc.name: GetNextFocusNode
 * @tc.desc: Test GridFocus GetNextFocusNode
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, GetNextFocusNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    frameNode_->layoutProperty_ = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode_->layoutProperty_->layoutDirection_ = TextDirection::RTL;
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(AceType::MakeRefPtr<ShallowBuilder>(nullptr), GridItemStyle::PLAIN);
    gridItemPattern->irregularItemInfo_ = { 2, 1, 1, 2, 1, 2, 2, 3 };
    auto frameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, 2, gridItemPattern);
    auto gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->UpdateMainIndex(-2);
    gridItemLayoutProperty->UpdateCrossIndex(-3);
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    WeakPtr<FrameNode> weakFrameNode = std::move(frameNode);
    auto current = AceType::MakeRefPtr<FocusHub>(weakFrameNode);
    WeakPtr<FocusHub> currentFocusNode = std::move(current);
    gridItemPattern->frameNode_ = frameNode;
    auto grid = AceType::RawPtr(pattern_);

    /**
     * @tc.steps: step2. Set GridLayoutInfo and GridFocus
     * and set GetCurrentFocusInfo to return false
     */
    GridLayoutInfo info = { .defCachedCount_ = 0,
        .crossCount_ = 3,
        .startIndex_ = 3,
        .endIndex_ = 1,
        .firstRepeatCount_ = 6,
        .childrenCount_ = 1 };
    GridFocus gridFocus(*grid, info);

    /**
     * @tc.steps: step3. Calling the GetNextFocusNode function
     * @tc.expected: The result of calling the function return nullptr
     */
    auto result = gridFocus.GetNextFocusNode(FocusStep::LEFT, currentFocusNode, true);
    EXPECT_EQ(result.Upgrade(), nullptr);
}

/**
 * @tc.name: GetCurrentFocusInfo_001
 * @tc.desc: Test GridFocus GetCurrentFocusInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, GetCurrentFocusInfo_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    frameNode_->layoutProperty_ = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode_->layoutProperty_->layoutDirection_ = TextDirection::RTL;
    auto grid = AceType::RawPtr(pattern_);
    GridLayoutInfo info = { .defCachedCount_ = 0,
        .crossCount_ = 3,
        .startIndex_ = 3,
        .endIndex_ = 1,
        .firstRepeatCount_ = 6,
        .childrenCount_ = 1 };

    GridFocus gridFocus(*grid, info);
    gridFocus.curFocusIndexInfo_ = { 1, 2, 1, 2, 1, 2, 2, 3 };
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(AceType::MakeRefPtr<ShallowBuilder>(nullptr), GridItemStyle::PLAIN);
    gridItemPattern->irregularItemInfo_ = { 2, 1, 1, 2, 1, 2, 2, 3 };
    auto frameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, 2, gridItemPattern);
    auto gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();

    /**
     * @tc.steps: step2. Set curMainIndex of gridItemLayoutProperty to be greater than 0
     * and set crossIndex of gridItemLayoutProperty to be less than 0
     */
    gridItemLayoutProperty->UpdateMainIndex(2);
    gridItemLayoutProperty->UpdateCrossIndex(-3);
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    WeakPtr<FrameNode> weakFrameNode = std::move(frameNode);
    auto current = AceType::MakeRefPtr<FocusHub>(weakFrameNode);
    WeakPtr<FocusHub> currentFocusNode = std::move(current);
    gridItemPattern->frameNode_ = frameNode;

    /**
     * @tc.steps: step3. set the step to NONE
     * @tc.expected: The result of calling the function return false
     */
    auto result = gridFocus.GetCurrentFocusInfo(FocusStep::NONE, currentFocusNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetCurrentFocusInfo_002
 * @tc.desc: Test GridFocus GetCurrentFocusInfo
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, GetCurrentFocusInfo_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    frameNode_->layoutProperty_ = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode_->layoutProperty_->layoutDirection_ = TextDirection::RTL;
    auto grid = AceType::RawPtr(pattern_);
    GridLayoutInfo info = {
        .crossCount_ = 3, .startIndex_ = 3, .endIndex_ = 1, .firstRepeatCount_ = 6, .childrenCount_ = 1
    };
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(AceType::MakeRefPtr<ShallowBuilder>(nullptr), GridItemStyle::PLAIN);
    gridItemPattern->irregularItemInfo_ = { 2, 1, 1, 2, 1, 2, 2, 3 };
    auto frameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, 2, gridItemPattern);
    auto gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();

    /**
     * @tc.steps: step2. Set curMainIndex and crossIndex of gridItemLayoutProperty to be greater than 0
     * and set curMainIndex not found in grid matrix
     */
    gridItemLayoutProperty->UpdateMainIndex(2);
    gridItemLayoutProperty->UpdateCrossIndex(3);
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    WeakPtr<FrameNode> weakFrameNode = std::move(frameNode);
    auto current = AceType::MakeRefPtr<FocusHub>(weakFrameNode);
    WeakPtr<FocusHub> currentFocusNode = std::move(current);
    gridItemPattern->frameNode_ = frameNode;
    info.gridMatrix_[1] = { { 1, 2 }, { 2, 3 } };
    GridFocus gridFocus(*grid, info);
    gridFocus.curFocusIndexInfo_ = { 1, 2, 1, 2, 1, 2, 2, 3 };

    /**
     * @tc.steps: step3. set the step to RIGHT
     * @tc.expected: The result of calling the function return false
     */
    auto result = gridFocus.GetCurrentFocusInfo(FocusStep::RIGHT, currentFocusNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleFocusSteps
 * @tc.desc: Test GridFocus HandleFocusSteps
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, HandleFocusSteps, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();
    
    GridLayoutInfo info = {
        .defCachedCount_ = 0, .crossCount_ = 3, .startIndex_ = 3, .endIndex_ = 1, .firstRepeatCount_ = 6
    };
    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(AceType::MakeRefPtr<ShallowBuilder>(nullptr), GridItemStyle::PLAIN);
    gridItemPattern->irregularItemInfo_ = { 2, 1, 1, 2, 1, 2, 2, 3 };
    auto frameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, 2, gridItemPattern);
    auto gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->UpdateMainIndex(-2);
    gridItemLayoutProperty->UpdateCrossIndex(-3);
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    WeakPtr<FrameNode> weakFrameNode = std::move(frameNode);
    auto current = AceType::MakeRefPtr<FocusHub>(weakFrameNode);
    WeakPtr<FocusHub> currentFocusNode = std::move(current);
    gridItemPattern->frameNode_ = frameNode;

    /**
     * @tc.steps: step2. Set GetFocusWrapMode to WRAP_WITH_ARROW
     * and axis_ of GridLayoutInfo to FREE and mainSpan of curFocusIndexInfo_ to be greater than 0
     */
    auto gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    gridLayoutProperty->layoutDirection_ = TextDirection::RTL;
    gridLayoutProperty->UpdateFocusWrapMode(FocusWrapMode::WRAP_WITH_ARROW);
    frameNode_->layoutProperty_ = gridLayoutProperty;
    auto grid = AceType::RawPtr(pattern_);
    info.axis_ = Axis::FREE;
    GridFocus gridFocus(*grid, info);
    gridFocus.curFocusIndexInfo_ = { 1, 2, 2, 1, 1, 2, 2, 3 };

    /**
     * @tc.steps: step3. set the step to LEFT and focusSteps
     * @tc.expected: The result of calling the function return currentFocusNode
     */
    auto focusSteps = std::make_pair(FocusStep::RIGHT, FocusStep::RIGHT_END);
    auto result = gridFocus.HandleFocusSteps(FocusStep::LEFT, currentFocusNode, focusSteps);
    EXPECT_EQ(result.Upgrade(), current);
}

/**
 * @tc.name: GetIndexByFocusHub
 * @tc.desc: Test GridFocus GetIndexByFocusHub
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, GetIndexByFocusHub, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    RefPtr<GridItemPattern> gridItemPattern =
        AceType::MakeRefPtr<GridItemPattern>(AceType::MakeRefPtr<ShallowBuilder>(nullptr), GridItemStyle::PLAIN);
    gridItemPattern->irregularItemInfo_ = { 2, 1, 1, 2, 1, 2, 2, 3 };
    auto frameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, 2, gridItemPattern);
    auto gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->UpdateMainIndex(1);
    gridItemLayoutProperty->UpdateCrossIndex(2);
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    WeakPtr<FrameNode> weakFrameNode = std::move(frameNode);
    auto current = AceType::MakeRefPtr<FocusHub>(weakFrameNode);
    WeakPtr<FocusHub> currentFocusNode = std::move(current);
    gridItemPattern->frameNode_ = frameNode;
    GridLayoutInfo info = {
        .defCachedCount_ = 0, .crossCount_ = 3, .startIndex_ = 3, .endIndex_ = 1, .firstRepeatCount_ = 6
    };
    frameNode_->layoutProperty_ = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode_->layoutProperty_->layoutDirection_ = TextDirection::RTL;
    auto grid = AceType::RawPtr(pattern_);

    /**
     * @tc.steps: step2. Set gridMatrix_
     */
    info.gridMatrix_[1] = { { 1, 2 }, { 2, 3 } };
    GridFocus gridFocus(*grid, info);
    gridFocus.curFocusIndexInfo_ = { 1, 2, 2, 1, 1, 2, 2, 3 };

    /**
     * @tc.steps: step3. Calling the GetIndexByFocusHub function
     * @tc.expected: The result of calling the function return 3
     */
    auto result = gridFocus.GetIndexByFocusHub(currentFocusNode);
    EXPECT_EQ(result, 3);
}

/**
 * @tc.name: GetNextIndexByStep
 * @tc.desc: Test GridFocus GetNextIndexByStep
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, GetNextIndexByStep, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    GridLayoutInfo info = { .startMainLineIndex_ = 2,
        .endMainLineIndex_ = 6,
        .startIndex_ = 1,
        .endIndex_ = 8,
        .firstRepeatCount_ = 3,
        .childrenCount_ = 4,
        .hasBigItem_ = 9 };

    frameNode_->layoutProperty_ = AceType::MakeRefPtr<GridLayoutProperty>();
    auto grid = AceType::RawPtr(pattern_);

    /**
     * @tc.steps: step2. Set curMainIndex not found in grid matrix
     */
    info.gridMatrix_[0] = { { 1, 2 }, { 2, 3 } };
    GridFocus gridFocus(*grid, info);

    /**
     * @tc.steps: step3. Calling the GetNextIndexByStep function
     * @tc.expected: The result of calling the function return {-1, -1}
     */
    auto result = gridFocus.GetNextIndexByStep(1, 2, 2, 1, FocusStep::LEFT);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

/**
 * @tc.name: FocusDependence001
 * @tc.desc: Test Grid focusDependence when gridItem get focus
 * @tc.type: FUNC
 */
HWTEST_F(GridFocusTestNg, FocusDependence001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFocusableGridItems(20);
    CreateDone();
    FlushUITasks();
    
    auto focusHub = frameNode_->GetFocusHub();
    EXPECT_NE(focusHub->GetFocusDependence(), FocusDependence::AUTO);
    
    RefPtr<FocusHub> currentFocusNode = GetChildFocusHub(frameNode_, 0);
    currentFocusNode->RequestFocusImmediately();
    FlushUITasks();
    EXPECT_EQ(focusHub->GetFocusDependence(), FocusDependence::AUTO);
}
} // namespace OHOS::Ace::NG