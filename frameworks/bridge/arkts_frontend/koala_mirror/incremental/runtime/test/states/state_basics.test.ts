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
import { uint32 } from "@koalaui/common"
import {
    GlobalStateManager,
    NodeAttach,
    TestNode,
    mutableState,
    testRoot,
    testTick,
} from "../../src"

suite("State management basics", () => {
    test("for loop computes the same id", () => {
        let storage: any[] = []
        let addend = mutableState<number>(0)
        let log: string[] = []

        /** @memo */
        function ui() {
            let addon = addend.value
            for (let i = addon; i < 3 + addon; i++) {
                TestNode.attach((node: TestNode) => {
                    node.content = `${i} ${addon}`
                    log.push(node.content)
                })
            }
        }
        const root = testRoot(ui)

        assert.deepEqual(log, ["0 0", "1 0", "2 0"])

        log = []
        addend.value = 10;
        testTick(root)
        assert.deepEqual(log, [])

        log = []
        addend.value = 200;
        testTick(root)
        assert.deepEqual(log, [])
    })

    test("Function identity is a part of positional key", () => {
        let log: string[] = []

        /** @memo */
        function f1() {
            log.push("f1")
        }

        /** @memo */
        function f2() {
            log.push("f2")
        }

        let f = mutableState(f1)

        /** @memo */
        function ui() {
            /** @memo */
            let y = f.value
            y()
        }

        log = []
        let root = testRoot(ui)
        assert.deepEqual(log, ["f1"])

        log = []
        testTick(root)
        assert.deepEqual(log, [])

        f.value = f2

        log = []
        testTick(root)
        assert.deepEqual(log, ["f2"])

        log = []
        testTick(root)
        assert.deepEqual(log, [])
    })

    test("The same test as above but without __distinct", () => {
        let log: string[] = []

        /** @memo */
        function f1() {
            log.push("f1")
        }
        /** @memo */
        function f2() {
            log.push("f2")
        }
        /** @memo */
        function f3() {
            log.push("f3")
        }

        let sequence = mutableState([f1, f2, f3])

        /** @memo */
        function ui() {
            for (let i = 0; i < 3; i++) {
                /** @memo */
                let f = sequence.value[i]
                f()
            }
        }

        log = []
        const root = testRoot(ui)
        assert.deepEqual(log, ["f1", "f2", "f3"])

        log = []
        testTick(root)
        assert.deepEqual(log, [])

        sequence.value = [f3, f2, f1]

        log = []
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
        assert.deepEqual(log, ["f2", "f1"])

        log = []
        testTick(root)
        assert.deepEqual(log, [])
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

        assert.equal(peekNode, "head")

        testTick(root)

        assert.equal(peekNode, "tail")

        testTick(root)

        assert.equal(peekNode, "head")
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

        assert.equal(peekNode, "head")

        testTick(root)

        assert.equal(peekNode, "head")

        testTick(root)

        assert.equal(peekNode, "head")
    })
    */

    test("Argument change causes recomposition", () => {
        let peekNode = ""
        let peekY: boolean | undefined = undefined
        let peekX: boolean | undefined = undefined
        const y = mutableState(true)

        /** @memo */
        function ui() {
            peekY = y.value
            child(y.value)
        }

        /** @memo */
        function child(x: boolean) {
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
        const root = testRoot(ui)

        assert.equal(peekY, true)
        assert.equal(peekX, true)
        assert.equal(peekNode, "head")
        y.value = !y.value

        testTick(root)

        assert.equal(peekY, false)
        assert.equal(peekX, false)
        assert.equal(peekNode, "tail")
        y.value = !y.value

        testTick(root)

        assert.equal(peekY, true)
        assert.equal(peekX, true)
        assert.equal(peekNode, "head")
    })

    test("Value seen immediately if not in @memo", () => {
        const x = mutableState(true)
        assert.equal(x.value, true)
        x.value = !x.value
        assert.equal(x.value, false)
    })

    test("Value seen later if in @memo", () => {
        GlobalStateManager.instance.frozen = true
        const x = mutableState(true)
        assert.equal(x.value, true)
        x.value = !x.value
        assert.equal(x.value, true)
        GlobalStateManager.instance.frozen = false
    })

    class fooNode extends TestNode {
        constructor(kind: uint32 = 1) {
            super(kind)
        }
    }

    test("Static member @memo", () => {
        const s = mutableState(11)
        const result: Array<number> = []
        class X {
            /** @memo */
            static foo(
                /** @memo */
                content?: () => void
            ) {
                NodeAttach(() => new fooNode(), () => {
                    result.push(s.value)
                    content?.()
                })
            }
        }

        /** @memo */
        function ui() {
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

        assert.deepEqual(result, [11, -1, 17, 41])
    })

    test("Receiver change triggers method recompute", () => {

        class X {
            constructor(public value: number) { }
            /** @memo */
            method(arg?: number) {
                peek.push(this.value)
            }
        }

        const x = mutableState<X>(new X(11))
        const peek: number[] = []

        /** @memo */
        function ui() {
            x.value.method()
        }

        const root = testRoot(ui)
        assert.deepEqual(peek, [11])

        testTick(root)
        assert.deepEqual(peek, [11])

        x.value = new X(22)
        testTick(root)
        assert.deepEqual(peek, [11, 22])

        testTick(root)
        assert.deepEqual(peek, [11, 22])

    })
})
