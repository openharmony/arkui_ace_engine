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
import { asArray, int32, KoalaCallsiteKey } from "@koalaui/common"
import {
    GlobalStateManager,
    Repeat,
    RepeatByArray,
    RepeatRange,
    RepeatWithKey,
    State,
    TestNode,
    memoLifecycle,
    mutableState,
    testTick,
} from "../../src"

// For tests we compute positional ids from strings.
export function key(name: string): KoalaCallsiteKey {
    let key: KoalaCallsiteKey = 0
    for (let i = 0; i < name.length; i++) {
        key = (key << 3) | (key >> 29) ^ (name[i] as int32)
    }
    return key
}

const collector = new Array<string>()

class Page {
    readonly id: KoalaCallsiteKey
    private readonly name: string
    constructor(name: string) {
        this.id = key(name)
        this.name = name
    }
    /** @memo */
    page(): void {
        memoLifecycle(
            () => { collector.push("+" + this.name) },
            () => { collector.push("-" + this.name) })
    }
}

function createPages(...names: string[]): ReadonlyArray<Page> {
    return asArray(names).map((name: string) => new Page(name))
}

function testExpected(root: State<TestNode>, ...expected: string[]) {
    collector.length = 0
    testTick(root)
    Assert.deepEqual(collector, asArray(expected))
    if (expected.length > 0) testExpected(root)
}

function testInsert(
    /** @memo */
    content: (array: ReadonlyArray<Page>) => void
) {
    GlobalStateManager.reset()
    const state = mutableState(createPages())
    const root = TestNode.create((_) => { content(state.value) })
    testExpected(root)
    state.value = createPages("three")
    testExpected(root, "+three")
    state.value = createPages("one", "three")
    testExpected(root, "+one")
    state.value = createPages("one", "three", "five")
    testExpected(root, "+five")
    state.value = createPages("one", "two", "three", "four", "five")
    testExpected(root, "+two", "+four")
}

function testRemove(
    /** @memo */
    content: (array: ReadonlyArray<Page>) => void
) {
    GlobalStateManager.reset()
    const state = mutableState(createPages("one", "two", "three", "four", "five"))
    const root = TestNode.create((_) => { content(state.value) })
    testExpected(root, "+one", "+two", "+three", "+four", "+five")
    state.value = createPages("one", "three", "five")
    testExpected(root, "-two", "-four")
    state.value = createPages("three", "five")
    testExpected(root, "-one")
    state.value = createPages("three")
    testExpected(root, "-five")
    state.value = createPages()
    testExpected(root, "-three")
}

function testSwap(
    /** @memo */
    content: (array: ReadonlyArray<Page>) => void
) {
    GlobalStateManager.reset()
    const state = mutableState(createPages("one", "two", "three", "four", "five"))
    const root = TestNode.create((_) => { content(state.value) })
    testExpected(root, "+one", "+two", "+three", "+four", "+five")
    state.value = createPages("two", "one", "three", "four", "five")
    testExpected(root, "-one", "+one")
    state.value = createPages("two", "four", "one", "three", "five")
    testExpected(root, "-one", "-three", "+one", "+three")
}

suite("repeat tests", () => {

    test("Repeat", () => {
        GlobalStateManager.reset()
        const state = mutableState(createPages())
        const root = TestNode.create((_) => {
            Repeat(state.value.length as int32, (index: int32) => {
                state.value[index].page() // index-based key
            })
        })
        testExpected(root)
        state.value = createPages("one")
        testExpected(root, "+one")
        state.value = createPages("one", "two", "three")
        testExpected(root, "+two", "+three")
        state.value = createPages("one", "two")
        testExpected(root, "-three")
        state.value = createPages("two")
        testExpected(root, "-two") // because of index-based key; should be "-one"
        state.value = createPages("one", "two")
        testExpected(root, "+two") // because of index-based key; should be "+one"
    })


    test("RepeatWithKey.insert", () => {
        testInsert((array) => {
            RepeatWithKey(
                array.length as int32,
                (index: int32) => array[index].id,
                (index: int32) => { array[index].page() })
        })
    })

    test("RepeatByArray.insert", () => {
        testInsert((array) => {
            RepeatByArray<Page>(
                array,
                (element: Page, _: int32) => element.id,
                (element: Page, _: int32) => { element.page() })
        })
    })

    test("RepeatRange.insert", () => {
        testInsert((array) => {
            RepeatRange(
                0,
                array.length as int32,
                (index: int32) => array[index],
                (element: Page, _: int32) => element.id,
                (element: Page, _: int32) => { element.page() })
        })
    })


    test("RepeatWithKey.remove", () => {
        testRemove((array) => {
            RepeatWithKey(
                array.length as int32,
                (index: int32) => array[index].id,
                (index: int32) => { array[index].page() })
        })
    })

    test("RepeatByArray.remove", () => {
        testRemove((array) => {
            RepeatByArray(
                array,
                (element: Page, _: int32) => element.id,
                (element: Page, _: int32) => { element.page() })
        })
    })

    test("RepeatRange.remove", () => {
        testRemove((array) => {
            RepeatRange(
                0,
                array.length as int32,
                (index: int32) => array[index],
                (element: Page, _: int32) => element.id,
                (element: Page, _: int32) => { element.page() })
        })
    })


    test("RepeatWithKey.swap", () => {
        testSwap((array) => {
            RepeatWithKey(
                array.length as int32,
                (index: int32) => array[index].id,
                (index: int32) => { array[index].page() })
        })
    })

    test("RepeatByArray.swap", () => {
        testSwap((array) => {
            RepeatByArray(
                array,
                (element: Page, _: int32) => element.id,
                (element: Page, _: int32) => { element.page() })
        })
    })

    test("RepeatRange.swap", () => {
        testSwap((array) => {
            RepeatRange(
                0,
                array.length as int32,
                (index: int32) => array[index],
                (element: Page, _: int32) => element.id,
                (element: Page, _: int32) => { element.page() })
        })
    })
})
export const __ARKTEST__ = "memo/repeat.test"
