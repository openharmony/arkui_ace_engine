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
    OnChange,
    RunEffect,
    State,
    TestNode,
    mutableState,
    testTick,
} from "../../src"

const collector = new Array<string>()

function testExpected(root: State<TestNode>, ...expected: string[]) {
    collector.length = 0
    testTick(root, false)
    assert.deepEqual(collector, [])
    GlobalStateManager.instance.callCallbacks()
    assert.deepEqual(collector, expected)
}

export function testChange(
    /** @memo */
    content: (value: string) => void,
    ...expected: string[]
) {
    GlobalStateManager.reset()
    const state = mutableState("first")
    const root = TestNode.create(() => content(state.value))
    testExpected(root, ...expected)
    state.value = "f" + "i" + "r" + "s" + "t"
    testExpected(root)
    state.value = "second"
    testExpected(root, "second")
    state.value = "third"
    testExpected(root, "third")
}

suite("changeListener tests", () => {

    test("RunEffect", () => testChange((value: string) => RunEffect(value, change => collector.push(change)), "first"))

    test("OnChange", () => testChange((value: string) => OnChange(value, change => collector.push(change))))
})
