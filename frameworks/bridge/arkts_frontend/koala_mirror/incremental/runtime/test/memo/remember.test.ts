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

import { Assert as assert, suite, test } from "@koalaui/harness"
import {
    GlobalStateManager,
    State,
    TestNode,
    memoLifecycle,
    mutableState,
    once,
    remember,
    rememberDisposable,
    rememberMutableState,
    testTick,
} from "../../src"

const collector = new Array<string>()

function testExpected(root: State<TestNode>, ...expected: string[]) {
    collector.length = 0
    testTick(root)
    assert.deepEqual(collector, expected)
    if (expected.length > 0) testExpected(root)
}

suite("remember tests", () => {

    test("memoLifecycle runs when attaching and detaching", () => {
        GlobalStateManager.reset()
        const state = mutableState(0)
        const root = TestNode.create(() => {
            if (state.value > 0) {
                memoLifecycle(
                    () => collector.push("attach"),
                    () => collector.push("detach")
                )
                collector.push("update")
            }
        })
        testExpected(root)
        state.value = 1
        testExpected(root, "attach", "update")
        state.value = 2
        testExpected(root, "update")
        state.value = 0
        testExpected(root, "detach")
    })

    test("once runs once when attaching to composition", () => {
        GlobalStateManager.reset()
        const state = mutableState(0)
        const root = TestNode.create(() => {
            once(() => collector.push("once" + state.value))
            collector.push("update" + state.value)
        })
        testExpected(root, "once0", "update0")
        state.value = 1
        testExpected(root, "update1")
        state.value = 2
        testExpected(root, "update2")
    })

    test("remember computes once", () => {
        GlobalStateManager.reset()
        const root = TestNode.create(() => {
            remember(() => collector.push("inner"))
            collector.push("outer")
        })
        testExpected(root, "inner", "outer")
    })

    test("remember computes once even if inner state changed", () => {
        GlobalStateManager.reset()
        const state = mutableState(false)
        const root = TestNode.create(() => {
            remember(() => {
                collector.push("inner")
                state.value // not depended
            })
            collector.push("outer")
        })
        testExpected(root, "inner", "outer")
        state.value = true
        testExpected(root)
    })

    test("remember computes once even if outer state changed", () => {
        GlobalStateManager.reset()
        const state = mutableState(false)
        const root = TestNode.create(() => {
            remember(() => collector.push("inner"))
            state.value // depended
            collector.push("outer")
        })
        testExpected(root, "inner", "outer")
        state.value = true
        testExpected(root, "outer")
    })

    test("intrinsic remember should not conflict each other", () => {
        GlobalStateManager.reset()
        const state = mutableState(false)
        const root = TestNode.create(() => {
            state.value
                ? remember(() => collector.push("positive"))
                : remember(() => collector.push("negative"))
        })
        testExpected(root, "negative")
        state.value = true
        testExpected(root, "positive")
        state.value = false
        testExpected(root, "negative")
        state.value = false
        testExpected(root)
    })

    test("rememberDisposable created and disposed accordingly", () => {
        GlobalStateManager.reset()
        const state = mutableState(false)
        const root = TestNode.create(() => {
            if (state.value) {
                rememberDisposable(
                    () => collector.push("create"),
                    () => collector.push("dispose"))
            }
        })
        testExpected(root)
        state.value = true
        testExpected(root, "create")
        state.value = false
        testExpected(root, "dispose")
        state.value = false
        testExpected(root)
    })

    test("rememberMutableState computes once even if initial state changed", () => {
        GlobalStateManager.reset()
        const global = mutableState(0)
        const root = TestNode.create(() => {
            const local = rememberMutableState(global.value)
            collector.push("global=" + global.value)
            collector.push("local=" + local.value)
        })
        testExpected(root, "global=0", "local=0")
        global.value++
        testExpected(root, "global=1", "local=0")
        global.value++
        testExpected(root, "global=2", "local=0")
    })
})
