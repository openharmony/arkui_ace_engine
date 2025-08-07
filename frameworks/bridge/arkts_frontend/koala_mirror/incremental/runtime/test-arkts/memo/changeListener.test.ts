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

import { assert, suite, test } from "@koalaui/harness"
import {
    GlobalStateManager,
    OnChange,
    RunEffect,
    State,
    TestNode,
    mutableState,
    testTick,
} from "../../ets"

const collector = new Array<string>()

function testExpected(root: State<TestNode>, expected?: string) {
    collector.length = 0
    testTick(root, false)
    assert.equal(collector.length, 0)
    GlobalStateManager.instance.callCallbacks()
    if (expected === undefined) {
        assert.equal(collector.length, 0)
    } else {
        assert.equal(collector.length, 1)
        assert.equal(collector[0], expected)
    }
}

export function testChange(
    /** @memo */
    content: (value: string) => void,
    expected?: string
) {
    GlobalStateManager.reset()
    const state = mutableState<string>("first")
    const root = TestNode.create((node): void => { content(state.value) })
    testExpected(root, expected)
    state.value = "f" + "i" + "r" + "s" + "t"
    testExpected(root)
    state.value = "second"
    testExpected(root, "second")
    state.value = "third"
    testExpected(root, "third")
}

suite("changeListener tests", () => {

    test("RunEffect", () => { testChange((value: string): void => { RunEffect(value, (change: string): void => { collector.push(change) }) }, "first") })

    test("OnChange", () => { testChange((value: string): void => { OnChange(value, (change: string): void => { collector.push(change) }) }) })
})
export const __ARKTEST__ = "memo/changeListeners.test"
