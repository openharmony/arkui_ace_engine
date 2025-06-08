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

// TODO: the real chai exports 'assert', but 'assert' is still a keyword in ArkTS
import { Assert, suite, test } from "@koalaui/harness"
import { asArray } from "@koalaui/common"
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
    testTick<TestNode>(root)
    Assert.deepEqual(collector, asArray(expected))
    if (expected.length > 0) testExpected(root)
}

suite("contextLocal tests", () => {

    test("contextLocalScope ensures name is not changed", () => {
        const state = mutableState<string>("first")
        const root = TestNode.create((node) => {
            contextLocalScope<string>(state.value, "value", () => {
                collector.push(contextLocalValue<string>(state.value))
            })
        })
        testExpected(root, "value")
        state.value = "second"
        Assert.throws(() => { testTick<TestNode>(root) })
    })

    test("contextLocalScope propagates state immediately", () => {
        const state = mutableState<string>("first")
        const root = TestNode.create((node) => {
            const str = state.value
            collector.push("ui:" + str)
            contextLocalScope<string>("parameter", state.value, () => {
                collector.push("state:" + contextLocalValue<string>("parameter"))
            })
        })
        testExpected(root, "ui:first", "state:first")
        state.value = "second"
        testExpected(root, "ui:second", "state:second")
        state.value = "third"
        testExpected(root, "ui:third", "state:third")
    })
})
export const __ARKTEST__ = "memo/contextLocal.test"
