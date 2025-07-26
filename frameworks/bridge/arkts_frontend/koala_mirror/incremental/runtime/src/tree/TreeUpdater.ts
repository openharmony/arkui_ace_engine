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

import { int32, uint32 } from "@koalaui/common"
import { TreePath } from "./TreePath"

/**
 * This class provides basic functionality for tree building or incremental tree updating.
 */
export abstract class TreeUpdater<Node> {
    private current: TreePath<Node>
    readonly reverse: boolean

    /**
     * @param root     the tree root that always exists
     * @param reverse  `false` builds a tree top-down, `true` build a tree bottom-up
     */
    constructor(root: Node, reverse: boolean = false) {
        this.current = new TreePath<Node>(root)
        this.reverse = reverse
    }

    /**
     * Returns the path to the selected node.
     */
    get path(): TreePath<Node> {
        return this.current
    }

    /**
     * Returns the selected node to perform tree change operations.
     */
    get node(): Node {
        return this.current.node
    }

    /**
     * Selects the specified child node when the updater is getting traversed down the tree.
     */
    down(node: Node): void {
        this.current = this.current.child(node)
    }

    /**
     * Selects the parent node when the updater is getting traversed up the tree.
     */
    up(): void {
        let parent = this.current.parent
        if (parent === undefined) throw new Error("unexpected")
        this.current = parent
    }

    /**
     * Selects the root node to prepare the updater to traversing a tree.
     */
    clear(): void {
        this.current = this.current.root
    }

    /**
     * Inserts the specified node as a child of a selected node at the given index.
     */
    abstract insert(index: int32, node: Node): void

    /**
     * Removes the specified amount of children from the given index.
     */
    abstract remove(index: int32, amount: uint32): void

    /**
     * Moves the specified amount of children from the indexFrom to the indexTo.
     */
    abstract move(indexFrom: int32, indexTo: int32, amount: uint32): void
}
