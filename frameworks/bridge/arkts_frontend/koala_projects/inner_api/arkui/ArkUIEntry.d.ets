/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { PeerNode } from 'arkui/PeerNode';
import {
    __memo_context_type as __memo_context_type,
    __memo_id_type as __memo_id_type,
} from 'arkui.incremental.runtime.state';

type KPointer = long;
type int32 = int;

let _undefinedInstanceId : int32 = -1000

export declare function addPartialUpdate<T>(update: () => void, context: T, callback: (before: boolean) => void): void;

export declare function createUiDetachedRoot(
    peerFactory: () => PeerNode,
    builder: (__memo_context: __memo_context_type, __memo_id: __memo_id_type) => void,
    instanceId: int32 = _undefinedInstanceId
): PeerNode;

export declare function destroyUiDetachedRoot(ptr: KPointer, instanceId: int32): boolean;