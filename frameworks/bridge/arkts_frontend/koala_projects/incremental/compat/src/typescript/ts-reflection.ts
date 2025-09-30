/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

export function className(object?: Object): string {
    return object?.constructor.name ?? "<null>"
}

export function isFunction(object?: Object): boolean {
    return typeof object === 'function'
}

// Improve: this is to match arkts counterpart
export function functionOverValue<Value>(value: Value|(()=>Value)): boolean {
    return typeof value === 'function'
}

export function refEqual<Value>(a: Value, b: Value): boolean {
    return a === b
}

export function isNotPrimitive(value: Object): boolean {
    return true
}
