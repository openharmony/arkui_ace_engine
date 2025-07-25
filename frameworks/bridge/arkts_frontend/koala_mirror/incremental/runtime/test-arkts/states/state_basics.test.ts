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
import { asArray, int32, uint32 } from "@koalaui/common"
import {
    GlobalStateManager,
    NodeAttach,
    TestNode,
    mutableState,
    testRoot,
    testTick,
} from "../../src"

function assertResultArray<T>(actual: Array<T>, ...expected: T[]) {
    Assert.deepEqual(actual, asArray(expected))
}

suite("State management basics", () => {
    test("for loop computes the same id", () => {
        let addend = mutableState<int32>(0)
        let log = new Array<string>()

        const ui =
        /** @memo */
        (node: TestNode): void => {
            let addon = addend.value
            for (let i = addon; i < 3 + addon; i++) {
                TestNode.attach((node: TestNode) => {
                    node.content = `${i} ${addon}`
                    log.push(node.content)
                })
            }
        }
        const root = testRoot(ui)

        assertResultArray(log, "0 0", "1 0", "2 0")

        log = new Array<string>()
        addend.value = 10;
        testTick(root)
        assertResultArray(log)

        log = new Array<string>()
        addend.value = 200;
        testTick(root)
        assertResultArray(log)
    })

    test("Function identity is a part of positional key", () => {
        let log = new Array<string>()

        const f1 =
        /** @memo */
        (): void => {
            log.push("f1")
        }

        const f2 =
        /** @memo */
        (): void => {
            log.push("f2")
        }

        let f = mutableState(f1)

        const ui =
        /** @memo */
        (node: TestNode): void => {
            /** @memo */
            let y = f.value
            y()
        }

        log = new Array<string>()
        let root = testRoot(ui)
        assertResultArray(log, "f1")

        log = new Array<string>()
        testTick(root)
        assertResultArray(log)

        f.value = f2

        log = new Array<string>()
        testTick(root)
        assertResultArray(log, "f2")

        log = new Array<string>()
        testTick(root)
        assertResultArray(log)
    })

    test("The same test as above but without __distinct", () => {
        let log = new Array<string>()

        const f1 =
        /** @memo */
        (): void => {
            log.push("f1")
        }
        const f2 =
        /** @memo */
        (): void => {
            log.push("f2")
        }
        const f3 =
        /** @memo */
        (): void => {
            log.push("f3")
        }

        let sequence = mutableState(asArray([f1, f2, f3]))

        const ui =
        /** @memo */
        (node: TestNode): void => {
            for (let i = 0; i < 3; i++) {
                /** @memo */
                let f = sequence.value[i]
                f()
            }
        }

        log = new Array<string>()
        const root = testRoot(ui)
        assertResultArray(log, "f1", "f2", "f3")

        log = new Array<string>()
        testTick(root)
        assertResultArray(log)

        sequence.value = asArray([f3, f2, f1])

        log = new Array<string>()
        testTick(root)
        // Compare this test with the previous one
        // Without distinct we just compare the subsequent iterations.
        //
        // f1 first time
        // f2 recomputes
        // f3 recomputes
        //
        // f3 the same!
        // f2 recomputes
        // f1 recomputes
        assertResultArray(log, "f2", "f1")

        log = new Array<string>()
        testTick(root)
        assertResultArray(log)
    })

    /*
     These two tests are no longer relevant, as we forbid state mutations in UI functions.

    test("mutable state dereference causes recomputes", () => {
        let peekNode = ""

        // @memo
        function ui() {
            const x = remember(() => mutableState(true))
            StringNode(node => {
                if (x.value) {
                    node.content = "head"
                } else {
                    node.content = "tail"
                }
                peekNode = node.content
            })
            x.value = !x.value
        }

        const root = testRoot(ui)

        Assert.equal(peekNode, "head")

        testTick(root)

        Assert.equal(peekNode, "tail")

        testTick(root)

        Assert.equal(peekNode, "head")
    })

    test("mutable state dereference doesn't affect nested scopes", () => {
        let peekNode = ""

        // @memo
        function ui() {
            const x = remember(() => mutableState(true))

            const y = x.value

            StringNode(node => {
                if (y) {
                    node.content = "head"
                } else {
                    node.content = "tail"
                }
                peekNode = node.content
            })
            x.value = !x.value
        }
        const root = testRoot(ui)

        Assert.equal(peekNode, "head")

        testTick(root)

        Assert.equal(peekNode, "head")

        testTick(root)

        Assert.equal(peekNode, "head")
    })
    */

    test("Argument change causes recomposition", () => {
        let peekNode = ""
        let peekY: boolean | undefined = undefined
        let peekX: boolean | undefined = undefined
        const y = mutableState(true)

        /** @memo */
        const child =
        /** @memo */
        (x: boolean): void => {
            peekX = x
            TestNode.attach((node: TestNode) => {
                if (x) {
                    node.content = "head"
                } else {
                    node.content = "tail"
                }
                peekNode = node.content
            })
        }

        const ui =
        /** @memo */
        (node: TestNode): void => {
            peekY = y.value
            child(y.value)
        }

        const root = testRoot(ui)

        Assert.equal<boolean | undefined>(peekY, true)
        Assert.equal<boolean | undefined>(peekX, true)
        Assert.equal(peekNode, "head")
        y.value = !y.value

        testTick(root)

        Assert.equal<boolean | undefined>(peekY, false)
        Assert.equal<boolean | undefined>(peekX, false)
        Assert.equal(peekNode, "tail")
        y.value = !y.value

        testTick(root)

        Assert.equal<boolean | undefined>(peekY, true)
        Assert.equal<boolean | undefined>(peekX, true)
        Assert.equal(peekNode, "head")
    })

    test("Value seen immediately if not in @memo", () => {
        const x = mutableState(true)
        Assert.equal(x.value, true)
        x.value = !x.value
        Assert.equal(x.value, false)
    })

    test("Value seen later if in @memo", () => {
        GlobalStateManager.instance.frozen = true
        const x = mutableState(true)
        Assert.equal(x.value, true)
        x.value = !x.value
        Assert.equal(x.value, true)
        GlobalStateManager.instance.frozen = false
    })

    class fooNode extends TestNode {
        constructor(kind: uint32 = 1) {
            super(kind)
        }
    }

    test("Static member @memo", () => {
        const s = mutableState<int32>(11)
        const result = new Array<int32>()
        class X {
            /** @memo */
            static foo(
                /** @memo */
                content?: () => void
            ) {
                NodeAttach<TestNode>((): TestNode => new fooNode(), (_: TestNode) => {
                    result.push(s.value)
                    content?.()
                })
            }
        }

        const ui =
        /** @memo */
        (node: TestNode): void => {
            X.foo(() => {
                result.push(-1)
            })
        }

        const root = testRoot(ui)
        testTick(root)
        testTick(root)
        s.value = 17
        testTick(root)
        testTick(root)
        s.value = 41
        testTick(root)
        testTick(root)

        assertResultArray(result, 11, -1, 17, 41)
    })

    test("Receiver change triggers method recompute", () => {

        const peek = new Array<int32>()
        class X {
            value: int32
            constructor(value: int32) {
                this.value = value
            }
            /** @memo */
            method(arg?: int32) {
                peek.push(this.value)
            }
        }

        const x = mutableState<X>(new X(11))

        const ui =
        /** @memo */
        (node: TestNode): void => {
            x.value.method()
        }

        const root = testRoot(ui)
        assertResultArray(peek, 11)

        testTick(root)
        assertResultArray(peek, 11)

        x.value = new X(22)
        testTick(root)
        assertResultArray(peek, 11, 22)

        testTick(root)
        assertResultArray(peek, 11, 22)

    })
})
export const __ARKTEST__ = "states/state_basics.test"
