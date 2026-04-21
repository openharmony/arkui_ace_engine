"use strict";
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
 *
*/

/**
 * ignoreLayoutSafeArea Layout Scheduling Simulator
 *
 * Simulates two mechanisms:
 * 1. Container Proactive Packing (Flex): ChildPreMeasureHelperEnabled=false, PostponedTaskForIgnoreEnabled=false
 * 2. Non-intrusive Pattern Hook (MultiChild): ChildPreMeasureHelperEnabled=true, PostponedTaskForIgnoreEnabled=true
 *
 * Reference: Ignore_Layout_Safe_Area_Knowledge_Base.md (absolutely correct)
 *
 * Test data is loaded from ignore_layout_test_data.json.
 * Run via: node ignore_layout_simulator.js [path/to/data.json]
 */
const fs = require("fs");
const path = require("path");

// ==================== Simulation Node ====================
class SimNode {
    constructor(config, parent = null) {
        this._delaySelfLayoutForIgnore = false;
        this.hasPreMeasured = false;
        this.ignoreLayoutProcess = false;
        this.delayMeasureChildren = [];
        this.delayLayoutChildren = [];
        this.name = config.name;
        this.type = config.type;
        this.isIgnore = config.isIgnore ?? false;
        this.parent = parent;
        this.children = (config.children || []).map((c) => new SimNode(c, this));
    }
    setDelaySelfLayoutForIgnore() {
        this._delaySelfLayoutForIgnore = true;
    }
    getDelaySelfLayoutForIgnore() {
        const val = this._delaySelfLayoutForIgnore;
        this._delaySelfLayoutForIgnore = false;
        return val;
    }
}

// ==================== Simulator ====================
class Simulator {
    constructor() {
        this.events = [];
        this.bundleQueue = [];
    }
    record(event) {
        this.events.push(event);
    }
    simulate(rootConfig) {
        this.events = [];
        this.bundleQueue = [];
        const root = new SimNode(rootConfig);
        this.createLayoutTask(root, "NORMAL");
        while (this.bundleQueue.length > 0) {
            this.flushPostponedLayoutTask();
        }
        return [...this.events];
    }
    createLayoutTask(node, layoutType) {
        if (layoutType === "LAYOUT_FOR_IGNORE") {
            this.frameNodeLayout(node);
            return;
        }
        if (layoutType === "MEASURE_FOR_IGNORE") {
            node.ignoreLayoutProcess = true;
        }
        this.frameNodeMeasure(node);
        this.frameNodeLayout(node);
        if (layoutType === "MEASURE_FOR_IGNORE") {
            node.ignoreLayoutProcess = false;
        }
    }
    /**
     * FrameNode::Measure simulation.
     * Checks PreMeasure (Pattern Hook only), then calls algorithm Measure,
     * then PostTaskForIgnore (Pattern Hook only).
     */
    frameNodeMeasure(node) {
        const parent = node.parent;
        if (parent && parent.type === "multiChild" && node.isIgnore) {
            if (!(node.ignoreLayoutProcess && node.hasPreMeasured)) {
                node.setDelaySelfLayoutForIgnore();
                node.hasPreMeasured = true;
                parent.delayMeasureChildren.push(node);
                parent.delayLayoutChildren.push(node);
                this.record(`${node.name}:PreMeasure(skip)`);
                return;
            }
        }
        this.algorithmMeasure(node);
        if (node.type === "multiChild" && node.delayMeasureChildren.length > 0) {
            const bundle = {
                first: [...node.delayMeasureChildren],
                second: node,
            };
            this.bundleQueue.push(bundle);
            node.delayMeasureChildren = [];
        }
    }
    /**
     * LayoutAlgorithm::Measure simulation.
     * Flex: Container Proactive Packing (IsExpandConstraintNeeded check)
     * MultiChild: measures all children normally (PreMeasure handled in frameNodeMeasure)
     * Leaf: no children
     */
    algorithmMeasure(node) {
        this.record(`${node.name}:Measure`);
        if (node.type === "leaf")
            return;
        if (node.type === "flex") {
            const localBundle = [];
            for (const child of node.children) {
                if (child.isIgnore) {
                    localBundle.push(child);
                    child.setDelaySelfLayoutForIgnore();
                    continue;
                }
                this.frameNodeMeasure(child);
            }
            if (localBundle.length > 0) {
                node.setDelaySelfLayoutForIgnore();
                this.bundleQueue.push({ first: localBundle, second: node });
            }
            return;
        }
        if (node.type === "multiChild") {
            for (const child of node.children) {
                this.frameNodeMeasure(child);
            }
            return;
        }
    }
    /**
     * FrameNode::Layout simulation.
     * Checks delaySelfLayoutForIgnore flag (consumes on read).
     */
    frameNodeLayout(node) {
        if (node.getDelaySelfLayoutForIgnore()) {
            this.record(`${node.name}:Layout(skip)`);
            return;
        }
        this.algorithmLayout(node);
    }
    /**
     * LayoutAlgorithm::Layout simulation.
     * All containers: layout all children.
     */
    algorithmLayout(node) {
        this.record(`${node.name}:Layout`);
        if (node.type === "leaf")
            return;
        for (const child of node.children) {
            this.frameNodeLayout(child);
        }
    }
    /**
     * FlushPostponedLayoutTask simulation.
     * Processes bundles in REVERSE order.
     * For each bundle: MEASURE_FOR_IGNORE on children, then container processing.
     */
    flushPostponedLayoutTask() {
        const currentBundles = [...this.bundleQueue];
        this.bundleQueue = [];
        for (let i = currentBundles.length - 1; i >= 0; i--) {
            const bundle = currentBundles[i];
            for (const child of bundle.first) {
                this.createLayoutTask(child, "MEASURE_FOR_IGNORE");
            }
            const container = bundle.second;
            if (container.type === "multiChild") {
                container.delayLayoutChildren = [];
            }
            else {
                this.createLayoutTask(container, "LAYOUT_FOR_IGNORE");
            }
        }
    }
}

// ==================== Runner ====================

function loadTestData(jsonPath) {
    const raw = fs.readFileSync(jsonPath, "utf-8");
    return JSON.parse(raw);
}

function main() {
    const defaultDataPath = path.join(__dirname, "ignore_layout_test_data.json");
    const dataPath = process.argv[2] || defaultDataPath;

    if (!fs.existsSync(dataPath)) {
        console.error(`Error: test data file not found: ${dataPath}`);
        process.exit(1);
    }

    const data = loadTestData(dataPath);
    const sim = new Simulator();

    for (const t of data.tests) {
        const result = sim.simulate(t.config);
        console.log(`\n=== ${t.name} (${result.length} events) ===`);
        for (let i = 0; i < result.length; i++) {
            console.log(`  [${i}] "${result[i]}",`);
        }
    }
}

main();
