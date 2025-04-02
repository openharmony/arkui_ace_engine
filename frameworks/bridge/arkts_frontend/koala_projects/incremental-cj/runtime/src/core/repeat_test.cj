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
package KoalaRuntime.core

import std.math.*

class Page <: Equatable<Page> {
    let key: CallsiteKey
    Page(private let name: String) {
        key = UInt64(abs(name.hashCode()))
    }
    func page(): Unit {
        rememberDisposable<Unit>({=> collector.append("+" + name)}, {_ => collector.append("-" + name)})
    }
    public operator func ==(that: Page): Bool {
        refEq(this, that)
    }
    public operator func !=(that: Page): Bool {
        !refEq(this, that)
    }
}

func createPages(names: Array<String>): Array<Page> {
    Array<Page>(names.size) {index => Page(names[index])}
}

func testExpected(root: State<TestNode>, expected: Array<String>): Unit {
    testTick(root)
    testCollector(expected)
    if (!expected.isEmpty()) {
        testExpected(root)
    }
}

func testInsert(content: (array: Array<Page>) -> Unit) {
    testPrepareOnStart()
    let state = mutableState(createPages())
    let root = testRoot {
        content(state.getValue())
    }
    testExpected(root)
    state.setValue(createPages("three"))
    testExpected(root, "+three")
    state.setValue(createPages("one", "three"))
    testExpected(root, "+one")
    state.setValue(createPages("one", "three", "five"))
    testExpected(root, "+five")
    state.setValue(createPages("one", "two", "three", "four", "five"))
    testExpected(root, "+two", "+four")
}

func testRemove(content: (array: Array<Page>) -> Unit) {
    testPrepareOnStart()
    let state = mutableState(createPages("one", "two", "three", "four", "five"))
    let root = testRoot {
        content(state.getValue())
    }
    testExpected(root, "+one", "+two", "+three", "+four", "+five")
    state.setValue(createPages("one", "three", "five"))
    testExpected(root, "-two", "-four")
    state.setValue(createPages("three", "five"))
    testExpected(root, "-one")
    state.setValue(createPages("three"))
    testExpected(root, "-five")
    state.setValue(createPages())
    testExpected(root, "-three")
}

func testSwap(content: (array: Array<Page>) -> Unit) {
    testPrepareOnStart()
    let state = mutableState(createPages("one", "two", "three", "four", "five"))
    let root = testRoot {
        content(state.getValue())
    }
    testExpected(root, "+one", "+two", "+three", "+four", "+five")
    state.setValue(createPages("two", "one", "three", "four", "five"))
    testExpected(root, "-one", "+one")
    state.setValue(createPages("two", "four", "one", "three", "five"))
    testExpected(root, "-one", "-three", "+one", "+three")
}

@Test
public class RepeatTest {
    @TestCase
    public func checkRepeat(): Unit {
        testPrepareOnStart()
        let state = mutableState(createPages())
        let root = testRoot {
            Repeat(state.getValue().size, {index => state.getValue()[index].page()})
        }
        testExpected(root)
        state.setValue(createPages("one"))
        testExpected(root, "+one")
        state.setValue(createPages("one", "two", "three"))
        testExpected(root, "+two", "+three")
        state.setValue(createPages("one", "two"))
        testExpected(root, "-three")
        state.setValue(createPages("two"))
        testExpected(root, "-two") // because of index-based key; should be "-one"
        state.setValue(createPages("one", "two"))
        testExpected(root, "+two") // because of index-based key; should be "+one"
    }
    @TestCase
    public func checkRepeatWithKeyInsert(): Unit {
        testInsert {
            array => RepeatWithKey(
                array.size,
                {index => array[index].key},
                {index => array[index].page()}
            )
        }
    }
    @TestCase
    public func checkRepeatByArrayInsert(): Unit {
        testInsert {
            array => RepeatByArray<Page>(
                array,
                {element, index => element.key},
                {element, index => element.page()}
            )
        }
    }
    @TestCase
    public func checkRepeatRangeInsert(): Unit {
        testInsert {
            array => RepeatRange<Page>(
                0,
                array.size,
                {index => array[index]},
                {element, index => element.key},
                {element, index => element.page()}
            )
        }
    }
    @TestCase
    public func checkRepeatWithKeyRemove(): Unit {
        testRemove {
            array => RepeatWithKey(
                array.size,
                {index => array[index].key},
                {index => array[index].page()}
            )
        }
    }
    @TestCase
    public func checkRepeatByArrayRemove(): Unit {
        testRemove {
            array => RepeatByArray<Page>(
                array,
                {element, index => element.key},
                {element, index => element.page()}
            )
        }
    }
    @TestCase
    public func checkRepeatRangeRemove(): Unit {
        testRemove {
            array => RepeatRange<Page>(
                0,
                array.size,
                {index => array[index]},
                {element, index => element.key},
                {element, index => element.page()}
            )
        }
    }
    @TestCase
    public func checkRepeatWithKeySwap(): Unit {
        testSwap {
            array => RepeatWithKey(
                array.size,
                {index => array[index].key},
                {index => array[index].page()}
            )
        }
    }
    @TestCase
    public func checkRepeatByArraySwap(): Unit {
        testSwap {
            array => RepeatByArray<Page>(
                array,
                {element, index => element.key},
                {element, index => element.page()}
            )
        }
    }
    @TestCase
    public func checkRepeatRangeSwap(): Unit {
        testSwap {
            array => RepeatRange<Page>(
                0,
                array.size,
                {index => array[index]},
                {element, index => element.key},
                {element, index => element.page()}
            )
        }
    }
}
