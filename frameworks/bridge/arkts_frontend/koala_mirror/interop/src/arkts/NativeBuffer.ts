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
import { Disposable } from "./ResourceManager"
import { Finalizable } from './Finalizable'

export final class NativeBuffer {
    public data: pointer
    public length: int64
    protected finalizable: Finalizable

    constructor(length: int64) {
        this(InteropNativeModule._Malloc(length), length, InteropNativeModule._GetMallocFinalizer())
    }

    constructor(data: pointer, length: int64, destroy: pointer) {
        this.data = data
        this.length = length
        this.finalizable = new Finalizable(data, destroy)
    }

    public readByte(index:int64): int32 {
        return unsafeMemory.readInt8(this.data + index)
    }

    public writeByte(index:int64, value: int32): void {
        unsafeMemory.writeInt8(this.data + index, value as byte)
    }
}

export class KBuffer implements Disposable {
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
        return unsafeMemory.readInt8(this._buffer + index)
    }
    public set(index: int64, value: byte): void {
        unsafeMemory.writeInt8(this._buffer + index, value)
    }
}