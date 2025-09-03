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

// TODO: this can be a performance disaster
// just wait for the library to provide the proper functionality.
export function asArray<T>(value: T[]): Array<T> {
    return Array.of<T>(...value)
}

// TODO: this can be a performance disaster
// just wait for the library to provide the proper functionality.
export function Array_from_set<T>(set: Set<T>): Array<T> {
    const array = new Array<T>() // to avoid creation of undefined content
    const values = set.values()
    for (let it = values.next(); it.done != true; it = values.next())  {
        array.push(it.value as T)
    }
    return array
}

// TODO: this can be a performance disaster
// just wait for the library to provide the proper functionality.
export function Array_from_int32(data: Int32Array): number[] {
    const result: number[] = []
    for (let i: int32 = 0; i < data.length; i++) {
        result[i] = data.at(i) as number
    }
    return result
}

// TODO: this can be a performance disaster
// just wait for the library to provide the proper functionality.
export function Array_from_number(data: float64[]): Array<float64> {
    const result = new Array<number>(data.length)
    for (let i: int32 = 0; i < data.length; i++) {
        result[i] = data[i]
    }
    return result
}

export function int8Array(size: int32): int8[] {
    return new int8[size]
}

