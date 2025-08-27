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

#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"

// Benchmark constants
namespace {
constexpr int32_t MIN_ITER_COUNT = 50;
constexpr int32_t MAX_ITER_COUNT = 1000;
constexpr int32_t CACHED_COUNT = 5;
constexpr double GAP_SIZE = 10.0;
} // namespace

namespace OHOS::Ace::NG {
static void CreateGrid(benchmark::State& state)
{
    testing::FLAGS_gmock_verbose = "error";
    auto gridCount = static_cast<int32_t>(state.range(0));
    for (auto iter : state) {
        // Test creating multiple grid frame nodes
        std::vector<RefPtr<FrameNode>> grids {};
        grids.reserve(gridCount);

        for (int32_t i = 0; i < gridCount; ++i) {
            auto gridNode = GridModelNG::CreateFrameNode(i);
            grids.push_back(gridNode);
            // Test grid configuration operations
            GridModelNG::SetColumnsTemplate(gridNode.GetRawPtr(), "1fr 1fr 1fr");
            GridModelNG::SetRowsTemplate(gridNode.GetRawPtr(), "1fr 1fr");
            GridModelNG::SetColumnsGap(gridNode.GetRawPtr(), Dimension(GAP_SIZE));
            GridModelNG::SetRowsGap(gridNode.GetRawPtr(), Dimension(GAP_SIZE));
            GridModelNG::SetCachedCount(gridNode.GetRawPtr(), CACHED_COUNT);
            GridModelNG::SetScrollEnabled(gridNode.GetRawPtr(), true);
            gridNode->MarkModifyDone();
        }

        benchmark::DoNotOptimize(grids);
    }
}

static void CreateGridWithModel(benchmark::State& state)
{
    testing::FLAGS_gmock_verbose = "error";
    for (auto iter : state) {
        GridModelNG gridModel;
        // Create grid with controller
        RefPtr<ScrollControllerBase> controller = nullptr;
        RefPtr<ScrollProxy> scrollProxy = nullptr;
        gridModel.Create(controller, scrollProxy);
        gridModel.Pop();

        benchmark::DoNotOptimize(gridModel);
    }
}

static void LayoutGrid(benchmark::State& state)
{
    auto frameNode = GridModelNG::CreateFrameNode(0);
    ViewAbstract::SetWidth(frameNode.GetRawPtr(), CalcLength(Dimension(100)));
    ViewAbstract::SetHeight(frameNode.GetRawPtr(), CalcLength(Dimension(100)));
    GridModelNG::SetRowsTemplate(frameNode.GetRawPtr(), "1fr 1fr");
    // Create grid items as children using GridItemModelNG APIs
    for (int32_t i = 0; i < 10; ++i) {
        auto gridItemNode = GridItemModelNG::CreateFrameNode(i);
        GridItemModelNG::SetRowStart(gridItemNode.GetRawPtr(), i / 2);
        GridItemModelNG::SetColumnStart(gridItemNode.GetRawPtr(), i % 2);
        GridItemModelNG::SetSelectable(gridItemNode.GetRawPtr(), true);
        gridItemNode->MountToParent(frameNode);
        gridItemNode->MarkModifyDone();
    }
    frameNode->MarkModifyDone();
    for (auto iter : state) {
        frameNode->SetActive();
        frameNode->SetLayoutDirtyMarked(true);
        frameNode->CreateLayoutTask();
    }
}

// Register benchmarks with varying sizes
BENCHMARK(CreateGrid)->Range(MIN_ITER_COUNT, MAX_ITER_COUNT)->Unit(benchmark::kMicrosecond);
BENCHMARK(CreateGridWithModel)->Range(MIN_ITER_COUNT, MAX_ITER_COUNT)->Unit(benchmark::kMicrosecond);
BENCHMARK(LayoutGrid)->Range(MIN_ITER_COUNT, MAX_ITER_COUNT)->Unit(benchmark::kMicrosecond);
} // namespace OHOS::Ace::NG

// Main
BENCHMARK_MAIN();
