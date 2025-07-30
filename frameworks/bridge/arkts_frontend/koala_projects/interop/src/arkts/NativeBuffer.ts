/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { pointer, KSerializerBuffer, nullptr } from './InteropTypes'
import { int32, int64 } from '@koalaui/common'
import { InteropNativeModule } from "./InteropNativeModule"

// stub wrapper for KInteropBuffer
export final class NativeBuffer {
    public data:pointer = 0
    public length: int64 = 0
    public resourceId: int32 = 0
    public hold:pointer = 0
    public release: pointer = 0

    constructor(data:pointer, length: int64, resourceId: int32, hold:pointer, release: pointer) {
        this.data = data
        this.length = length
        this.resourceId = resourceId
        this.hold = hold
        this.release = release
    }

    public readByte(index:int32): int32 {
        return InteropNativeModule._ReadByte(this.data, index, this.length)
    }

    public writeByte(index:int32, value: int32): void {
        InteropNativeModule._WriteByte(this.data, index, this.length, value)
    }

    static wrap(data:pointer, length: int64, resourceId: int32, hold:pointer, release: pointer): NativeBuffer {
        return new NativeBuffer(data, length, resourceId, hold, release)
    }
}

export class KBuffer {
    private _buffer: KSerializerBuffer
    private readonly _length: int64
    private readonly _owned: boolean
    constructor(length: int64) {
       this._buffer = InteropNativeModule._Malloc(length)
       this._length = length
       this._owned = true
    }
    constructor(buffer: KSerializerBuffer, length: int64) {
        this._buffer = buffer
        this._length = length
        this._owned = false
    }

    dispose(): void {
        if (this._owned && this._buffer != nullptr) {
            InteropNativeModule._Free(this._buffer)
            this._buffer = nullptr
        }
    }

    public get buffer(): KSerializerBuffer {
        return this._buffer
    }

    public get length(): int64 {
        return this._length
    }

    public get(index: int64): byte {
        return InteropNativeModule._ReadByte(this._buffer, index, this._length) as byte
    }
    public set(index: int64, value: byte): void {
        InteropNativeModule._WriteByte(this._buffer, index, this._length, value)
    }
}