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

@file:OptIn(ExperimentalForeignApi::class)

package koalaui.interop

import kotlinx.cinterop.*

public open class DeserializerBase {
    private var _position: Int = 0
    private var _length: Int = 96
    private var _buffer: KSerializerBuffer
    private var _finalizable: Finalizable? = null

    constructor(buffer: KSerializerBuffer, length: Int) {
        _buffer = buffer
        _length = length
        _finalizable = Finalizable(buffer, InteropNativeModule._GetMallocFinalizer())
    }

    fun asBuffer(): KSerializerBuffer {
        return _buffer
    }

    fun currentPosition(): Int {
        return _position
    }

    fun resetCurrentPosition(): Unit {
        _position = 0
    }

    private fun checkCapacity(value: Int) {
        if (_position > _length - value) {
            error("DeserializerBase.checkCapacity: remaining buffer length is less than ${value} (position=$_position, length=$_length)")
        }
    }

    fun readInt8(): Int {
        checkCapacity(1)
        val result = (_buffer + _position).toCPointer<ByteVar>()?.get(0) ?: 0
        _position += 1
        return result.toInt()
    }

    fun readInt32(): Int {
        checkCapacity(4)
        val result = (_buffer + _position).toCPointer<IntVar>()?.get(0) ?: 0
        _position += 4
        return result
    }

    fun readInt64(): Long {
        checkCapacity(8)
        val result = (_buffer + _position).toCPointer<LongVar>()?.get(0) ?: 0
        _position += 8
        return result
    }

    fun readPointer(): pointer {
        return readInt64()
    }

    fun readFloat32(): Float {
        checkCapacity(4)
        val result = (_buffer + _position).toCPointer<FloatVar>()?.get(0) ?: 0.0f
        _position += 4
        return result
    }
    fun readFloat64(): Double {
        checkCapacity(8)
        val result = (_buffer + _position).toCPointer<DoubleVar>()?.get(0) ?: 0.0
        _position += 8
        return result
    }

    fun readBoolean(): Boolean {
        checkCapacity(1)
        val result = (_buffer + _position).toCPointer<ByteVar>()?.get(0) ?: 0
        _position += 1
        return result.toInt() == 1
    }

    fun readCallbackResource(): CallbackResource {
        return object: CallbackResource {
            override var resourceId = this@DeserializerBase.readInt32()
            override var hold = this@DeserializerBase.readPointer()
            override var release = this@DeserializerBase.readPointer()
        }
    }

    fun readString(): String {
        val length = readInt32()
        checkCapacity(length)
        val value = InteropNativeModule._Utf8ToString(_buffer, _position, length)
        _position += length
        return value
    }

    fun readCustomObject(kind: String): Any {
        throw Exception("readCustomObject")
    }

    fun readNumber(): Number? {
        val tag = readInt8()
        if (tag == Tag.UNDEFINED.value) {
            return null
        } else if (tag == Tag.INT32.value) {
            return readInt32()
        } else if (tag == Tag.FLOAT32.value) {
            return readFloat32()
        } else {
            throw Exception("Unknown number tag: ${tag}")
        }
    }

    fun readObject(): Any {
        val resource = readCallbackResource()
        return ResourceHolder.get(resource.resourceId)
    }

    fun readBuffer(): NativeBuffer {
        val resource = readCallbackResource()
        val data = readPointer()
        val length = readInt64()
        InteropNativeModule._CallCallbackResourceHolder(resource.hold, resource.resourceId)
        return NativeBuffer(data, length, resource.release)
    }
}
