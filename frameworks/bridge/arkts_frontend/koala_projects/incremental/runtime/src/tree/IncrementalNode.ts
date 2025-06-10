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

import { className, uint32 } from "@koalaui/common"
import { Disposable } from "../states/Disposable"
import { ReadonlyTreeNode } from "./ReadonlyTreeNode"

/**
 * This is a node implementation for a tree, which is represented as a pair of bidirectional lists.
 * It allows nodes to be added or removed incrementally using the state manager.
 */
export class IncrementalNode implements Disposable, ReadonlyTreeNode {
    private _disposed = false
    private _child: IncrementalNode | undefined = undefined
    private _prev: IncrementalNode | undefined = undefined
    private _next: IncrementalNode | undefined = undefined
    private _parent: IncrementalNode | undefined = undefined
    private _incremental: IncrementalNode | undefined = undefined

    /**
     * This callback is called when a child node is added to this parent.
     */
    protected onChildInserted: ((node: IncrementalNode) => void) | undefined = undefined

    /**
     * This callback is called when a child node is removed from this parent.
     */
    protected onChildRemoved: ((node: IncrementalNode) => void) | undefined = undefined

    /**
     * This kind can be used to distinguish nodes.
     * @see isKind
     */
    readonly kind: uint32

    /**
     * @param kind - the kind of this instance
     * @see PrimeNumbers
     */
    constructor(kind: uint32 = 1) {
        this.kind = kind
    }

    /**
     * Use this method instead of standard instanceof for the sake of speed and reliability.
     * @param kind - a kind of this or parent instance to check against
     * @returns `true` if this node is an instance of the expected kind
     * @see PrimeNumbers
     */
    isKind(kind: uint32): boolean {
        return this.kind % kind == 0
    }

    /**
     * Reuse a scope from the pool.
     * @param reuseKey - The type of the scope to reuse.
     * @returns A recycled scope, or undefined if none is available.
     */
    reuse(reuseKey: string): Disposable | undefined {
        return undefined
    }

    /**
     * Recycle a scope by adding it to the recycler pool for reuse.
     * @param scope - The scope to recycle.
     * @param reuseKey - The type of the scope (used as the key in the pool).
     * @return true if child is successfully recycled
     */
    recycle(reuseKey: string, child: Disposable): boolean {
        return false
    }

    /**
     * @returns `true` if this node should no longer be used
     */
    get disposed(): boolean {
        return this._disposed
    }

    /**
     * This method is called to remove this node from the hierarchy and cleanup related resources.
     */
    dispose(): void {
        if (this._disposed) return
        this._disposed = true
        this.detach()
    }

    /**
     * This method is called to remove this node from the hierarchy.
     * @internal
     */
    detach(): void {
        const prev = this._prev
        const next = this._next
        const parent = this._parent
        if (prev) {
            this._prev = undefined
            prev._next = next
        }
        if (next) {
            this._next = undefined
            next._prev = prev
        }
        if (parent) {
            this._parent = undefined
            if (parent._child === this) {
                parent._child = next
            }
            parent.onChildRemoved?.(this)
        }
    }

    /**
     * @returns a parent node if it is exist
     */
    get parent(): IncrementalNode | undefined {
        return this._parent
    }

    /**
     * @returns text representation of the node
     */
    toString(): string {
        return className(this) + ": " + this.kind
    }

    /**
     * @returns text representation of a tree hierarchy starting from this node
     */
    toHierarchy(): string {
        let str = ""
        for (let node = this._parent; node; node = node!._parent) str += "  "
        str += this.toString()
        for (let node = this._child; node; node = node!._next) str += "\n" + node!.toHierarchy()
        return str
    }

    /**
     * @returns the first child node contained in this node if it is exist
     */
    get firstChild(): IncrementalNode | undefined {
        return this._child
    }

    /**
     * @returns the next sibling of this node if it is exist
     */
    get nextSibling(): IncrementalNode | undefined {
        return this._next
    }

    /**
     * @returns the previous sibling of this node if it is exist
     */
    get previousSibling(): IncrementalNode | undefined {
        return this._prev
    }

    /**
     * This method is called by the state manager
     * when the incremental update should skip several unchanged child nodes.
     * @param count - a number of child nodes to skip during the incremental update
     * @internal
     */
    incrementalUpdateSkip(count: uint32) {
        if (count > 0) {
            const prev = this._incremental
            let next = prev ? prev._next : this._child
            while (1 < count--) {
                if (next === undefined) throw new Error("child node is expected here")
                next = next._next
            }
            this._incremental = next
        }
        else throw new Error("unexpected count of child nodes to skip: " + count)
    }

    /**
     * This method is called by the state manager
     * when the incremental update of all children of this node is completed.
     * @internal
     */
    incrementalUpdateDone(parent?: IncrementalNode) {
        if (this._disposed) throw new Error("child node is already disposed")
        this._incremental = undefined
        if (parent) {
            const prev = parent._incremental
            const next = prev ? prev._next : parent._child
            if (this._parent) {
                if (this._parent != parent) throw new Error("child node belongs to another parent")
                if (this != next) throw new Error("child node is not expected here")
                parent._incremental = this
            } else {
                parent._incremental = this
                this._prev = prev
                this._next = next
                this._parent = parent
                if (next) next._prev = this
                if (prev) prev._next = this
                else parent._child = this
                parent.onChildInserted?.(this)
            }
        }
    }
}
