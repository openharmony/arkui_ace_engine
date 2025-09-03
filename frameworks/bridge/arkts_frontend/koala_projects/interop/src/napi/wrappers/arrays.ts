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

import { CustomTextDecoder, CustomTextEncoder } from "@koalaui/common"
import { Access, Exec, ExecWithLength, PtrArray, TypedArray } from "../../interop/arrays"
import { nullptr } from "./Wrapper"
import { Wrapper } from "../../interop/Wrapper"
import { KPointer, KStringArrayPtr } from "../../interop"

const encoder = new CustomTextEncoder()
const decoder = new CustomTextDecoder()

export function decodeToString(array: Uint8Array): string {
    return decoder.decode(array)
}

export function encodeToData(string: string): Uint8Array {
    return encoder.encode(string, false)
}

export function withString<R>(data: string | undefined, exec: Exec<string|null, R>): R {
    return exec(data === undefined ? null : data)
}

export function withStringArray<R>(strings: Array<string> | undefined, exec: Exec<KStringArrayPtr, R>): R {
    if (strings === undefined || strings.length === 0) {
        return exec(null)
    }

    let array = encoder.encodeArray(strings)
    return exec(array)
}

function withArray<C extends TypedArray, R>(
    data: C | undefined,
    exec: ExecWithLength<C | null, R>
): R {
    return exec(data ?? null, data?.length ?? 0)
}

export function withPtrArray<R>(data: BigUint64Array, access: Access, exec: ExecWithLength<BigUint64Array | null, R>) {
    return exec(data ?? null, data?.length ?? 0) // TODO rethink
}

export function toPtrArray<T extends Wrapper>(data: Array<T | undefined> | undefined): BigUint64Array {
    if (data == undefined || data.length === 0) {
        return new BigUint64Array(0)
    }
    const array = new BigUint64Array(data.length)
    for (let i = 0; i < data.length; i++) {
        let item = data[i]
        array[i] = item != undefined ? item.ptr as bigint : nullptr
    }
    return array
}

export function fromPtrArray<T extends Wrapper>(array: PtrArray, factory: (ptr: KPointer) => T) : Array<T | undefined> {
    if (array.length === 0) {
        return new Array<T>(0)
    }
    const result = new Array<T|undefined>(array.length)
    for (let i = 0; i < array.length; i++) {
        let ptr = array[i]
        if (ptr == nullptr) {
            result[i] = undefined
        } else {
            result[i] = factory(ptr)
        }
    }
    return result
}

export function withUint8Array<T>(data: Uint8Array | undefined, access: Access, exec: ExecWithLength<Uint8Array | null, T>) {
    return withArray(data, exec)
}
export function withInt8Array<T>(data: Int8Array | undefined, access: Access, exec: ExecWithLength<Int8Array | null, T>) {
    return withArray(data, exec)
}
export function withUint16Array<T>(data: Uint16Array | undefined, access: Access, exec: ExecWithLength<Uint16Array | null, T>) {
    return withArray(data, exec)
}
export function withInt16Array<T>(data: Int16Array | undefined, access: Access, exec: ExecWithLength<Int16Array | null, T>) {
    return withArray(data, exec)
}
export function withUint32Array<T>(data: Uint32Array | undefined, access: Access, exec: ExecWithLength<Uint32Array | null, T>) {
    return withArray(data, exec)
}
export function withInt32Array<T>(data: Int32Array | undefined, access: Access, exec: ExecWithLength<Int32Array | null, T>) {
    return withArray(data, exec)
}
export function withFloat32Array<T>(data: Float32Array | undefined, access: Access, exec: ExecWithLength<Float32Array | null, T>) {
    return withArray(data, exec)
}
export function withFloat64Array<T>(data: Float64Array | undefined, access: Access, exec: ExecWithLength<Float64Array | null, T>) {
    return withArray(data, exec)
}
export function wasmHeap(): ArrayBuffer {
    throw new Error("Unused")
}