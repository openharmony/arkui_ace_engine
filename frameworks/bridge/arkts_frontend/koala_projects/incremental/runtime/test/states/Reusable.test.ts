/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { TestNode, ReusableTestNode, testUpdate, memoEntry, __id } from "../../src"
import { createStateManager, InternalScope } from "../../src/states/State"
import { assertNode } from "./State.test"
suite("State", () => {
    test("reuse nodes basic", () => {
        const manager = createStateManager()
        const changed = manager.mutableState(false)

        let reusedScope: InternalScope<void>
        const rootNode = new ReusableTestNode(); rootNode.content = "root"
        const root = manager.updatableNode(rootNode, context => {
            assert.equal(rootNode, context.node)
            if (!changed.value) {
                reusedScope =
                    context.scope(5, 0, () => { const node = new TestNode(); node.content = "first node"; return node }, undefined, undefined, undefined, "reuse")
                if (!reusedScope.unchanged)
                    reusedScope.recache()
                const scope = context.scope(6, 0, () => { const node = new TestNode(); node.content = "second node"; return node }, undefined, undefined, undefined, "reuse")
                if (!scope.unchanged)
                    scope.recache()
            } else {
                const scope3 = context.scope(6, 0, () => { const node = new TestNode(); node.content = "third node"; return node }, undefined, undefined, undefined, "reuse")
                if (!scope3.unchanged)
                    scope3.recache()
                let scope4 = context.scope(7, 0, () => { const node = new TestNode(); node.content = "fourth node"; return node }, undefined, undefined, undefined, "reuse")
                assert.equal(reusedScope, scope4)
                if (!scope4.unchanged)
                    scope4.recache()
            }
        })
        assertNode(root,
            "root\n" +
            "  first node\n" +
            "  second node")
        changed.value = true
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  second node\n" +
            "  first node")
    })

    test("reuse nodes after disposing all", () => {
        const manager = createStateManager()
        const phase = manager.mutableState(0)

        let reusedScope1: InternalScope<void>
        let reusedScope2: InternalScope<void>
        const rootNode = new ReusableTestNode(); rootNode.content = "root"
        const root = manager.updatableNode(rootNode, context => {
            assert.equal(rootNode, context.node)
            if (phase.value == 0) {
                reusedScope1 =
                    context.scope(5, 0, () => { const node = new TestNode(); node.content = "first node"; return node }, undefined, undefined, undefined, "reuse")
                if (!reusedScope1.unchanged)
                    reusedScope1.recache()
                reusedScope2 = context.scope(6, 0, () => { const node = new TestNode(); node.content = "second node"; return node }, undefined, undefined, undefined, "reuse")
                if (!reusedScope2.unchanged)
                    reusedScope2.recache()
            } else if (phase.value == 1) {
                // remove all
            } else {
                const scope3 = context.scope(8, 0, () => new TestNode(), undefined, undefined, undefined, "reuse")
                assert.equal(reusedScope2, scope3)
                if (!scope3.unchanged)
                    scope3.recache()
                const scope4 = context.scope(9, 0, () => new TestNode(), undefined, undefined, undefined, "reuse")
                assert.equal(reusedScope1, scope4)
                if (!scope4.unchanged)
                    scope4.recache()
                // scope 5 is brand new
                const scope5 = context.scope(10, 0, () => new TestNode(), undefined, undefined, undefined, "reuse")
                if (!scope5.unchanged)
                    scope5.recache()
            }
        })
        assertNode(root,
            "root\n" +
            "  first node\n" +
            "  second node")
        ++phase.value
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root, "root")
        ++phase.value
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  second node\n" +
            "  first node\n" +
            "  <UNDEFINED>")
    })

    test("dispose root", () => {
        const manager = createStateManager()

        const rootNode = new ReusableTestNode(); rootNode.content = "root"
        const firstNode = new TestNode(); firstNode.content = "first node";
        const secondNode = new TestNode(); secondNode.content = "second node";
        const root = manager.updatableNode(rootNode, context => {
            assert.equal(rootNode, context.node)
            const scope1 =
                context.scope(5, 0, () => firstNode, undefined, undefined, undefined, "reuse")
            if (!scope1.unchanged)
                scope1.recache()
            const scope2 = context.scope(6, 0, () => secondNode, undefined, undefined, undefined, "reuse")
            if (!scope2.unchanged)
                scope2.recache()
        })
        assertNode(root,
            "root\n" +
            "  first node\n" +
            "  second node")
        root.dispose()
        assert(root.disposed)
        assert(firstNode.disposed)
        assert(secondNode.disposed)
    })

    test("reuse nested", () => {
        const manager = createStateManager()
        const version = manager.mutableState(0)

        let reusedScope: InternalScope<void>
        const rootNode = new ReusableTestNode(); rootNode.content = "root"
        const root = manager.updatableNode(rootNode, context => {
            assert.equal(rootNode, context.node)
            if (version.value == 0) {
                memoEntry(context, 2, () => {
                    reusedScope =
                        context.scope(5, 0, () => { const node = new TestNode(); node.content = "first node"; return node }, undefined, undefined, undefined, "reuse")
                    if (!reusedScope.unchanged)
                        reusedScope.recache()
                })
                memoEntry(context, 3, () => {
                    const scope = context.scope(6, 0, () => { const node = new TestNode(); node.content = "second node"; return node }, undefined, undefined, undefined, "reuse")
                    if (!scope.unchanged)
                        scope.recache()
                })
            } else if (version.value == 1) {
                // remove all
            } else {
                let id = 0
                memoEntry(context, 3, () => {
                    id = __id()
                    console.log(`scope3`)
                    const scope3 = context.scope(6, 0, () => { const node = new TestNode(); node.content = "third node"; return node }, undefined, undefined, undefined, "reuse")
                    if (!scope3.unchanged) {
                        // assert.equal(__id(), 0)
                        scope3.recache()
                    }
                })
                console.log(`after scope 3`)
                memoEntry(context, 0, () => {
                    assert.equal(__id(), id - 3)
                    console.log(`scope4`)
                    let scope4 = context.scope(7, 0, () => { const node = new TestNode(); node.content = "fourth node"; return node }, undefined, undefined, undefined, "reuse")
                    assert.equal(reusedScope, scope4)
                    if (!scope4.unchanged)
                        scope4.recache()
                })
            }
        })
        assertNode(root,
            "root\n" +
            "  first node\n" +
            "  second node")
        version.value++
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root, "root")
        version.value++
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  second node\n" +
            "  first node")
    })
}
)