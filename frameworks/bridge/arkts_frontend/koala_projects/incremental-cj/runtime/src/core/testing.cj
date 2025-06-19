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

import std.collection.*

/** @internal */
let collector = ArrayList<String>()

/** @internal */
func testCollector(array: Array<String>) {
    let actual = collector.toString()
    collector.clear()
    let expected = array.toString()
    if (expected != actual) {
        throw IllegalStateException("expected${expected} != actual${actual}")
    }
}

/** @internal */
func testCollectorAfterCallbacks(expected: Array<String>): Unit {
    testCollector()
    performScheduledCallbacks()
    testCollector(expected)
}

/** @internal */
func testCollectorBeforeCallbacks(expected: Array<String>): Unit {
    testCollector(expected)
    performScheduledCallbacks()
    testCollector()
}

/** @internal */
class TestNode <: IncrementalNode & Equatable<TestNode> {
    TestNode(var content: String) {
        super(0)
    }

    public func toStringBuilder(sb: StringBuilder): Unit {
        sb.append(this.content)
    }

    public operator func ==(that: TestNode): Bool {
        super == that
    }

    public operator func !=(that: TestNode): Bool {
        super != that
    }
}

/** @internal */
func testPrepareOnStart(): Unit {
    GlobalStateManager.reset()
    collector.clear()
}

/** @internal */
func testRoot(content: () -> Unit): ComputableState<TestNode> {
    let root = memoRoot(TestNode("root"), content)
    root.getValue()
    return root
}

/** @internal */
func testTick<Node>(root: State<Node>): Unit where Node <: IncrementalNode {
    performSnapshotUpdating()
    root.getValue()
}

/** @internal */
func testTickWithCallbacks<Node>(root: State<Node>): Unit where Node <: IncrementalNode {
    testTick(root)
    performScheduledCallbacks()
}
