/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

import { int32, uint32 } from "@koalaui/common"
import {
    GlobalStateManager, IncrementalNode, NodeAttach, memoRoot, mutableState
} from "@koalaui/runtime"

class StringerNode extends IncrementalNode {
    constructor(kind: uint32 = 1) {
        super(kind)
    }
    data: string | undefined = undefined
}

const state1 = mutableState<uint32>(17)
const state2 = mutableState<uint32>(1)

/** @memo */
function Stringer(
    arg: string,
    /** @memo */
    content?: () => void
): void {
    if (state1.value - state2.value != 16) {
        console.log("STATE IS INCONSISTENT")
        throw new Error("state1.value - state2.value!= 16")
    }
    NodeAttach(() => new StringerNode(), (node: StringerNode): void => {
        node.data = arg
        console.log("I am recomputing with arg: ", arg)
        content?.()
    })
}

/** @memo */
function demo(node: StringerNode): void {
    Stringer("First", () => {
        console.log("Content of the first")
        Stringer(`Second ${state1.value}`, () => {
            console.log("Content of the second")
            Stringer(`Third ${state2.value}`)
        })
        Stringer("Fourth", () => {
            console.log("Content of the 4th")
            Stringer("5th")
        })
    })
}

async function delay(ms: int32) {
    return new Promise((resolve) => setTimeout(resolve, ms))
}

class Sync {
    private syncCount = 0
    private syncPromise: Promise<void> | undefined = undefined
    private syncPromiseResolve: (() => void) | undefined = undefined

    private init() {
        if (!this.syncPromise)
            this.syncPromise = new Promise(resolve => this.syncPromiseResolve = resolve)
    }

    async sync() {
        while (this.syncCount == 0) {
            this.init()
            await this.syncPromise
            this.syncPromise = undefined
        }
        this.syncCount--
    }

    notify() {
        this.syncCount++
        this.init()
        this.syncPromiseResolve!()
    }
}

let numFrames = 10

async function renderThread(sync: Sync) {
    console.log(">>> render thread")
    const root = memoRoot<StringerNode>(new StringerNode(0), demo)
    console.log(root.value.toHierarchy())

    let frameCount = 0
    const manager = GlobalStateManager.instance

    while (frameCount < numFrames) {
        await sync.sync()
        let updated = manager.updateSnapshot()
        console.log(`>>> render thread frame ${frameCount}, updated=${updated}`)
        if (updated) {
            console.log("Render")
            console.log(root.value.toHierarchy())
        }
        frameCount++
        // Render the UI.
        // Wait for vsync.
    }
    console.log(">>> render thread done")
}

async function businessThread(sync: Sync) {
    console.log("<<< Business thread")

    let loopCount = 0
    while (loopCount < numFrames) {
        await delay(100)
        // Read user input
        // Deliver events to handlers
        // Execute app business logic.
        if (loopCount % 2 == 1) {
            // State update.
            console.log("<<< Business thread update")
            state1.value++
            // This code does not race on JS VM, as concurrency model is not preempting,
            // so we cannot hit in the middle of updateSnapshot().
            await delay(1 + loopCount)
            state2.value++
        } else {
            console.log("<<< Business thread no update")
        }
        loopCount++
        sync.notify()
    }

    console.log("<<< Business thread done")
}

function entry() {
    let sync = new Sync()
    setTimeout(async () => renderThread(sync), 0)
    setTimeout(async () => businessThread(sync), 0)
}

entry()