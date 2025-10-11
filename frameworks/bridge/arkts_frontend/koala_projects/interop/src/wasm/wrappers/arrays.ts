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

import { CustomTextEncoder, CustomTextDecoder, int32 } from "@koalaui/common"

import { KPointer } from "../../interop/InteropTypes"
import { Wrapper } from "../../interop/Wrapper"
import { Access, isRead, isWrite, Exec, TypedArray, ExecWithLength } from "../../interop/arrays"

const encoder = new CustomTextEncoder()
const decoder = new CustomTextDecoder()

export function decodeToString(array: Uint8Array): string {
    return decoder.decode(array)
}

export function encodeToData(string: string): Uint8Array {
    return encoder.encode(string, false)
}

type Heap = { readonly buffer: ArrayBuffer }

// Improve: actually memory allocation primitives are defined for a specific intance instance,
// refactor me
declare const _heaps: {
    HEAP8(): Heap;
    HEAP16(): Heap;
    HEAP32(): Heap;
    HEAPU8(): Heap;
    HEAPU16(): Heap;
    HEAPU32(): Heap;
    HEAPF32(): Heap;
    HEAPF64(): Heap;
}
declare function _malloc(size: number): number;
declare function _free(ptr: number): void;

const nullptr: number = 0

// with string as array of utf8 data headed by length
export function withString<R>(data: string | undefined, exec: Exec<number, R>): R {
    if (data === undefined) return exec(nullptr)

    let array = encoder.encode(data, true)
    return withUint8Array(array, Access.READ, exec)
}

export function withStringArray<R>(strings: Array<string> | undefined, exec: Exec<number, R>): R {
    if (strings === undefined || strings.length === 0) {
        return exec(nullptr)
    }

    let array = encoder.encodeArray(strings)
    return withUint8Array(array, Access.READ, exec)
}

function withArray<C extends TypedArray, R>(
    data: C | undefined,
    access: Access,
    exec: ExecWithLength<number, R>,
    bytesPerElement: int32,
    ctor: (ptr: number, length: number) => C
): R {
    if (data === undefined || data.length === 0) {
        return exec(nullptr, 0)
    }

    let ptr = _malloc(data.length * bytesPerElement)
    let wasmArray = ctor(ptr, data.length)

    if (isRead(access)) {
        wasmArray.set(data)
    }

    let result = exec(ptr, data.length)

    if (isWrite(access)) {
        data.set(wasmArray)
    }

    _free(ptr)

    return result
}

export function withPtrArray<R>(data: Uint32Array, access: Access, exec: ExecWithLength<number, R>) {
    return withArray(data as Uint32Array, access, exec, Uint32Array.BYTES_PER_ELEMENT, (ptr: number, length: number) => {
        return new Uint32Array(_heaps.HEAPU8().buffer, ptr, length)
    })
}

export function toPtrArray<T extends Wrapper>(data: Array<T | undefined> | undefined): Uint32Array {
    if (data === undefined || data.length === 0) {
        return new Uint32Array(0)
    }
    const array = new Uint32Array(data.length)
    for (let i = 0; i < data.length; i++) {
        array[i] = data[i]?.ptr as number
    }
    return array
}

export function fromPtrArray<T extends Wrapper>(array: Uint32Array, factory: (ptr: KPointer) => T) : Array<T | undefined> {
    const result = new Array<T|undefined>(array.length)
    for (let i = 0; i < array.length; i++) {
        let v = array[i]
        if (v == 0) {
            result[i] = undefined
        } else {
            result[i] = factory(v)
        }
    }
    return result
}

export function withUint8Array<T>(data: Uint8Array | undefined, access: Access, exec: ExecWithLength<number, T>) {
    return withArray(data, access, exec, Uint8Array.BYTES_PER_ELEMENT, (ptr: number, length: number) => {
        return new Uint8Array(_heaps.HEAPU8().buffer, ptr, length)
    })
}
export function withInt8Array<T>(data: Int8Array | undefined, access: Access, exec: ExecWithLength<number, T>) {
    return withArray(data, access, exec, Int8Array.BYTES_PER_ELEMENT, (ptr: number, length: number) => {
        return new Int8Array(_heaps.HEAPU8().buffer, ptr, length)
    })
}
export function withUint16Array<T>(data: Uint16Array | undefined, access: Access, exec: ExecWithLength<number, T>) {
    return withArray(data, access, exec, Uint16Array.BYTES_PER_ELEMENT, (ptr: number, length: number) => {
        return new Uint16Array(_heaps.HEAPU8().buffer, ptr, length)
    })
}
export function withInt16Array<T>(data: Int16Array | undefined, access: Access, exec: ExecWithLength<number, T>) {
    return withArray(data, access, exec, Int16Array.BYTES_PER_ELEMENT, (ptr: number, length: number) => {
        return new Int16Array(_heaps.HEAPU8().buffer, ptr, length)
    })
}
export function withUint32Array<T>(data: Uint32Array | undefined, access: Access, exec: ExecWithLength<number, T>) {
    return withArray(data, access, exec, Uint32Array.BYTES_PER_ELEMENT, (ptr: number, length: number) => {
        return new Uint32Array(_heaps.HEAPU8().buffer, ptr, length)
    })
}
export function withInt32Array<T>(data: Int32Array | undefined, access: Access, exec: ExecWithLength<number, T>) {
    return withArray(data, access, exec, Int32Array.BYTES_PER_ELEMENT, (ptr: number, length: number) => {
        return new Int32Array(_heaps.HEAPU8().buffer, ptr, length)
    })
}
export function withFloat32Array<T>(data: Float32Array | undefined, access: Access, exec: ExecWithLength<number, T>) {
    return withArray(data, access, exec, Float32Array.BYTES_PER_ELEMENT, (ptr: number, length: number) => {
        return new Float32Array(_heaps.HEAPU8().buffer, ptr, length)
    })
}
export function withFloat64Array<T>(data: Float64Array | undefined, access: Access, exec: ExecWithLength<number, T>) {
    return withArray(data, access, exec, Float64Array.BYTES_PER_ELEMENT, (ptr: number, length: number) => {
        return new Float64Array(_heaps.HEAPU8().buffer, ptr, length)
    })
}

export function wasmHeap(): ArrayBuffer {
    return _heaps.HEAP32().buffer
}
