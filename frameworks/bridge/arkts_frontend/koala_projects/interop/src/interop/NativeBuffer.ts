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

import { pointer } from './InteropTypes'
import { int32, int64 } from '@koalaui/common'
import { InteropNativeModule } from "./InteropNativeModule"
import { Finalizable } from './Finalizable'

// stub wrapper for KInteropBuffer
// export type NativeBuffer = ArrayBuffer

export class NativeBuffer {
    public data: pointer
    public length: int64
    protected finalizable: Finalizable

    constructor(length: int64)
    constructor(data: pointer, length: int64, destroy: pointer)
    constructor(dataOrLength: pointer | int64, length_?: int64, destroy_?: pointer) {
        let data: pointer
        let length: int64
        let destroy: pointer
        if (length_ === undefined) {
            length = dataOrLength as int64
            data = InteropNativeModule._Malloc(length)
            destroy = InteropNativeModule._GetMallocFinalizer()
        } else {
            data = dataOrLength as pointer
            length = length_ as int64
            destroy = destroy_ as pointer
        }
        this.data = data
        this.length = length
        this.finalizable = new Finalizable(data, destroy)
    }

    public readByte(index: int64): int32 {
        return InteropNativeModule._ReadByte(this.data, index, BigInt(this.length))
    }

    public writeByte(index: int64, value: int32): void {
        InteropNativeModule._WriteByte(this.data, index, BigInt(this.length), value)
    }
}