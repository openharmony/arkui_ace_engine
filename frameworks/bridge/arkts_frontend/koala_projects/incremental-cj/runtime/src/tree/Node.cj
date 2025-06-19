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
package KoalaRuntime.tree

import std.unittest.*

public interface TreeNode<N> where N <: TreeNode<N> {
    /**
     * @returns a parent node if it is exist
     */
    prop parent: ?N

    /**
     * @returns the first child node contained in this node if it is exist
     */
    prop firstChild: ?N

    /**
     * @returns the next sibling of this node if it is exist
     */
    prop nextSibling: ?N

    /**
     * @returns the previous sibling of this node if it is exist
     */
    prop previousSibling: ?N

    /**
     * Appends a string representation of the node to the specified string builder. In general, the toString method returns a string that "textually represents" this object. The result should be a concise but informative representation that is easy for a person to read. It is recommended that all subclasses override this method.
     * @param sb - a string builder to collect content
     */
    func toStringBuilder(sb: StringBuilder): Unit
}

public func forEachParentOf<N>(node: N, accept: (parent: N) -> Unit): Unit where N <: TreeNode<N> {
    var option = node.parent
    while (let Some(parent) <- option) {
        option = parent.parent
        accept(parent)
    }
}

public func forEachChildOf<N>(node: N, accept: (child: N) -> Unit): Unit where N <: TreeNode<N> {
    var option = node.firstChild
    while (let Some(child) <- option) {
        option = child.nextSibling
        accept(child)
    }
}

/**
 * @param node - a node from which the text representation of a tree hierarchy starts to dump
 * @returns text representation of a tree hierarchy starting from the specified node
 */
public func dumpHierarchyOf<N>(node: N): String where N <: TreeNode<N> {
    let sb = StringBuilder()
    dumpHierarchyImpl(node, sb)
    sb.toString()
}

func dumpHierarchyImpl<N>(node: N, sb: StringBuilder): Unit where N <: TreeNode<N> {
    forEachParentOf(node) {
        _ => sb.append("  ")
    }
    node.toStringBuilder(sb)
    forEachChildOf(node) {
        child =>
        sb.append("\n")
        dumpHierarchyImpl(child, sb)
    }
}

/**
 * @param node - a node from which the text representation of a tree hierarchy starts to dump
 * @param hierarchy - text representation of expected tree hierarchy starting from the specified node
 */
public func assertHierarchyOf<N>(node: N, hierarchy: String): Unit where N <: TreeNode<N> {
    assertEqual("expected hierarchy", "actual hierarchy", hierarchy, dumpHierarchyOf<N>(node))
}
