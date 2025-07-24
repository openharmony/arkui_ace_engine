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

const fakeHeap = new ArrayBuffer(16384)
export const HEAP8 = new Int8Array(fakeHeap)
export const HEAP16 = new Int16Array(fakeHeap)
export const HEAP32 = new Int32Array(fakeHeap)
const fakeUint8 = new Uint8Array(fakeHeap)
const fakeUint16 = new Uint16Array(fakeHeap)
const fakeUint32 = new Uint32Array(fakeHeap)
const fakeFloat32 = new Float32Array(fakeHeap)
const fakeFloat64 = new Float64Array(fakeHeap);

// TODO Check usages and probably remove
(globalThis as any)._heaps = {
    HEAP8() {
        return HEAP8
    },
    HEAP16() {
        return HEAP16
    },
    HEAP32() {
        return HEAP32
    },
    HEAPU8() {
        return fakeUint8
    },
    HEAPU16() {
        return fakeUint16
    },
    HEAPU32() {
        return fakeUint32
    },
    HEAPF32() {
        return fakeFloat32
    },
    HEAPF64() {
        return fakeFloat64
    },
};

let currentMallocPointer = 16;
(globalThis as any)._malloc = (length: int32) => {
    let result = currentMallocPointer
    currentMallocPointer = (currentMallocPointer + length + 3) & ~3
    if (currentMallocPointer > fakeHeap.byteLength) {
        currentMallocPointer = 16
        result = currentMallocPointer
    }
    return result
}
(globalThis as any)._free = (x: int32) => {}
