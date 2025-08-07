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

import { float64, int32, int8 } from "./types"

export function asArray<T>(value: T[]): Array<T> {
    return value
}

export function Array_from_set<T>(set: Set<T>): Array<T> {
    return Array.from(set)
}

export function Array_from_int32(data: Int32Array): int32[] {
    return Array.from(data)
}

export function Array_from_number(data: float64[]): Array<float64> {
    return data
}

export function int8Array(size: int32): int8[] {
    return []
}
