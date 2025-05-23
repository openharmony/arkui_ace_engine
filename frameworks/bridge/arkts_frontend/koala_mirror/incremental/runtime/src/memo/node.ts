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

import { className, uint32 } from "@koalaui/common"
import { __context, __id } from "../internals"
import { IncrementalNode } from "../tree/IncrementalNode"
import { memoEntry1 } from "./entry"
import { __memo_context_type, __memo_id_type } from "../internals"

/**
 * @param create - the node constructor is invoked only once,
 *                 then the created node is attached to the hierarchy
 * @param update - the node updater is invoked right after the node constructor,
 *                 than it can be invoked again if the values of the used states have changed
 * @internal
 */
/** @memo:intrinsic */
export function NodeAttach<Node extends IncrementalNode>(
    create: () => Node,
    /** @memo */
    update: (node: Node) => void,
    reuseKey?: string
): void {
    const scope =
        __context().scope<void>(__id(), 0, create, undefined, undefined, undefined, reuseKey)
    if (scope.unchanged) {
        scope.cached
    } else try {
        if (!reuseKey)
            update(__context().node as Node)
        else
            // reset ID addition to 0 to simplify the reuse process later
            memoEntry1(__context(), 0, update, __context().node as Node)
    } finally {
        scope.recache()
    }
}

/**
 * @param kind - expected kind of current node
 * @param name - description of a call site to use in exception
 * @returns current node
 * @throws Error with the given name if node kind is not expected
 * @internal
 */
/** @memo:intrinsic */
export function contextNode<T extends IncrementalNode>(kind: uint32 = 1, name?: string): T {
    const node = __context().node
    if (node?.isKind(kind) == true) return node as T
    throw new Error(name
        ? (name + " cannot be used in context of " + className(node))
        : ("current " + className(node) + " does not contain the specified kind: " + kind)
    )
}

/**
 * @internal
 */
export class DataNode<Data> extends IncrementalNode {
    private data: Data | undefined = undefined

    constructor(kind: uint32 = 1) {
        super(kind)
    }

    /** @memo:intrinsic */
    static attach<Data>(
        kind: uint32,
        data: Data,
        onDataChange?: () => void
    ): void {
        const scope = __context().scope<void>(__id(), 1, (): IncrementalNode => new DataNode<Data>(kind))
        const state = scope.param<Data>(0, data)
        if (scope.unchanged) {
            scope.cached
        } else try {
            const node = __context().node as DataNode<Data>
            if (node.kind != kind) throw new Error("data node kind changed unexpectedly from " + node.kind + " to " + kind)
            node.data = state.value as Data // subscribe to the parameter change
            onDataChange?.()
        } finally {
            scope.recache()
        }
    }

    static extract<Data>(kind: uint32, node: IncrementalNode): Data | undefined {
        return node.isKind(kind) ? (node as DataNode<Data>).data : undefined
    }
}
