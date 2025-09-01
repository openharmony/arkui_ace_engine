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
#include <memory>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @brief Provides baseline performance measurements for UI operations.
 *        The ratio between baseline and actual code performance can be tracked to prevent regressions.
 */

// Mock UI Node structure for baseline
struct MockUINode {
    int32_t id;
    std::string tag;
    float x, y, width, height;
    std::vector<std::shared_ptr<MockUINode>> children;
    std::unordered_map<std::string, float> properties;

    MockUINode(int32_t nodeId, const std::string& nodeTag) : id(nodeId), tag(nodeTag), x(0), y(0), width(0), height(0)
    {}
};

// Baseline for node creation - similar to FrameNode creation
static void BaselineNodeCreation(benchmark::State& state)
{
    const int nodeCount = 10;
    for (auto _ : state) {
        std::vector<std::shared_ptr<MockUINode>> nodes;
        nodes.reserve(nodeCount);

        for (int i = 0; i < nodeCount; ++i) {
            auto node = std::make_shared<MockUINode>(i, "Node" + std::to_string(i));
            node->properties["opacity"] = 1.0f;
            node->properties["rotation"] = 0.0f;
            nodes.push_back(node);
        }
        benchmark::DoNotOptimize(nodes);
    }
}

// Baseline for tree construction - similar to UI tree building
static void BaselineTreeConstruction(benchmark::State& state)
{
    const int childCount = 10;
    for (auto _ : state) {
        auto root = std::make_shared<MockUINode>(0, "Root");

        for (int i = 1; i <= childCount; ++i) {
            auto child = std::make_shared<MockUINode>(i, "Child" + std::to_string(i));
            root->children.push_back(child);
        }
        benchmark::DoNotOptimize(root);
    }
}

// Baseline for layout calculation - similar to layout algorithm
static void BaselineLayoutCalculation(benchmark::State& state)
{
    const int nodeCount = 10;
    // Pre-create nodes
    std::vector<std::shared_ptr<MockUINode>> nodes;
    for (int i = 0; i < nodeCount; ++i) {
        auto node = std::make_shared<MockUINode>(i, "Node" + std::to_string(i));
        nodes.push_back(node);
    }

    for (auto _ : state) {
        float totalWidth = 0;
        float totalHeight = 0;

        // Simulate layout calculation
        for (auto& node : nodes) {
            node->width = static_cast<float>(node->id % 100 + 50); // Varying widths
            node->height = static_cast<float>(node->id % 80 + 30); // Varying heights
            node->x = totalWidth;
            node->y = static_cast<float>(node->id / 10 * 50); // Row-based positioning

            totalWidth += node->width + 5.0f; // Gap
            totalHeight = std::max(totalHeight, node->y + node->height);
        }

        benchmark::DoNotOptimize(totalWidth);
        benchmark::DoNotOptimize(totalHeight);
    }
}

// Baseline for property updates - similar to style/property changes
static void BaselinePropertyUpdate(benchmark::State& state)
{
    const int nodeCount = 10;
    // Pre-create nodes
    std::vector<std::shared_ptr<MockUINode>> nodes;
    for (int i = 0; i < nodeCount; ++i) {
        auto node = std::make_shared<MockUINode>(i, "Node" + std::to_string(i));
        node->properties["opacity"] = 1.0f;
        node->properties["rotation"] = 0.0f;
        node->properties["scale"] = 1.0f;
        nodes.push_back(node);
    }

    for (auto _ : state) {
        for (auto& node : nodes) {
            node->properties["opacity"] = static_cast<float>(node->id % 100) / 100.0f;
            node->properties["rotation"] = static_cast<float>(node->id % 360);
            node->properties["scale"] = 1.0f + static_cast<float>(node->id % 50) / 100.0f;
        }
        benchmark::DoNotOptimize(nodes);
    }
}

// Baseline for tree traversal - similar to layout/render tree walks
static void BaselineTreeTraversal(benchmark::State& state)
{
    const int level1Count = 10;
    const int level2Count = 10;
    // Create a tree structure
    auto root = std::make_shared<MockUINode>(0, "Root");
    int nodeId = 1;

    // Create multiple levels
    for (int level1 = 0; level1 < level1Count; ++level1) {
        auto child1 = std::make_shared<MockUINode>(nodeId++, "Level1_" + std::to_string(level1));
        for (int level2 = 0; level2 < level2Count; ++level2) {
            auto child2 = std::make_shared<MockUINode>(nodeId++, "Level2_" + std::to_string(level2));
            child1->children.push_back(child2);
        }
        root->children.push_back(child1);
    }

    for (auto _ : state) {
        int visitCount = 0;
        std::function<void(const std::shared_ptr<MockUINode>&)> traverse =
            [&](const std::shared_ptr<MockUINode>& node) {
                visitCount++;
                for (auto& child : node->children) {
                    traverse(child);
                }
            };

        traverse(root);
        benchmark::DoNotOptimize(visitCount);
    }
}

// Register benchmarks
BENCHMARK(BaselineNodeCreation);
BENCHMARK(BaselineTreeConstruction);
BENCHMARK(BaselineLayoutCalculation);
BENCHMARK(BaselinePropertyUpdate);
BENCHMARK(BaselineTreeTraversal);

// Main
BENCHMARK_MAIN();
