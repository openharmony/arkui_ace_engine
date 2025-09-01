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

#include <benchmark/benchmark.h>
#include <gmock/gmock.h>
#include <numeric>
#include <vector>


#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"

// Benchmark constants
namespace {
constexpr int32_t CACHED_COUNT = 5;
constexpr double GAP_SIZE = 10.0;
} // namespace

namespace OHOS::Ace::NG {
static void CreateGrid(benchmark::State& state)
{
    for (auto iter : state) { // framework automatically determines number of iterations
        auto gridNode = GridModelNG::CreateFrameNode(0);
        // Test grid configuration operations
        GridModelNG::SetColumnsTemplate(gridNode.GetRawPtr(), "1fr 1fr 1fr");
        GridModelNG::SetRowsTemplate(gridNode.GetRawPtr(), "1fr 1fr");
        GridModelNG::SetColumnsGap(gridNode.GetRawPtr(), Dimension(GAP_SIZE));
        GridModelNG::SetRowsGap(gridNode.GetRawPtr(), Dimension(GAP_SIZE));
        GridModelNG::SetCachedCount(gridNode.GetRawPtr(), CACHED_COUNT);
        GridModelNG::SetScrollEnabled(gridNode.GetRawPtr(), true);
        gridNode->MarkModifyDone();
    }
}

static void LayoutGrid(benchmark::State& state)
{
    const auto numItems = state.range(0);
    for (auto it : state) {
        auto frameNode = GridModelNG::CreateFrameNode(0);
        ViewAbstract::SetWidth(frameNode.GetRawPtr(), CalcLength(Dimension(100)));
        ViewAbstract::SetHeight(frameNode.GetRawPtr(), CalcLength(Dimension(100)));
        GridModelNG::SetRowsTemplate(frameNode.GetRawPtr(), "1fr 1fr");
        // Create grid items as children using GridItemModelNG APIs
        for (int32_t i = 0; i < numItems; ++i) {
            auto gridItemNode = GridItemModelNG::CreateFrameNode(i);
            GridItemModelNG::SetRowStart(gridItemNode.GetRawPtr(), i / 2);
            GridItemModelNG::SetColumnStart(gridItemNode.GetRawPtr(), i % 2);
            GridItemModelNG::SetSelectable(gridItemNode.GetRawPtr(), true);
            gridItemNode->MountToParent(frameNode);
            gridItemNode->MarkModifyDone();
        }
        frameNode->MarkModifyDone();
        frameNode->SetActive();
        frameNode->SetLayoutDirtyMarked(true);
        frameNode->CreateLayoutTask();
        benchmark::DoNotOptimize(frameNode);
    }
}

BENCHMARK(CreateGrid);
BENCHMARK(LayoutGrid)->Range(8, 512); // range specifies number of children
} // namespace OHOS::Ace::NG
