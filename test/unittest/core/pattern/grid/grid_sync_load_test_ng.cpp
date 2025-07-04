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

#include "grid_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"
namespace OHOS::Ace::NG {
class GridSyncLoadTestNg : public GridTestNg {
public:
    void TearDown() override;
    GridItemModelNG CreateGridItemForSyncLoad(float width, float height, GridItemStyle gridItemStyle);
    void CreateGridItems(int32_t itemNumber);
};

void GridSyncLoadTestNg::TearDown()
{
    GridTestNg::TearDown();
    MockPipelineContext::GetCurrent()->SetResponseTime(INT32_MAX);
}

GridItemModelNG GridSyncLoadTestNg::CreateGridItemForSyncLoad(float width, float height, GridItemStyle gridItemStyle)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    GridItemModelNG itemModel;
    itemModel.Create(gridItemStyle);
    ViewAbstract::SetWidth(CalcLength(width));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewAbstract::SetFocusable(true);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    frameNode->measureCallback_ = [](RefPtr<Kit::FrameNode>& node) {
        NG::MockPipelineContext::GetCurrent()->DecResponseTime();
    };
    return itemModel;
}

void GridSyncLoadTestNg::CreateGridItems(int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        CreateGridItemForSyncLoad(FILL_VALUE, ITEM_MAIN_SIZE, GridItemStyle::NONE);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

/**
 * @tc.name: SyncLoad001
 * @tc.desc: Test Grid sync load
 * @tc.type: FUNC
 */
HWTEST_F(GridSyncLoadTestNg, SyncLoad001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Grid
     * @tc.expected: Grid load 2 item(just one line) in first frame
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetSyncLoad(false);
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    model.SetOnReachStart(event);
    CreateGridItems(10);
    MockPipelineContext::GetCurrent()->SetResponseTime(2);
    CreateDone();
    EXPECT_EQ(pattern_->info_.endIndex_, 1);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 0);
    EXPECT_TRUE(frameNode_->isLayoutDirtyMarked_);
    EXPECT_FALSE(isTrigger);
    
    /**
     * @tc.steps: step2. Flush next frame
     * @tc.expected: Grid load 1 item(less than one line) in the second frame
     */
    MockPipelineContext::GetCurrent()->SetResponseTime(1);
    MockPipelineContext::GetCurrent()->FlushUITaskWithSingleDirtyNode(frameNode_);
    EXPECT_EQ(pattern_->info_.endIndex_, 2);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 1);

    /**
     * @tc.steps: step3. fill grid
     * @tc.expected: trigger grid onReachStart
     */
    MockPipelineContext::GetCurrent()->SetResponseTime(INT32_MAX);
    MockPipelineContext::GetCurrent()->FlushUITaskWithSingleDirtyNode(frameNode_);
    EXPECT_FALSE(frameNode_->isLayoutDirtyMarked_);
    EXPECT_EQ(pattern_->info_.endIndex_, 7);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: SyncLoad002
 * @tc.desc: Test Grid sync load
 * @tc.type: FUNC
 */
HWTEST_F(GridSyncLoadTestNg, SyncLoad002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Grid
     * @tc.expected: Grid load 1 item(less than one line) in first frame
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetSyncLoad(false);
    CreateGridItems(10);
    MockPipelineContext::GetCurrent()->SetResponseTime(1);
    CreateDone();
    EXPECT_EQ(pattern_->info_.endIndex_, 0);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 0);
    EXPECT_TRUE(frameNode_->isLayoutDirtyMarked_);

    /**
     * @tc.steps: step2. Flush next frame
     * @tc.expected: Grid load 1 item(fill the first line) in the second frame
     */
    MockPipelineContext::GetCurrent()->SetResponseTime(1);
    MockPipelineContext::GetCurrent()->FlushUITaskWithSingleDirtyNode(frameNode_);
    EXPECT_EQ(pattern_->info_.endIndex_, 1);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 0);
}

/**
 * @tc.name: SyncLoad003
 * @tc.desc: Test Grid sync load
 * @tc.type: FUNC
 */
HWTEST_F(GridSyncLoadTestNg, SyncLoad003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Grid
     * @tc.expected: Fill current page
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetSyncLoad(false);
    CreateGridItems(100);
    CreateDone();
    EXPECT_EQ(pattern_->info_.endIndex_, 7);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 3);

    /**
     * @tc.steps: step2. scroll page with animation
     * @tc.expected: fill next page
     */
    pattern_->UpdateCurrentOffset(-HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    MockPipelineContext::GetCurrent()->SetResponseTime(1);
    MockPipelineContext::GetCurrent()->FlushUITaskWithSingleDirtyNode(frameNode_);
    EXPECT_EQ(pattern_->info_.endIndex_, 15);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 7);

    /**
     * @tc.steps: step3. scroll page without animation
     * @tc.expected: fill next page
     */
    pattern_->ScrollPage(false);
    MockPipelineContext::GetCurrent()->SetResponseTime(1);
    MockPipelineContext::GetCurrent()->FlushUITaskWithSingleDirtyNode(frameNode_);
    EXPECT_EQ(pattern_->info_.endIndex_, 23);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 11);
}

/**
 * @tc.name: SyncLoad004
 * @tc.desc: Test Grid sync load with cachedCount show
 * @tc.type: FUNC
 */
HWTEST_F(GridSyncLoadTestNg, SyncLoad004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Grid
     * @tc.expected: Fill current page
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetSyncLoad(false);
    model.SetCachedCount(0, false);
    CreateGridItems(100);
    CreateDone();
    EXPECT_EQ(pattern_->info_.endIndex_, 7);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 3);

    /**
     * @tc.steps: step2. set cache shown and limit layout time
     * @tc.expected: layout cached items by limited count
     */
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, CachedCount, 2, frameNode_);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, ShowCachedItems, true, frameNode_);
    MockPipelineContext::GetCurrent()->SetResponseTime(1);
    MockPipelineContext::GetCurrent()->FlushUITaskWithSingleDirtyNode(frameNode_);
    EXPECT_EQ(pattern_->info_.gridMatrix_.size(), 5);
    EXPECT_EQ(pattern_->info_.gridMatrix_.rbegin()->second.size(), 1);

    /**
     * @tc.steps: step3. flush next layout
     * @tc.expected: fill current cached line and start the second
     */
    MockPipelineContext::GetCurrent()->SetResponseTime(2);
    MockPipelineContext::GetCurrent()->FlushUITaskWithSingleDirtyNode(frameNode_);
    EXPECT_EQ(pattern_->info_.gridMatrix_.size(), 6);
    EXPECT_EQ(pattern_->info_.gridMatrix_.rbegin()->second.size(), 1);
}

/**
 * @tc.name: SyncLoad005
 * @tc.desc: Test Grid sync load during scrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridSyncLoadTestNg, SyncLoad005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Grid
     * @tc.expected: Fill current page
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    GridLayoutOptions options;
    model.SetLayoutOptions(options);
    model.SetSyncLoad(false);
    model.SetCachedCount(0, false);
    CreateGridItems(100);
    CreateDone();
    EXPECT_EQ(pattern_->info_.endIndex_, 7);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 3);

    /**
     * @tc.steps: step2. scroll to index without animation
     * @tc.expected: layout items by limited count
     */
    MockPipelineContext::GetCurrent()->SetResponseTime(1);
    int32_t targetIndex = 30;
    ScrollAlign align = ScrollAlign::START;
    ScrollToIndex(targetIndex, false, align);
    EXPECT_EQ(pattern_->info_.startIndex_, 30);
    EXPECT_EQ(pattern_->info_.endIndex_, 32);

    /**
     * @tc.steps: step3. scroll to index with animation
     * @tc.expected: layout all items
     */
    MockPipelineContext::GetCurrent()->SetResponseTime(2);
    targetIndex = 80;
    align = ScrollAlign::START;
    ScrollToIndex(targetIndex, true, align);
    if (!MockAnimationManager::GetInstance().AllFinished()) {
        MockAnimationManager::GetInstance().Tick();
        FlushUITasks();
    }
    EXPECT_EQ(pattern_->info_.startIndex_, targetIndex);
    EXPECT_EQ(pattern_->info_.endIndex_, targetIndex + 7);
}
} // namespace OHOS::Ace::NG
