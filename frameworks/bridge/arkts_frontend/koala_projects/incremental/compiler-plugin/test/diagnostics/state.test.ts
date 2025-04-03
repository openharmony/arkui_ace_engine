/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
    value: Value
}

export interface MutableState<Value> extends State<Value> {
    value: Value
}

export class MutableStateImpl<Value> implements MutableState<Value> {
    constructor(public value: Value) {}
}

export function mutableState<T>(value: T): MutableState<T> {
    return new MutableStateImpl<T>(value)
}
