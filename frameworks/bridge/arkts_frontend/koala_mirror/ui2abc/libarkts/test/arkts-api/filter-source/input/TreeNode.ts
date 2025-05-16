/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { Assert as Assert, suite as suite, test as test } from "../../../../../../incremental/harness/src";

import { float64 as float64, int32 as int32, uint32 as uint32 } from "@koalaui/common";

import { TreeNode as TreeNode } from "./TreeNode";

abstract class ETSGLOBAL {
    public static main() {}

    public static _$init$_() {
        suite("TreeNode", (() => {}));
    }

    public static contentOf(node: TreeNode): string | undefined {
        return ({let gensym%%_21 = (node as StringNode);
        (((gensym%%_21) == (null)) ? undefined : gensym%%_21.content)});
    }

    public static assertContent(node: TreeNode, content: string) {
        Assert.equal<string | undefined>(contentOf(node), content);
    }

    public static assertRoot(node: TreeNode) {
        Assert.isUndefined(node.parent);
        Assert.equal(node.depth, 0);
        Assert.equal(node.index, -1);
    }

    public static assertLeaf(node: TreeNode) {
        Assert.equal(node.childrenCount, 0);
    }

    public static assertNoChildAt(parent: TreeNode, index: int32) {
        Assert.isUndefined(parent.childAt(index));
    }

    public static assertChildAt(parent: TreeNode, index: int32): TreeNode {
        let child = parent.childAt(index);
        Assert.isDefined(child);
        Assert.equal(({let gensym%%_22 = child;
        (((gensym%%_22) == (null)) ? undefined : gensym%%_22.parent)}), parent);
        Assert.equal(({let gensym%%_23 = child;
        (((gensym%%_23) == (null)) ? undefined : gensym%%_23.index)}), index);
        return child!;
    }

    public static assertToString(root: TreeNode, expected: string) {
        Assert.equal(root.toHierarchy(), expected);
    }

    public static assertRemoveChildrenAt(root: TreeNode, index: int32, count: uint32, expected: int32) {
        let childrenCount = root.childrenCount;
        let children = root.removeChildrenAt(index, count);
        Assert.equal(children.length, expected);
        Assert.equal(root.childrenCount, ((childrenCount) - (expected)));
        for (let i = 0;((i) < (expected));(i++)) {
            assertRoot(children[i]);
        }
    }

    public static createRoot() {
        return new StringNode("root", new StringNode("first"), new StringNode("second"), new StringNode("third"));
    }

    public static createDigitsRoot() {
        return new StringNode("digits", new StringNode("0"), new StringNode("1"), new StringNode("2"), new StringNode("3"), new StringNode("4"), new StringNode("5"), new StringNode("6"), new StringNode("7"), new StringNode("8"), new StringNode("9"));
    }

    public static hellohellohello() {
        console.log("hello");
    }

    public static __ARKTEST__ = "tree/TreeNode.test";


}

class StringNode extends TreeNode {
    public readonly content: string;

    public constructor(content: string, ...children: StringNode[]) {
        super();
        (this).content = content;
        (this).appendChildren(...children);
    }

    public toString(): string {
        return (this).content;
    }

}