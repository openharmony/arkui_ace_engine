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

import { memo, memo_skip, memo_intrinsic } from "../annotations"
import { ArrayState, ControlledScope, MutableState } from "../states/State"
@memo_intrinsic export declare function memoize<Value>(compute: () => Value): Value
@memo_intrinsic export declare function memoLifecycle(onAttach: () => void, onDetach: () => void): void
@memo_intrinsic export declare function once(callback: () => void): void
@memo_intrinsic export declare function remember<Value>(compute: () => Value): Value
@memo_intrinsic export declare function rememberDisposable<Value>(compute: () => Value, cleanup: (value: Value | undefined) => void): Value 
@memo_intrinsic export declare function rememberMutableState<Value>(initial: (() => Value) | Value): MutableState<Value>
@memo_intrinsic export declare function rememberArrayState<Value>(initial?: () => ReadonlyArray<Value>): ArrayState<Value>
@memo export declare function rememberMutableAsyncState<Value>(compute: () => Promise<Value | undefined>, initial?: Value, onError?: (error: Error) => void): MutableState<Value | undefined>
@memo export declare function rememberComputableState<Key, Value>(key: Key, @memo_skip compute: (key: Key) => Promise<Value | undefined>, initial?: Value, onError?: (error: Error) => void): MutableState<Value | undefined>
@memo export declare function rememberComputableValue<Key, Value>(key: Key, @memo_skip compute: (key: Key) => Promise<Value | undefined>, initial?: Value, onError?: (e: Error) => void): Value | undefined
@memo_intrinsic export declare function rememberControlledScope(invalidate: () => void): ControlledScope
