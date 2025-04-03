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

import { int32 } from "@koalaui/common"
import { KPointer } from "../../interop/InteropTypes"

export const nullptr: number = 0

export function isNullPtr(value: KPointer): boolean {
    return (value == nullptr)
}

export function ptrToString(ptr: KPointer) {
    if (ptr === 0) return "0x0"

    const hex = (ptr as number).toString(16).padStart(8, "0")
    return `0x${hex}`
}

export function isSamePtr(a: KPointer, b: KPointer) {
    return a === b
}

export function ptrToBits(ptr: KPointer): Uint32Array {
    let result = new Uint32Array(2)
    result[0] = ptr as int32
    return result
}

export function bitsToPtr(array: Int32Array, offset: int32): KPointer {
    return array[offset]
}
