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
    return object ? Class.of(object).getName() : 'null'
}

export function isFunction(object?: Object): boolean {
    return object instanceof Function
}

// Improve: This is an very ad hoc function,
// but I could not find in ArkTS stdlib enough functionality
// for a more generic way.
export function functionOverValue<Value>(value: Value | (() => Value)): boolean {
    return value instanceof Function
}

export function isNotPrimitive(value: Object): boolean {
    const ttype = Class.of(value)
    return !(ttype === Class.from<void>() ||
            ttype === Class.from<null>() ||
            ttype === Class.from<undefined>() ||
            ttype === Class.from<Boolean>() ||
            ttype === Class.from<Byte>() ||
            ttype === Class.from<Short>() ||
            ttype === Class.from<Int>() ||
            ttype === Class.from<Long>() ||
            ttype === Class.from<Char>() ||
            ttype === Class.from<Float>() ||
            ttype === Class.from<Double>() ||
            ttype === Class.from<Number>() ||
            ttype === Class.from<String>())
}
