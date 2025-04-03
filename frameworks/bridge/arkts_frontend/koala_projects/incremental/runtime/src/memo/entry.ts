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

import { KoalaCallsiteKey, KoalaCallsiteKeys, KoalaProfiler } from "@koalaui/common"
import { GlobalStateManager } from "../states/GlobalStateManager"
import { ComputableState, StateContext } from "../states/State"
import { IncrementalNode } from "../tree/IncrementalNode"

/**
 * @param manager - a state manager
 * @param node - a root node for the composition
 * @param update - a memo-function to build and update the composition
 * @returns updatable state with the given node as the composition root
 * @internal
 */
export function memoRoot<Node extends IncrementalNode>(
    node: Node,
    /** @memo */
    update: (node: Node) => void,
): ComputableState<Node> {
    const manager = GlobalStateManager.instance
    return manager.updatableNode<Node>(node, (context: StateContext) => {
        KoalaProfiler.counters?.buildRootEnter()
        const frozen = manager.frozen
        manager.frozen = true // states are frozen during recomposition
        memoEntry1<Node, void>(context, KoalaCallsiteKeys.empty, update, node)
        manager.frozen = frozen
        KoalaProfiler.counters?.buildRootExit()
    })
}

/**
 * This is where regular code can enter the memo realm.
 * This function allows to run a memo function in a non-memo context.
 * @internal
 */
/** @memo:entry */
export function memoEntry<R>(
    __memo_context: StateContext,
    __memo_id: KoalaCallsiteKey,
    /** @memo */
    entry: () => R,
): R {
    return entry()
}

/**
 * This is where regular code can enter the memo realm.
 * This function allows to run a memo function in a non-memo context.
 * @internal
 */
/** @memo:entry */
export function memoEntry1<T, R>(
    __memo_context: StateContext,
    __memo_id: KoalaCallsiteKey,
    /** @memo */
    entry: (arg: T) => R,
    arg: T,
): R {
    return entry(arg)
}

/**
 * This is where regular code can enter the memo realm.
 * This function allows to run a memo function in a non-memo context.
 * @internal
 */
/** @memo:entry */
export function memoEntry2<T1, T2, R>(
    __memo_context: StateContext,
    __memo_id: KoalaCallsiteKey,
    /** @memo */
    entry: (arg1: T1, arg2: T2) => R,
    arg1: T1,
    arg2: T2,
): R {
    return entry(arg1, arg2)
}
