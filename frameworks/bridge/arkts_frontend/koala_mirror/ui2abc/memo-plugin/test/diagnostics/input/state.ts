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

export interface State<Value> {
    /**
     * If state was modified since last UI computations.
     */
    readonly modified: boolean
    /**
     * Current value of the state.
     * State value doesn't change during memo code execution.
     */
    readonly value: Value
}

export interface MutableState<Value> extends State<Value> {
    /**
     * Current value of the state as a mutable value.
     * You should not change state value from a memo code.
     * State value doesn't change during memo code execution.
     * In the event handlers and other non-memo code
     * a changed value is immediately visible.
     */
    value: Value
}

export function mutableState<T>(value: T): MutableState<T> {
    return { value, modified: false }
}


interface I {
    s: string
}

class Impl {
    s = " asd"
}

export function provideI(): I {
    return new Impl()
}