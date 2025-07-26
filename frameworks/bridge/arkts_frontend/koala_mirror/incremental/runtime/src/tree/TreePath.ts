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

import { uint32 } from "@koalaui/common"

/**
 * This class represents a path to a node in a tree.
 */
export class TreePath<Node> {
    readonly node: Node
    readonly parent: TreePath<Node> | undefined

    /**
     * Creates a tree path to the given node relative to the specified parent path.
     * The path represents a root node if parent path is undefined.
     *
     * @param node    a node in a tree
     * @param parent  a path to a parent node or undefined for the root
     */
    constructor(node: Node, parent?: TreePath<Node>) {
        this.node = node
        this.parent = parent
    }

    /**
     * Creates a tree path to the specified child node.
     *
     * @param node  a node in a tree
     */
    child(node: Node): TreePath<Node> {
        return new TreePath<Node>(node, this)
    }

    /**
     * Returns the tree path that represents the root node.
     * The root path returns itself.
     */
    get root(): TreePath<Node> {
        return this.parent?.root ?? this
    }

    /**
     * Returns the depth of the tree path relative to the root node.
     * The root path returns 0.
     */
    get depth(): uint32 {
        let count: uint32 = 0
        let parent = this.parent
        while (parent !== undefined) {
            parent = parent!.parent
            count++
        }
        return count
    }

    toString(): string {
        let parent = this.parent ?? ""
        return `${parent}/${this.node}`
    }
}
