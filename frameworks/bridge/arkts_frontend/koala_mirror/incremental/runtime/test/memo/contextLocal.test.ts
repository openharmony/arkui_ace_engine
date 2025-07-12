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
    State,
    TestNode,
    contextLocalScope,
    contextLocalValue,
    mutableState,
    testTick,
} from "../../src"

const collector = new Array<string>()

function testExpected(root: State<TestNode>, ...expected: string[]) {
    collector.length = 0
    testTick(root)
    assert.deepEqual(collector, expected)
    if (expected.length > 0) testExpected(root)
}

suite("contextLocal tests", () => {

    test("contextLocalScope ensures name is not changed", () => {
        const state = mutableState("first")
        const root = TestNode.create(() => {
            contextLocalScope(state.value, "value", () => {
                collector.push(contextLocalValue(state.value))
            })
        })
        testExpected(root, "value")
        state.value = "second"
        assert.throws(() => testTick(root))
    })

    test("contextLocalScope propagates state immediately", () => {
        const state = mutableState("first")
        const root = TestNode.create(() => {
            collector.push("ui:" + state.value)
            contextLocalScope("parameter", state.value, () => {
                collector.push("state:" + contextLocalValue("parameter"))
            })
        })
        testExpected(root, "ui:first", "state:first")
        state.value = "second"
        testExpected(root, "ui:second", "state:second")
        state.value = "third"
        testExpected(root, "ui:third", "state:third")
    })
})
