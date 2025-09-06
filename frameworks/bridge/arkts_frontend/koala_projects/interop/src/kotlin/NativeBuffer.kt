/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

package koalaui.interop

public class NativeBuffer {
    public var data: pointer
    public var length: Long
    var finalizable: Finalizable

    constructor(length: Long) {
        this.data = InteropNativeModule._Malloc(length)
        this.length = length
        var destroy = InteropNativeModule._GetMallocFinalizer()
        this.finalizable = Finalizable(data, destroy)
    }

    constructor(data: pointer, length: Long, destroy: pointer) {
        this.data = data
        this.length = length
        this.finalizable = Finalizable(data, destroy)
    }

    public fun readByte(index: Long): Int {
        return InteropNativeModule._ReadByte(this.data, index, this.length)
    }

    public fun writeByte(index: Long, value: Int) {
        InteropNativeModule._WriteByte(this.data, index, this.length, value)
    }
}
