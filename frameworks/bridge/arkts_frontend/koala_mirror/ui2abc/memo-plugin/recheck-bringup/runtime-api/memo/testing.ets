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

import { memo, memo_intrinsic } from "../annotations"
import { uint32, KoalaCallsiteKey } from "../common"
import { GlobalStateManager } from "../states/GlobalStateManager"
import { ComputableState, State, StateContext, StateManager } from "../states/State"
import { IncrementalNode } from "../tree/IncrementalNode"
export declare class TestNode extends IncrementalNode {
    content: string
    constructor(kind: uint32 = 1)
    toString(): string
    static create(@memo content: (node: TestNode) => void): ComputableState<TestNode>
    static create(content: (__memo_context: StateContext, __memo_id: KoalaCallsiteKey, node: TestNode) => void): ComputableState<TestNode>
    @memo_intrinsic static attach(content: (node: TestNode) => void): void
    @memo_intrinsic static attach(content: (__memo_context: StateContext, __memo_id: KoalaCallsiteKey, node: TestNode) => void): void
}
export declare function testRoot(@memo content: (node: TestNode) => void): State<TestNode>
export declare function testRoot(content: (__memo_context: StateContext, __memo_id: KoalaCallsiteKey, node: TestNode) => void): State<TestNode>
export declare function testUpdate(withCallbacks: boolean = true, manager: StateManager = GlobalStateManager.instance): uint32
export declare function testTick<Node extends IncrementalNode>(root: State<Node>, withCallbacks: boolean = true): void
