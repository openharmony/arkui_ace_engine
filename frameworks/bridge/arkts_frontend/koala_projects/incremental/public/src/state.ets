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

export type __memo_context_type = StateContext;

export type __memo_id_type = int;

type Equivalent<Value> = (oldV: Value, newV: Value) => boolean;

export interface StateContext {
    scope<T>(id: __memo_id_type, paramCount: int): IncrementalScope<T>;
}

export interface IncrementalScope<T> {
    get unchanged(): boolean;
    get cached(): T;
    recache(value?: T): T;
    param<V>(index: int, value: V): ReadableState<V>;
}

export interface ReadableState<V> {
    readonly value: V;
    readonly modified: boolean;
}
