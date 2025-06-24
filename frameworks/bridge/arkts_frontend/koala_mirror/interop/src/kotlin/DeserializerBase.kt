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
package interop

public open class DeserializerBase {
    private var position: Int = 0
    var length: Int = 96 // make private
    var buffer: pointer // make private

    constructor(buffer: ULong, length: Int) {
        this.buffer = buffer
        this.length = length
    }
    constructor(buffer: Array<UByte>, length: Int) {
        this.buffer = InteropNativeModule._Malloc(length.toLong())
        for (i in 0..length) {
            DeserializerBase.writeu8(this.buffer, i, length, buffer[i])
        }
        this.length = length
    }

    companion object {
        private fun writeu8(buffer: pointer, offset: Int, length: Int, value: UByte): Unit {
            InteropNativeModule._WriteByte(buffer, offset, length, value.toInt())
        }
        private fun readu8(buffer: pointer, offset: Int, length: Int): Int {
            return InteropNativeModule._ReadByte(buffer, offset, length)
        }
    }

    public fun asBuffer(): pointer {
        return this.buffer
    }

    public fun currentPosition(): Int {
        return this.position
    }

    public fun resetCurrentPosition(): Unit {
        this.position = 0
    }

    private fun checkCapacity(value: Int) {
        if (value > this.length) {
            throw Exception("${value} is less than remaining buffer length")
        }
    }

    public fun readInt8(): Byte {
        this.checkCapacity(1)
        var res = DeserializerBase.readu8(this.buffer, this.position, this.length)
        this.position += 1
        return res.toByte()
    }

    public fun readInt32(): Int {
        this.checkCapacity(4)
        var result: Int = 0
        for (i in 0..3) {
            result = result or (DeserializerBase.readu8(this.buffer, this.position + i, this.length) shl (8 * i))
        }
        this.position += 4
        return result
    }

    public fun readInt64(): Long {
        this.checkCapacity(8)
        var result: Long = 0
        for (i in 0..7) {
            result = result or (DeserializerBase.readu8(this.buffer, this.position + i, this.length).toLong() shl (8 * i))
        }
        this.position += 8
        return result
    }

    public fun readPointer(): KPointer {
        this.checkCapacity(8)
        var result: ULong = 0uL
        for (i in 0..7) {
            result = result or (DeserializerBase.readu8(this.buffer, this.position + i, this.length).toULong() shl (8 * i))
        }
        this.position += 8
        return result
    }

    public fun readFloat32(): Float {
        this.checkCapacity(4)
        var result: Int = 0
        for (i in 0..3) {
            result = result or (DeserializerBase.readu8(this.buffer, this.position + i, this.length).toInt() shl (8 * i))
        }
        this.position += 4
        return Float.fromBits(result)
    }
    public fun readFloat64(): Double {
        this.checkCapacity(8)
        var result: Long = 0
        for (i in 0..7) {
            result = result or (DeserializerBase.readu8(this.buffer, this.position + i, this.length).toLong() shl (8 * i))
        }
        this.position += 8
        return Double.fromBits(result)
    }

    public fun readBoolean(): Boolean {
        var byteVal = DeserializerBase.readu8(this.buffer, this.position, this.length)
        this.position += 1
        return byteVal == 1
    }

    public fun readString(): String {
        val length = this.readInt32()
        this.checkCapacity(length)
        // read without null-terminated byte
        val value = InteropNativeModule._Utf8ToString(this.buffer, this.position, length)
        this.position += length
        return value
    }

    public fun readCustomObject(kind: String): Object {
        throw Exception("readCustomObject")
    }

    public fun readObject(): Any {
        val resource = this.readCallbackResource()
        return ResourceHolder.instance() // .get(resource.resourceId)
    }

    public fun readBuffer(): UIntArray {
        return UIntArray(0)
    }

    public fun readFunction(): Any {
        return 0
    }

    public fun readNumber(): Number {
        val tag = this.readInt8().toInt()
        if (tag == Tag.UNDEFINED.value) {
            throw Exception("Read number can't return undefined.")
        } else if (tag == Tag.INT32.value) {
            return this.readInt32()
        } else if (tag == Tag.FLOAT32.value) {
            return this.readFloat32()
        } else {
            throw Exception("Unknown number tag: ${tag}")
        }
    }

    public fun readCallbackResource(): CallbackResource {
        return object: CallbackResource {
            override var resourceId = this@DeserializerBase.readInt32()
            override var hold = this@DeserializerBase.readPointer()
            override var release = this@DeserializerBase.readPointer()
        }
    }
}
