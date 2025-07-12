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
import { TreePath } from "../../src/tree/TreePath"

suite("TreePath", () => {

    let root = new TreePath<string>("root")

    test("root path is root", () => Assert.strictEqual(root.root, root))
    test("root path depth", () => Assert.equal(root.depth, 0))
    test("root path has undefined parent", () => Assert.strictEqual(root.parent, undefined))
    test("root path to string", () => Assert.equal(root.toString(), "/root"))

    let parent = root.child("parent")
    let current = parent.child("node")

    test("tree path has root", () => Assert.strictEqual(current.root, root))
    test("tree path has parent", () => Assert.strictEqual(current.parent, parent))
    test("tree path depth", () => Assert.equal(current.depth, 2))
    test("tree path parent depth", () => Assert.equal(current.parent?.depth, 1))
    test("tree path to string", () => Assert.equal(current.toString(), "/root/parent/node"))

    let sibling = parent.child("sibling")

    test("siblings has the same parents", () => Assert.strictEqual(current.parent, sibling.parent))
})
export const __ARKTEST__ = "tree/TreePath.test"
