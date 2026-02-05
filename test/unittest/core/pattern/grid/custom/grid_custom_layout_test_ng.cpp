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

#include "custom_layout_options.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/grid/grid_test_ng.h"

#include "core/components_ng/pattern/grid/grid_custom/grid_custom_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"

namespace OHOS::Ace::NG {
class GridCustomLayoutTestNg : public GridTestNg {};

/**
 * @tc.name: InitializedMeasure
 * @tc.desc: Test Grid custom layout algorithm initial measure
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, InitializedMeasure, TestSize.Level1)
{
    int32_t crossCount = 2;
    GridLayoutOptions options;
    auto onGetStartIndexByOffset = [crossCount](float offset) -> GridStartLineInfo {
        int32_t line = offset / static_cast<int32_t>(ITEM_MAIN_SIZE);
        float startOffset = std::fmod(offset, ITEM_MAIN_SIZE);
        return { .startIndex = line * crossCount, .startLine = line, .startOffset = startOffset };
    };
    options.getStartIndexByOffset = std::move(onGetStartIndexByOffset);

    auto onGetStartIndexByIndex = [crossCount](int32_t targetIndex) -> GridStartLineInfo {
        int32_t line = targetIndex / crossCount;
        return { .startIndex = line * crossCount, .startLine = line };
    };
    options.getStartIndexByIndex = std::move(onGetStartIndexByIndex);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(options);
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 7);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 3);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: ScrollByBackward001
 * @tc.desc: Test Grid custom layout algorithm with scroll by
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, ScrollByBackward001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    ScrollBy(0, ITEM_MAIN_SIZE / 2);
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 9);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 4);
    EXPECT_EQ(pattern_->info_.currentOffset_, -50);

    ScrollBy(0, ITEM_MAIN_SIZE * 2);
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 2);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 6);
    EXPECT_EQ(pattern_->info_.currentOffset_, -50);
}

/**
 * @tc.name: ScrollByBackward002
 * @tc.desc: Test Grid custom layout algorithm with scroll by large Offset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, ScrollByBackward002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    ScrollBy(0, HEIGHT * 2);
    EXPECT_EQ(pattern_->info_.startIndex_, 16);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 8);
    EXPECT_EQ(pattern_->info_.endIndex_, 23);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 11);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);

    ScrollBy(0, HEIGHT * 3);
    EXPECT_EQ(pattern_->info_.startIndex_, 40);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 20);
    EXPECT_EQ(pattern_->info_.endIndex_, 47);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 23);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: ScrollToBackward001
 * @tc.desc: Test Grid custom layout algorithm with scroll To
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, ScrollToBackward001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    ScrollTo(HEIGHT * 2);
    EXPECT_EQ(pattern_->info_.startIndex_, 16);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 8);
    EXPECT_EQ(pattern_->info_.endIndex_, 23);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 11);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);

    ScrollTo(HEIGHT * 5);
    EXPECT_EQ(pattern_->info_.startIndex_, 40);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 20);
    EXPECT_EQ(pattern_->info_.endIndex_, 47);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 23);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: UpdateCurrentOffset
 * @tc.desc: Test Grid custom layout algorithm with updateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, UpdateCurrentOffset, TestSize.Level1)
{
    int32_t crossCount = 2;
    auto onScrollbarUpdate = [crossCount](int32_t index,
                                 Dimension offset) -> std::pair<std::optional<float>, std::optional<float>> {
        return { index / crossCount * ITEM_MAIN_SIZE - offset.Value(), ITEM_MAIN_SIZE / crossCount * ITEM_MAIN_SIZE };
    };
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(crossCount, ITEM_MAIN_SIZE));
    model.SetOnScrollBarUpdate(std::move(onScrollbarUpdate));
    CreateFixedItems(50);
    CreateDone();
    for (int32_t i = 1; i < 15; ++i) {
        UpdateCurrentOffset(-30.0f, SCROLL_FROM_UPDATE);
        EXPECT_EQ(pattern_->GetTotalOffset(), 30.f * i);
    }
}

/**
 * @tc.name: UpdateCrossCount
 * @tc.desc: Test Grid custom layout algorithm with crossCount updated
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, UpdateCrossCount, TestSize.Level1)
{
    int32_t crossCount = 2;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(crossCount, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 42);
    EXPECT_EQ(pattern_->info_.endIndex_, 49);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.totalOffset_, 2100.f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr");
    layoutProperty_->UpdateLayoutOptions(GetRegularDemoOptions(4, ITEM_MAIN_SIZE));
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 36);
    EXPECT_EQ(pattern_->info_.endIndex_, 49);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.totalOffset_, 900.f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    layoutProperty_->UpdateLayoutOptions(GetRegularDemoOptions(3, ITEM_MAIN_SIZE));
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 36);
    EXPECT_EQ(pattern_->info_.endIndex_, 47);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.totalOffset_, 1200.f);
}
} // namespace OHOS::Ace::NG
