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

/**
 * Represents a type of the callsite identifier.
 * It is the second memo parameter inserted by the compiler plugin.
 */
export type __memo_id_type = int

/**
 * Represents an incremental context of the current state manager.
 * It is the first memo parameter inserted by the compiler plugin.
 * This interface is intended to avoid creating additional lambdas by the compiler plugin.
 *
 * Example of memo function:
 * ```
 * function f(p1: number, p2: number): number {
 *     return p1 + p2
 * }
 * ```
 * Example of memo function transformation:
 * ```
 * function f(__c: __memo_context_type, __id: __memo_id_type, p1: number, p2: number): number {
 *     const __s = __c.scope<number>(id, 2)
 *     const __p1 = __s.param(0, p1)
 *     const __p2 = __s.param(1, p2)
 *     if (__s.unchanged) {
 *         return __s.cached
 *     } else {
 *         return __s.recache(__p1.value + __p2.value)
 *     }
 * }
 * ```
 */
export declare interface __memo_context_type {
    /**
     * Enters into the nested scope corresponding to a memo function.
     * @param id - a callsite identifier
     * @param paramCount - number of trackable parameters that lead to recomputatuin of this scope
     */
    scope<T>(id: __memo_id_type, paramCount: int): IncrementalScope<T>
}

/**
 * Represents a nested scope corresponding to a memo function.
 */
export declare interface IncrementalScope<T> {
    /**
     * @returns `true` if cached value can be returned as is
     */
    readonly unchanged: boolean
    /**
     * @returns cached value if it is already computed
     */
    readonly cached: T
    /**
     * @param value - a computed value or `undefined` for void scopes
     * @returns cached value updated after the computation
     */
    recache(value?: T): T
    /**
     * @returns internal state for the parameter, specified by index
     */
    param<V>(index: int, value: V): State<V>
}

/**
 * Represents a state, wrapping a value of the given type.
 */
export declare interface State<V> {
    /**
     * Returns a current value of the state and
     * adds a dependency to the current incremental scope.
     */
    readonly value: V
}
