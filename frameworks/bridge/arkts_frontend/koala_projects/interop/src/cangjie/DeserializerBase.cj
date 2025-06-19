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
package Interop

import std.binary.*
import std.collection.*

public class CallbackResource {
    public var resourceId: Int32
    public var hold: pointer
    public var release: pointer
    init(resourceId: Int32, hold: pointer, release: pointer) {
        this.resourceId = resourceId
        this.hold = hold
        this.release = release
    }
}

public open class DeserializerBase {
    private var position = 0
    private var length = 96
    private var buffer: Array<UInt8>

    public init(buffer: Array<UInt8>, length: Int64) {
        this.buffer = buffer
        this.length = length
    }

    public func asArray(position: Int64, length: Int64): ArrayList<UInt8> {
        return ArrayList<UInt8>()
    }

    public func currentPosition(): Int64 {
        return this.position
    }

    public func resetCurrentPosition(): Unit {
        this.position = 0
    }

    private func checkCapacity(value: Int64) {
        if (value > this.length) {
            throw Exception("${value} is less than remaining buffer length")
        }
    }

    public func readInt8(): Int8 {
        this.checkCapacity(1)
        let res = Int8.readLittleEndian(this.buffer[this.position..this.position+1])
        this.position += 1
        return res
    }

    public func readInt32(): Int32 {
        this.checkCapacity(4)
        let res = Int32.readLittleEndian(this.buffer[this.position..this.position+4])
        this.position += 4
        return res
    }

    public func readInt64(): Int64 {
        this.checkCapacity(8)
        let res = Int64.readLittleEndian(this.buffer[this.position..this.position+8])
        this.position += 8
        return res
    }

    public func readPointer(): KPointer {
        this.checkCapacity(8)
        let res = UInt64.readLittleEndian(this.buffer[this.position..this.position+8])
        this.position += 8
        return res
    }

    public func readFloat32(): Float32 {
        this.checkCapacity(4)
        let res = Float32.readLittleEndian(this.buffer[this.position..this.position+4])
        this.position += 4
        return res
    }

    public func readBoolean(): Bool {
        let res = Bool.readLittleEndian(this.buffer[this.position..this.position+1])
        this.position += 1
        return res
    }

    // readMaterialized(): object {
    //     const ptr = this.readPointer()
    //     return { ptr: ptr }
    // }

    public func readString(): String {
        let length = Int64(this.readInt32())
        this.checkCapacity(length)
        // read without null-terminated byte
        let value = InteropNativeModule._Utf8ToString(this.buffer.toArray(), Int32(this.position), Int32(length))
        this.position += length
        return value
    }

    public func readCustomObject(kind: String): Object{
        throw Exception("readCustomObject")
    }

    public func readNumber(): Float64 {
        let tag = this.readInt8()
        if (tag == Tag.UNDEFINED.value) {
            throw Exception("Read number can't return undefined.")
        } else if (tag == Tag.INT32.value) {
            return Float64(this.readInt32())
        } else if (tag == Tag.FLOAT32.value) {
            return Float64(this.readFloat32())
        } else {
            throw Exception("Unknown number tag: ${tag}")
        }
    }

    public func readCallbackResource(): CallbackResource {
        return CallbackResource(this.readInt32(), this.readPointer(), this.readPointer())
    }
}
