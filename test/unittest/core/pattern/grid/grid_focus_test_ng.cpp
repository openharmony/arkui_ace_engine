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

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/manager/focus/focus_manager.h"
#include "core/components_ng/pattern/grid/grid_focus.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class GridFocusTestNg : public TestNG {
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
} // namespace OHOS::Ace::NG