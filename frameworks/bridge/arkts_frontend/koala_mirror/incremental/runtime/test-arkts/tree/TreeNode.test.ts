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
import { float64, int32, uint32 } from "@koalaui/common"
import { TreeNode } from "../../src/tree/TreeNode"

class StringNode extends TreeNode {
    readonly content: string

    constructor(content: string, ...children: TreeNode[]) {
        super()
        this.content = content
        this.appendChildren(...children)
    }

    toString(): string {
        return this.content
    }
}

function contentOf(node: TreeNode): string | undefined {
    return (node as StringNode)?.content
}

function assertContent(node: TreeNode, content: string) {
    Assert.equal<string | undefined>(contentOf(node), content)
}

function assertRoot(node: TreeNode) {
    Assert.isUndefined(node.parent)
    Assert.equal(node.depth, 0)
    Assert.equal(node.index, -1)
}

function assertLeaf(node: TreeNode) {
    Assert.equal(node.childrenCount, 0)
}

function assertNoChildAt(parent: TreeNode, index: int32) {
    Assert.isUndefined(parent.childAt(index))
}

function assertChildAt(parent: TreeNode, index: int32): TreeNode {
    let child = parent.childAt(index)
    Assert.isDefined(child)
    Assert.equal(child?.parent, parent)
    Assert.equal(child?.index, index)
    return child!
}

function assertToString(root: TreeNode, expected: string) {
    Assert.equal(root.toHierarchy(), expected)
}

function assertRemoveChildrenAt(root: TreeNode, index: int32, count: uint32, expected: int32) {
    let childrenCount = root.childrenCount
    let children = root.removeChildrenAt(index, count)
    Assert.equal(children.length, expected)
    Assert.equal(root.childrenCount, childrenCount - expected)
    for (let i = 0; i < expected; i++) {
        assertRoot(children[i])
    }
}

function createRoot() {
    return new StringNode("root",
        new StringNode("first"),
        new StringNode("second"),
        new StringNode("third"))
}

function createDigitsRoot() {
    return new StringNode("digits",
        new StringNode("0"),
        new StringNode("1"),
        new StringNode("2"),
        new StringNode("3"),
        new StringNode("4"),
        new StringNode("5"),
        new StringNode("6"),
        new StringNode("7"),
        new StringNode("8"),
        new StringNode("9"))
}

suite("TreeNode", () => {
    test("single node", () => {
        let node = new StringNode("node")
        assertContent(node, "node")
        assertRoot(node)
        assertLeaf(node)
    })
    test("simple root", () => {
        let root = createRoot()
        assertContent(root, "root")
        assertRoot(root)
        Assert.equal(root.childrenCount, 3)
        assertNoChildAt(root, -1)
        assertNoChildAt(root, 3)
        let node0 = assertChildAt(root, 0)
        assertContent(node0, "first")
        assertLeaf(node0)
        let node1 = assertChildAt(root, 1)
        assertContent(node1, "second")
        assertLeaf(node1)
        let node2 = assertChildAt(root, 2)
        assertContent(node2, "third")
        assertLeaf(node2)
        const children = root.children.slice()
        Assert.equal(children.length, 3)
        Assert.equal(children[0], node0)
        Assert.equal(children[1], node1)
        Assert.equal(children[2], node2)
        assertToString(root,
            "root\n" +
            "  first\n" +
            "  second\n" +
            "  third")
    })
    test("iterate for each child", () => {
        let root = createRoot()
        let count = 0
        let children = ["first", "second", "third"]
        root.forEach((node, index) => {
            Assert.equal<string | undefined>(children[count], contentOf(node))
            count++
        })
        Assert.equal(count, 3)
    })
    test("iterate for each child with index", () => {
        let root = createRoot()
        let count = 0
        root.forEach((node, index) => {
            Assert.equal<float64>(index, count)
            count++
        })
        Assert.equal(count, 3)
    })
    test("iterate through not every child", () => {
        let root = createRoot()
        let count = 0
        Assert.isFalse(root.every((node, index) => {
            count++
            return contentOf(node)?.length == 5
        }))
        Assert.equal(count, 2)
    })
    test("iterate through every child with index", () => {
        let root = createRoot()
        let count = 0
        let children = ["first", "second", "third"]
        Assert.isTrue(root.every((node, index) => {
            Assert.equal<float64>(index, count)
            count++
            return children[index as int32] === contentOf(node)
        }))
        Assert.equal(count, 3)
    })
    test("iterate through some children", () => {
        let root = createRoot()
        let count = 0
        Assert.isTrue(root.some((node, index) => {
            count++
            return contentOf(node)?.length == 6
        }))
        Assert.equal(count, 2)
    })
    test("iterate through some children with index", () => {
        let root = createRoot()
        let count = 0
        Assert.isTrue(root.some((node, index) => {
            Assert.equal<float64>(index, count)
            count++
            return index == 0
        }))
        Assert.equal(count, 1)
    })
    test("find child by content", () => {
        let root = createRoot()
        Assert.equal(root.find<TreeNode>((node, index): TreeNode | undefined => contentOf(node) == "second" ? node : undefined), assertChildAt(root, 1))
    })
    test("find child by index", () => {
        let root = createRoot()
        Assert.equal(root.find<TreeNode>((node, index): TreeNode | undefined => index == 1 ? node : undefined), assertChildAt(root, 1))
    })
    test("insert, move and remove children", () => {
        let root = createRoot()
        Assert.isFalse(root.removeChild(new StringNode("second"))) // non-existent node
        assertToString(root,
            "root\n" +
            "  first\n" +
            "  second\n" +
            "  third")
        let second = assertChildAt(root, 1)
        second.appendChildren(new StringNode("1"), new StringNode("2"), new StringNode("3"))
        assertToString(root,
            "root\n" +
            "  first\n" +
            "  second\n" +
            "    1\n" +
            "    2\n" +
            "    3\n" +
            "  third")
        second.removeFromParent()
        assertRoot(second)
        assertToString(second,
            "second\n" +
            "  1\n" +
            "  2\n" +
            "  3")
        assertToString(root,
            "root\n" +
            "  first\n" +
            "  third")
        Assert.isFalse(root.removeChild(second)) // cannot remove twice
        Assert.isTrue(root.insertChildAt(0, second))
        assertToString(root,
            "root\n" +
            "  second\n" +
            "    1\n" +
            "    2\n" +
            "    3\n" +
            "  first\n" +
            "  third")
        let first = root.removeChildAt(1)
        Assert.isDefined(first)
        assertRoot(first!)
        assertContent(first!, "first")
        root.appendChild(first!)
        assertToString(root,
            "root\n" +
            "  second\n" +
            "    1\n" +
            "    2\n" +
            "    3\n" +
            "  third\n" +
            "  first")
    })
    test("insert several children at once", () => {
        let root = createRoot()
        let children: Array<TreeNode> = [new StringNode("second.1"), new StringNode("second.2"), new StringNode("second.3")]
        Assert.isFalse(root.insertChildrenAt(-1, ...children))
        Assert.isFalse(root.insertChildrenAt(4, ...children))
        Assert.isTrue(root.insertChildrenAt(2, ...children))
        assertToString(root,
            "root\n" +
            "  first\n" +
            "  second\n" +
            "  second.1\n" +
            "  second.2\n" +
            "  second.3\n" +
            "  third")
        Assert.isTrue(root.insertChildrenAt(0, new StringNode("zero")))
        assertToString(root,
            "root\n" +
            "  zero\n" +
            "  first\n" +
            "  second\n" +
            "  second.1\n" +
            "  second.2\n" +
            "  second.3\n" +
            "  third")
        Assert.isTrue(root.insertChildrenAt(root.childrenCount, new StringNode("third.A"), new StringNode("third.B")))
        assertToString(root,
            "root\n" +
            "  zero\n" +
            "  first\n" +
            "  second\n" +
            "  second.1\n" +
            "  second.2\n" +
            "  second.3\n" +
            "  third\n" +
            "  third.A\n" +
            "  third.B")
    })
    test("remove several children at once", () => {
        let root = createDigitsRoot()
        assertToString(root,
            "digits\n" +
            "  0\n" +
            "  1\n" +
            "  2\n" +
            "  3\n" +
            "  4\n" +
            "  5\n" +
            "  6\n" +
            "  7\n" +
            "  8\n" +
            "  9")
        assertRemoveChildrenAt(root, -1, 1, 0)
        assertRemoveChildrenAt(root, root.childrenCount, 1, 0)
        // remove leading nodes
        assertRemoveChildrenAt(root, 0, 1 + root.childrenCount, 0)
        assertRemoveChildrenAt(root, 0, 2, 2)
        assertToString(root,
            "digits\n" +
            "  2\n" +
            "  3\n" +
            "  4\n" +
            "  5\n" +
            "  6\n" +
            "  7\n" +
            "  8\n" +
            "  9")
        // remove trailing nodes
        assertRemoveChildrenAt(root, root.childrenCount - 1, 2, 0)
        assertRemoveChildrenAt(root, root.childrenCount - 2, 2, 2)
        assertToString(root,
            "digits\n" +
            "  2\n" +
            "  3\n" +
            "  4\n" +
            "  5\n" +
            "  6\n" +
            "  7")
        // remove inner nodes
        assertRemoveChildrenAt(root, 1, root.childrenCount, 0)
        assertRemoveChildrenAt(root, 1, 4, 4)
        assertToString(root,
            "digits\n" +
            "  2\n" +
            "  7")
    })
    test("remove trailing children at once", () => {
        let root = createDigitsRoot()
        Assert.equal(root.childrenCount, 10)
        Assert.equal(root.removeChildrenAt(-1).length, 0)
        Assert.equal(root.removeChildrenAt(root.childrenCount).length, 0)
        Assert.equal(root.childrenCount, 10)
        Assert.equal(root.removeChildrenAt(7).length, 3)
        Assert.equal(root.childrenCount, 7)
        Assert.equal(root.removeChildrenAt(6).length, 1)
        Assert.equal(root.childrenCount, 6)
        Assert.equal(root.removeChildrenAt(1).length, 5)
        Assert.equal(root.childrenCount, 1)
        Assert.equal(root.removeChildrenAt(0).length, 1)
        Assert.equal(root.childrenCount, 0)
    })
})
export const __ARKTEST__ = "tree/TreeNode.test"
