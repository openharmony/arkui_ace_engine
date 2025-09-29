/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { int32 } from "@koalaui/common"

/**
 * Adds statistics for constructing/disposing of the TreeNode instances.
 * It is disabled by default because collecting such data affects performance.
 */
const DEBUG_WITH_NODE_STATS = false

export class RuntimeProfiler {
    private static readonly map: Map<int32, Set<Object> > | undefined = DEBUG_WITH_NODE_STATS
        ? new Map<int32, Set<Object>>()
        : undefined

    static nodeCreated(nodeType: int32, node: Object) {
        if (RuntimeProfiler.map === undefined) return
        let set = RuntimeProfiler.map!.get(nodeType)
        if (set === undefined) {
            set = new Set<Object>()
            RuntimeProfiler.map!.set(nodeType, set)
        }
        set.add(node)
    }

    static nodeDisposed(nodeType: int32, node: Object) {
        if (RuntimeProfiler.map === undefined) return
        let set = RuntimeProfiler.map!.get(nodeType)
        if (set === undefined) throw new Error("node never existed")
        if (!set.delete(node)) console.log("node is already disposed")
    }

    public static instance: RuntimeProfiler | undefined = undefined

    private invalidations = 0
    private computes = 0
    private builds = 0
    private nodes = 0
    private realDraws = 0
    private cachedDraws = 0
    private measures = 0
    private layouts = 0
    private frames = 0
    private lastTime = 0.0
    private lastFPS = 0
    private updateEnterTime = 0.0
    private updateExitTime = 0.0
    private updateTime = 0.0
    private buildEnterTime = 0.0
    private buildExitTime = 0.0
    private buildTime = 0.0
    private layoutEnterTime = 0.0
    private layoutExitTime = 0.0
    private layoutTime = 0.0
    private drawEnterTime = 0.0
    private drawExitTime = 0.0
    private drawTime = 0.0
    private updatableStates = 0
    private mutableStates = 0
    private computableValues = 0

    static enable() {
        RuntimeProfiler.instance = new RuntimeProfiler()
    }

    static disable() {
        RuntimeProfiler.instance = undefined
    }

    static enabled(): boolean {
        return RuntimeProfiler.instance != undefined
    }

    reset() {
        this.invalidations = 0
        this.computes = 0
        this.builds = 0
        this.nodes = 0
        this.realDraws = 0
        this.cachedDraws = 0
        this.layouts = 0
        this.measures = 0
        this.updateEnterTime = 0
        this.updateExitTime = 0
        this.updatableStates = 0
        this.mutableStates = 0
        this.computableValues = 0
    }

    report() {
        console.log(this.getReport())
    }

    getReport(): string {
        const updateTime = Math.round(1000 * (this.updateExitTime - this.updateEnterTime))
        const buildTime = Math.round(1000 * (this.buildExitTime - this.buildEnterTime))
        const layoutTime = Math.round(1000 * (this.layoutExitTime - this.layoutEnterTime))
        const drawTime = Math.round(1000 * (this.drawExitTime - this.drawEnterTime))
        if (this.updateTime < updateTime) this.updateTime = updateTime
        if (this.buildTime < buildTime) this.buildTime = buildTime
        if (this.layoutTime < layoutTime) this.layoutTime = layoutTime
        if (this.drawTime < drawTime) this.drawTime = drawTime

        // Improve: OHOS does not properly handle \n in template literals
        const array = Array.of<string>(
            `invalidations: ${this.invalidations}`,
            `modified states: ${this.mutableStates}/${this.updatableStates} + ${this.computableValues}`,
            `update states (mks): ${this.updateTime} / ${updateTime}`,
            `build root node (mks): ${this.buildTime} / ${buildTime}`,
            `layout view (mks): ${this.layoutTime} / ${layoutTime}`,
            `draw view (mks): ${this.drawTime} / ${drawTime}`,
            `computes: ${this.computes}`,
            `builds: ${this.builds}`,
            `nodes: ${this.nodes}`,
            `realDraws: ${this.realDraws}`,
            `cachedDraws: ${this.cachedDraws}`,
            `measures: ${this.measures}`,
            `layouts: ${this.layouts}`,
            `FPS: ${this.lastFPS}`,
        )
        RuntimeProfiler.map?.forEach((set:Set<Object>, kind:int32) => {
            if (set.size > 0) array.push(kind + ":" + set.size)
        })
        return array.join("\n")
    }

    invalidation() { this.invalidations++ }
    compute() { this.computes++ }
    build() { this.builds++ }
    node() { this.nodes++ }
    realDraw() { this.realDraws++ }
    cachedDraw() { this.cachedDraws++ }
    layout() {  this.layouts++ }
    measure() { this.measures++ }
    frame(ms: number) {
        if (ms - this.lastTime <= 1000) {
            this.frames++
        } else {
            this.lastFPS = Math.round(this.frames * 1000 / (ms - this.lastTime)) as int32
            this.frames = 1
            this.lastTime = ms
        }
    }
    buildRootEnter() {
        this.buildEnterTime = Date.now()
    }
    buildRootExit() {
        this.buildExitTime = Date.now()
    }
    layoutEnter() {
        this.layoutEnterTime = Date.now()
    }
    layoutExit() {
        this.layoutExitTime = Date.now()
    }
    drawEnter() {
        this.drawEnterTime = Date.now()
    }
    drawExit() {
        this.drawExitTime = Date.now()
    }
    updateSnapshotEnter() {
        this.updateEnterTime = Date.now()
    }
    updateSnapshotExit() {
        this.updateExitTime = Date.now()
    }
    updateSnapshot(modified: int32, all?: int32) {
        if (all === undefined) {
            this.computableValues = modified - this.mutableStates

        } else {
            this.mutableStates = modified
            this.updatableStates = all
        }
    }
}
