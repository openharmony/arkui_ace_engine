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

import { className, float64, float64ToInt, int32, uint32 } from "@koalaui/common"
import { RuntimeProfiler } from "../common/RuntimeProfiler"
import { Disposable } from "../states/Disposable"
import { ReadonlyTreeNode } from "./ReadonlyTreeNode"

/**
 * A tree node used to build an incremental runtime and a component tree.
 */
export class TreeNode implements Disposable, ReadonlyTreeNode {
    private myIndex: int32 = -1
    private myParent: TreeNode | undefined = undefined
    private myChildren = new Array<TreeNode>()
    private myIndicesValid: boolean = true
    private myDisposed: boolean = false

    readonly kind: uint32

    protected onChildInserted: ((node: TreeNode, index: int32) => void) | undefined
    protected onChildRemoved: ((node: TreeNode, index: int32) => void) | undefined

    constructor(kind: uint32 = 1) {
        this.kind = kind
        RuntimeProfiler.nodeCreated(this.kind, this)
        RuntimeProfiler.instance?.node()
    }

    get disposed(): boolean {
        return this.myDisposed
    }

    /**
     * This method may be called to notify this node that it
     * is completely removed from the hierarchy and is no longer in use.
     */
    dispose(): void {
        this.myDisposed = true
        RuntimeProfiler.nodeDisposed(this.kind, this)
    }

    /**
     * Returns the parent node.
     */
    get parent(): TreeNode | undefined {
        return this.myParent
    }

    /**
     * Returns the depth of this node relative to the root node.
     * The root node returns 0.
     */
    get depth(): uint32 {
        let count: uint32 = 0
        let parent = this.myParent
        while (parent !== undefined) {
            parent = parent!.myParent
            count++
        }
        return count
    }

    /**
     * Returns the number of children of this node.
     */
    get childrenCount(): uint32 {
        return float64ToInt(this.myChildren.length)
    }

    /**
     * Returns all children of this node.
     * Note that this array is updated automatically.
     */
    get children(): ReadonlyArray<TreeNode> {
        return this.myChildren
    }

    /**
     * Returns the index of this node in the parent's children.
     * The root node returns -1.
     */
    get index(): int32 {
        const parent = this.myParent
        if (parent?.myIndicesValid == false) {
            parent!.myIndicesValid = true
            // recalculate indices of all children
            const children = parent!.myChildren
            const length = children.length
            for (let i = 0; i < length; i++) {
                children[i].myIndex = i
            }
        }
        return this.myIndex
    }

    /**
     * @internal
     *
     * Use this method instead of standard instanceof for the sake of speed and reliability.
     * @param kind - kind id of this or parent instance to check against.
     * @returns true if this TreeNode is instance of given kind.
     */
    isKind(kind: uint32): boolean {
        return this.kind % kind == 0
    }

    /**
     * Iterates through the child nodes and returns the first defined value.
     */
    find<V>(valueOf: (node: TreeNode, index: int32) => V | undefined): V | undefined {
        const children = this.myChildren
        const length = children.length
        for (let i = 0; i < length; i++) {
            let value = valueOf(children[i], i)
            if (value !== undefined) return value
        }
        return undefined
    }

    /**
     * Performs the specified action for each child node.
     */
    forEach(action: (node: TreeNode, index: float64) => void): void {
        // must be int32, but ArkTS array.forEach requires index to be float64
        this.myChildren.forEach(action)
    }

    /**
     * Determines whether all child nodes satisfy the specified predicate.
     */
    every(predicate: (node: TreeNode, index: float64) => boolean): boolean {
        // must be int32, but ArkTS array.every requires index to be float64
        return this.myChildren.every(predicate)
    }

    /**
     * Determines whether any child node satisfies the specified predicate.
     */
    some(predicate: (node: TreeNode, index: float64) => boolean): boolean {
        // must be int32, but ArkTS array.some requires index to be float64
        return this.myChildren.some(predicate)
    }

    /**
     * Returns a child node at the specified index.
     */
    childAt(index: int32): TreeNode | undefined {
        if (!this.accessible(index)) return undefined // index out of bounds
        return this.myChildren[index]
    }

    /**
     * Adds the given node after existing children if possible.
     */
    appendChild(node: TreeNode): boolean {
        return this.insertChildAt(this.childrenCount, node)
    }

    /**
     * Inserts the given node at the specified index if possible.
     */
    insertChildAt(index: int32, node: TreeNode): boolean {
        if (!this.accessible(index, 0)) return false // index out of bounds
        if (!this.insertable(node)) return false // cannot be inserted
        this.insertNodeAt(index, node)
        return true
    }

    /**
     * Adds several nodes after existing children if possible.
     */
    appendChildren(...nodes: TreeNode[]): boolean {
        return this.insertChildrenAt(this.childrenCount, ...nodes)
    }

    /**
     * Inserts several nodes at the specified index if possible.
     */
    insertChildrenAt(index: int32, ...nodes: TreeNode[]): boolean {
        if (!this.accessible(index, 0)) return false // index out of bounds
        if (nodes.length < 1) return false // nothing to insert
        const length = nodes.length
        for (let i = 0; i < length; i++) {
            if (!this.insertable(nodes[i])) return false // cannot be inserted
        }
        for (let i = 0; i < length; i++) {
            this.insertNodeAt(index + i, nodes[i])
        }
        return true
    }

    /**
     * Removes a child node at the specified index if possible.
     */
    removeChildAt(index: int32): TreeNode | undefined {
        if (!this.accessible(index)) return undefined // index out of bounds
        return this.removeNodes(index, 1)[0]
    }

    /**
     * Removes several nodes at the specified index if possible.
     */
    removeChildrenAt(index: int32, count?: uint32): Array<TreeNode> {
        if (count === undefined) count = this.childrenCount - index
        if (count < 1 || !this.accessible(index, count)) return new Array<TreeNode>() // index out of bounds
        return this.removeNodes(index, count)
    }

    /**
     * Removes a child node if possible.
     */
    removeChild(node: TreeNode): boolean {
        if (node.myParent !== this) return false // not in hierarchy
        const index: int32 = this.myIndicesValid ? node.index : float64ToInt(this.myChildren.indexOf(node))
        return undefined !== this.removeChildAt(index)
    }

    /**
     * Removes this node from its parent.
     */
    removeFromParent(): void {
        this.myParent?.removeChild(this)
    }

    private removeNodes(index: int32, count: uint32): Array<TreeNode> {
        const nodes = this.myChildren.splice(index, count)
        if (index < this.childrenCount) this.myIndicesValid = false
        const length = nodes.length
        for (let i = 0; i < length; i++) {
            const current = nodes[i]
            current.myIndex = -1
            current.myParent = undefined
            this.onChildRemoved?.(current, index)
        }
        return nodes
    }

    private insertNodeAt(index: int32, node: TreeNode): void {
        node.myIndex = index
        node.myParent = this
        if (index < this.childrenCount) this.myIndicesValid = false
        this.myChildren.splice(index, 0, node)
        this.onChildInserted?.(node, index)
    }

    private insertable(node: TreeNode): boolean {
        // We decided to remove the check for cyclic dependency to improve performance.
        // Attention! Now it is possible to create a tree with a cyclic dependencies.
        // So you have to be sure that the inserting node is not the root of this node.
        return node.parent === undefined
    }

    private accessible(index: int32, count: uint32 = 1): boolean {
        return Number.isInteger(index) && 0 <= index
            && Number.isInteger(count) && index <= this.childrenCount - count // integer index within range
    }

    toString(): string {
        return className(this)
    }

    toHierarchy(): string {
        return this.collectNodes().map((node: TreeNode) => "  ".repeat(node.depth) + node.toString()).join("\n")
    }

    collectNodes(): Array<TreeNode> {
        const array = new Array<TreeNode>()
        this.collectParentsTo(array)
        array.push(this)
        this.collectChildrenTo(array, true)
        return array
    }

    collectParentsTo(array: Array<TreeNode>): void {
        const index = float64ToInt(array.length)
        let parent = this.myParent
        while (parent !== undefined) {
            array.splice(index, 0, parent!)
            parent = parent!.myParent
        }
    }

    collectChildrenTo(array: Array<TreeNode>, deep: boolean = false): void {
        const children = this.myChildren
        const length = children.length
        for (let i = 0; i < length; i++) {
            const current = children[i]
            array.push(current)
            if (deep) current.collectChildrenTo(array, deep)
        }
    }
}
