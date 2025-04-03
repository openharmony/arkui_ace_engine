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

import { memo } from "../annotations"
import { KoalaCallsiteKey, int32 } from "../common"
import { StateContext } from "../states/State"
@memo export declare function Repeat(count: int32, @memo action: (index: int32) => void): void
export declare function Repeat(__memo_context: StateContext, __memo_id: KoalaCallsiteKey, count: int32, action: (__memo_context: StateContext, __memo_id: KoalaCallsiteKey, index: int32) => void): void
@memo export declare function RepeatWithKey(count: int32, key: (index: int32) => KoalaCallsiteKey, @memo action: (index: int32) => void): void
export declare function RepeatWithKey(__memo_context: StateContext, __memo_id: KoalaCallsiteKey, count: int32, key: (index: int32) => KoalaCallsiteKey, action: (__memo_context: StateContext, __memo_id: KoalaCallsiteKey, index: int32) => void): void
@memo export declare function RepeatByArray<T>(array: ReadonlyArray<T>, key: (element: T, index: int32) => KoalaCallsiteKey, @memo action: (element: T, index: int32) => void): void
export declare function RepeatByArray<T>(__memo_context: StateContext, __memo_id: KoalaCallsiteKey, array: ReadonlyArray<T>, key: (element: T, index: int32) => KoalaCallsiteKey, action: (__memo_context: StateContext, __memo_id: KoalaCallsiteKey, element: T, index: int32) => void): void
@memo export declare function RepeatRange<T>(start: int32, end: int32, element: (index: int32) => T, key: (element: T, index: int32) => KoalaCallsiteKey, @memo action: (element: T, index: int32) => void): void
export declare function RepeatRange<T>(__memo_context: StateContext, __memo_id: KoalaCallsiteKey, start: int32, end: int32, element: (index: int32) => T, key: (element: T, index: int32) => KoalaCallsiteKey, action: (__memo_context: StateContext, __memo_id: KoalaCallsiteKey, element: T, index: int32) => void): void
