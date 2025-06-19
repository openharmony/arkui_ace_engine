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
import { State, StateContext } from "../states/State"
import { KoalaCallsiteKey } from "../common"
import { ReadonlyTreeNode } from "../tree/ReadonlyTreeNode"
@memo_intrinsic export declare function contextLocal<Value>(name: string): State<Value> | undefined
@memo_intrinsic export declare function contextLocalValue<Value = ReadonlyTreeNode>(name: string): Value // TODO
export declare function contextLocalValue<Value = ReadonlyTreeNode>(stateContext: StateContext, id: KoalaCallsiteKey, name: string): Value // TODO
@memo_intrinsic export declare function contextLocalScope<Value>(name: string, value: Value, @memo content: () => void): void
