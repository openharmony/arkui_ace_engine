/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

export interface ReadonlyTreeNode {
    /**
     * @returns a parent tree node if it is exist
     */
    readonly parent: ReadonlyTreeNode | undefined
    /**
     * @returns the first child node contained in this node if it is exist
     */
    readonly firstChild: ReadonlyTreeNode | undefined
    /**
     * @returns the next sibling of this node if it is exist
     */
    readonly nextSibling: ReadonlyTreeNode | undefined
    /**
     * @returns text representation of the node used to generate a tree hierarchy
     */
    toString(): string
    /**
     * @returns text representation of a tree hierarchy starting from the tree node
     */
    toHierarchy(): string
}
