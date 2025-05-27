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

#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"

namespace OHOS::Ace::NG {
class GridScrollLayoutTestNg : public GridTestNg {
};

/**
 * @tc.name: GetStartingItem001
 * @tc.desc: Test GetStartingItem in GridScrollWithOptionsLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GetStartingItem001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetLayoutOptions(option);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedHeightItems(600, ITEM_MAIN_SIZE);
    CreateDone();

    ScrollToIndex(99, false, ScrollAlign::END);
    FlushUITasks();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());

    layoutAlgorithm->info_.hasBigItem_ = true;
    EXPECT_EQ(layoutAlgorithm->GetStartingItem(AceType::RawPtr(frameNode_), 99), 99);
}
} // namespace OHOS::Ace::NG
 