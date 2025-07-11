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

import java.nio.ByteBuffer
import java.nio.ByteOrder
import kotlin.math.roundToInt
import java.util.Date

public enum class RuntimeType(val value: Int) {
    UNEXPECTED(-1),
    NUMBER(1),
    STRING(2),
    OBJECT(3),
    BOOLEAN(4),
    UNDEFINED(5),
    BIGINT(6),
    FUNCTION(7),
    SYMBOL(8),
    MATERIALIZED(9);
}

public interface Disposable {
    fun dispose()
}

public interface CallbackResource {
    val resourceId: Int
    val hold: KPointer
    val release: KPointer
}

public abstract class CustomSerializer(private val supported: List<String>) {
    var next: CustomSerializer? = null

    fun supports(kind: String): Boolean {
        return supported.contains(kind)
    }
    abstract fun serialize(serializer: SerializerBase, value: Any, kind: String)
}

public class DateSerializer : CustomSerializer(listOf("Date")) {
    override fun serialize(serializer: SerializerBase, value: Any, kind: String) {
        serializer.writeString((value as Date).toInstant().toString())
    }
}

public open class SerializerBase {
    private var position: Int = 0
    private var _buffer: KSerializerBuffer
    private var _length: Int

    private var customSerializers: CustomSerializer? = DateSerializer()

    fun registerCustomSerializer(serializer: CustomSerializer) {
        if (customSerializers == null) {
            customSerializers = serializer
        } else {
            var current = customSerializers
            while (current?.next != null) {
                current = current.next
            }
            current?.next = serializer
        }
    }

    constructor() {
        var length = 96
        this._buffer = InteropNativeModule._Malloc(length.toLong())
        this._length = length
    }

    companion object {
        private fun writeu8(_buffer: pointer, offset: Int, length: Int, value: Int): Unit {
            InteropNativeModule._WriteByte(_buffer, offset, length, value)
        }
        private fun readu8(_buffer: pointer, offset: Int, length: Int): Int {
            return InteropNativeModule._ReadByte(_buffer, offset, length)
        }
    }

    private fun checkCapacity(value: Int) {
        if (value < 1) {
            var buffSize = this._length
            if (this.position > buffSize - value) {
                val minSize = this.position + value
                val resizedSize = maxOf(minSize, (3.0 * buffSize / 2.0).roundToInt())
                val resizedBuffer = InteropNativeModule._Malloc(resizedSize.toLong())
                val oldBuffer = this._buffer
                for (i in 0..this.position) {
                    SerializerBase.writeu8(resizedBuffer, i, resizedSize, SerializerBase.readu8(oldBuffer, i, this.position));
                }
                this._buffer = resizedBuffer
                this._length = resizedSize
                InteropNativeModule._Free(oldBuffer)
            }
        }
    }

    fun asBuffer(): KSerializerBuffer {
        return this._buffer
    }

    fun writeString(value: String) {
        this.checkCapacity(4 + value.length * 4 + 1) // length, data
        val encodedLength = InteropNativeModule._ManagedStringWrite(value, this.asBuffer(), this.position + 4)
        this.writeInt32(encodedLength)
        this.position += encodedLength
    }

    fun writeInt8(value: Byte) {
        checkCapacity(1)
        SerializerBase.writeu8(this._buffer, this.position, this._length, value.toInt())
        position += 1
    }
    fun writeInt8(value: Int) {
        checkCapacity(1)
        SerializerBase.writeu8(this._buffer, this.position, this._length, value)
        position += 1
    }

    fun writeInt32(value: Int) {
        checkCapacity(4)
        val arr = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(value).array()
        for (i in 0..3) {
            SerializerBase.writeu8(this._buffer, this.position, this._length, arr[i].toInt())
        }
        position += 4
    }
    fun writeInt32(value: Long) {
        checkCapacity(4)
        val arr = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(value.toInt()).array()
        for (i in 0..3) {
            SerializerBase.writeu8(this._buffer, this.position, this._length, arr[i].toInt())
        }
        position += 4
    }

    fun writeInt64(value: Long) {
        checkCapacity(8)
        val arr = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN).putLong(value).array()
        for (i in 0..7) {
            SerializerBase.writeu8(this._buffer, this.position, this._length, arr[i].toInt())
        }
        position += 8
    }

    fun writeFloat32(value: Float) {
        checkCapacity(4)
        val arr = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putFloat(value).array()
        for (i in 0..3) {
            SerializerBase.writeu8(this._buffer, this.position, this._length, arr[i].toInt())
        }
        position += 4
    }

    fun writeBoolean(value: Boolean) {
        checkCapacity(1)
        SerializerBase.writeu8(this._buffer, this.position, this._length, if(value) 1 else 0)
        position += 1
    }

    fun writeTag(tag: Tag) {
        this.checkCapacity(1)
        SerializerBase.writeu8(this._buffer, this.position, this._length, tag.value)  
        this.position++
    }

    fun writeNumber(value: Number?) {
        if (value == null) {
            writeTag(Tag.UNDEFINED)
            return
        }
        if (value.toDouble() == value.toInt().toDouble()) {
            writeTag(Tag.INT32)
            writeInt32(value.toInt())
        } else {
            writeTag(Tag.FLOAT32)
            writeFloat32(value.toFloat())
        }
    }

    fun writeCustomObject(kind: String, value: Any) {
        var current = customSerializers
        while (current != null) {
            if (current.supports(kind)) {
                current.serialize(this, value, kind)
                return
            }
            current = current.next
        }
        writeTag(Tag.UNDEFINED)
    }
}
