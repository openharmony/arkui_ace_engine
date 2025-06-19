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

import { memo, memo_entry } from "../annotations"
import { KoalaCallsiteKey } from "../common"
import { ComputableState, StateContext } from "../states/State"
import { IncrementalNode } from "../tree/IncrementalNode"
export declare function memoRoot<Node extends IncrementalNode>(node: Node, @memo update: (node: Node) => void): ComputableState<Node>
export declare function memoRoot<Node extends IncrementalNode>(node: Node, update: (__memo_context: StateContext, __memo_id: KoalaCallsiteKey, node: Node) => void): ComputableState<Node>
@memo_entry export declare function memoEntry<R>(__memo_context: StateContext, __memo_id: KoalaCallsiteKey, @memo entry: () => R): R
@memo_entry export declare function memoEntry<R>(__memo_context: StateContext, __memo_id: KoalaCallsiteKey, entry: (__memo_context: StateContext, __memo_id: KoalaCallsiteKey) => R): R
@memo_entry export declare function memoEntry1<T, R>(__memo_context: StateContext, __memo_id: KoalaCallsiteKey, @memo entry: (arg: T) => R, arg: T): R
@memo_entry export declare function memoEntry1<T, R>(__memo_context: StateContext, __memo_id: KoalaCallsiteKey, entry: (__memo_context: StateContext, __memo_id: KoalaCallsiteKey, arg: T) => R, arg: T): R
@memo_entry export declare function memoEntry2<T1, T2, R>(__memo_context: StateContext, __memo_id: KoalaCallsiteKey, @memo entry: (arg1: T1, arg2: T2) => R, arg1: T1, arg2: T2): R
@memo_entry export declare function memoEntry2<T1, T2, R>(__memo_context: StateContext, __memo_id: KoalaCallsiteKey, entry: (__memo_context: StateContext, __memo_id: KoalaCallsiteKey, arg1: T1, arg2: T2) => R, arg1: T1, arg2: T2): R
