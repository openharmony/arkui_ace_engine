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
    GlobalStateManager,
    State,
    TestNode,
    memoBind,
    testTick,
} from "../../src"

const collector = new Array<string>()

function testExpected(root: State<TestNode>, ...expected: string[]) {
    collector.length = 0
    testTick(root)
    Assert.deepEqual(collector, asArray(expected))
    if (expected.length > 0) testExpected(root)
}

/** @memo */
function sample(arg: string): void {
    collector.push(arg)
}

suite("memo tests", () => {
    test("memoBind trivial test", () => {
        GlobalStateManager.reset()
        const root = TestNode.create((_) => {
            /** @memo */
            const bind = memoBind(sample, "red")
            bind()
        })
        testExpected(root, "red")
    })
})
export const __ARKTEST__ = "memo/bind.test"
