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

import { int32, KoalaCallsiteKey, uint32 } from "@koalaui/common"
import { GlobalStateManager } from "../states/GlobalStateManager"
import { ComputableState, State, StateManager } from "../states/State"
import { IncrementalNode } from "../tree/IncrementalNode"
import { Disposable } from "../states/Disposable"
import { memoRoot } from "./entry"
import { NodeAttach } from "./node"
import { __memo_context_type, __memo_id_type } from "../internals"

/** @internal */
export class TestNode extends IncrementalNode {
    content: string = "<UNDEFINED>"

    constructor(kind: uint32 = 1) {
        super(kind)
    }

    toString(): string {
        return this.content
    }

    static create(
        /** @memo */
        content: (node: TestNode) => void
    ): ComputableState<TestNode> {
        return memoRoot(new TestNode(), content)
    }

    /** @memo:intrinsic */
    static attach(
        /** @memo */
        content: (node: TestNode) => void
    ) {
        NodeAttach(():TestNode => new TestNode(), content)
    }

}

/* parent node that has a Reusable pool */
export class ReusableTestNode extends TestNode {
    constructor() {
        super()
    }

    reusePool = new Map<string, Array<Disposable>>()

    override reuse(reuseKey: string, id: KoalaCallsiteKey): Disposable | undefined {
        if (this.reusePool!.has(reuseKey)) {
            const scopes = this.reusePool!.get(reuseKey)!;
            return scopes.pop();
        }
        return undefined;
    }

    override recycle(reuseKey: string, child: Disposable, id: KoalaCallsiteKey): boolean {
        if (!this.reusePool!.has(reuseKey)) {
            this.reusePool!.set(reuseKey, new Array<Disposable>());
        }
        this.reusePool!.get(reuseKey)!.push(child);
        return true
    }

    override dispose(): void {
        super.dispose()
        for (const scopes of this.reusePool.values()) {
            for (const scope of scopes) {
                scope.dispose()
            }
        }
        this.reusePool.clear()
    }
}

/** @internal */
export function testRoot(
    /** @memo */
    content: (node: TestNode) => void
): State<TestNode> {
    const root = TestNode.create(content)
    root.value
    return root
}

/** @internal */
export function testUpdate(withCallbacks: boolean = true, manager: StateManager = GlobalStateManager.instance): uint32 {
    if (withCallbacks) manager.callCallbacks()
    manager.syncChanges()
    return manager.updateSnapshot()
}

/** @internal */
export function testTick<Node extends IncrementalNode>(root: State<Node>, withCallbacks: boolean = true) {
    testUpdate(withCallbacks)
    root.value
}
