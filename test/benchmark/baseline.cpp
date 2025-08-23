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
#include <numeric>
#include <vector>

/**
 * @brief Provides baseline performance measurements using simple addition and std::accumulate.
 *        The ratio between baseline and actual code performance can be tracked to prevent regressions.
 */

static void BaselineAdd(benchmark::State& state)
{
    std::vector<int> data(state.range(0), 1);
    for (auto _ : state) {
        long long sum = 0;
        for (int v : data) {
            sum += v;
        }
        benchmark::DoNotOptimize(sum); // prevent compiler from optimizing away
    }
}

static void BaselineAccumulate(benchmark::State& state)
{
    std::vector<int> data(state.range(0), 1);
    for (auto _ : state) {
        auto sum = std::accumulate(data.begin(), data.end(), 0LL);
        benchmark::DoNotOptimize(sum);
    }
}

// Register benchmarks with varying sizes
BENCHMARK(BaselineAdd)->Range(8, 8 << 10);
BENCHMARK(BaselineAccumulate)->Range(8, 8 << 10);

// Main
BENCHMARK_MAIN();
