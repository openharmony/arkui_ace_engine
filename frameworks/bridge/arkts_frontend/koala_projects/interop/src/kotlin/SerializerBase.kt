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

import kotlin.math.roundToInt
import kotlinx.cinterop.*
import platform.posix.memcpy

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

public fun registerCallback(value: Any): Int {
    // TODO: fix me!
    return 42
}

public interface CallbackResource {
    val resourceId: Int
    val hold: pointer
    val release: pointer
}

public data class PromiseResourceIdHolder<T>(val promise: T, val resourceId: ResourceId)

public abstract class CustomSerializer(private val supported: List<String>) {
    var next: CustomSerializer? = null

    fun supports(kind: String): Boolean {
        return supported.contains(kind)
    }
    abstract fun serialize(serializer: SerializerBase, value: Any, kind: String)
}

public class DateSerializer : CustomSerializer(listOf("Date")) {
    override fun serialize(serializer: SerializerBase, value: Any, kind: String) {
        serializer.writeString("Date")
    }
}

public open class SerializerBase {
    private var _position: Int = 0
    private var _length: Int
    private var _buffer: KSerializerBuffer

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
        val length = 96
        _buffer = InteropNativeModule._Malloc(length.toLong())
        _length = length
    }

    fun release() {
        releaseResources()
        _position = 0
        if (this != SerializerBase.pool[SerializerBase.poolTop - 1]) {
            error("Serializers should be release in LIFO order")
        }
        SerializerBase.poolTop -= 1;
    }
    private fun releaseResources() {
        if (heldResourcesCount == 0) return
        for (i in 0..<heldResourcesCount) {
            InteropNativeModule._ReleaseCallbackResource(heldResources[i])
        }
        heldResourcesCount = 0
    }

    companion object {
        private var pool: Array<SerializerBase> = arrayOf<SerializerBase>(
            SerializerBase(),
            SerializerBase(),
            SerializerBase(),
            SerializerBase(),
            SerializerBase(),
            SerializerBase(),
            SerializerBase(),
            SerializerBase(),
        )
        private var poolTop: Int = 0

        fun hold(): SerializerBase {
            if (SerializerBase.poolTop == SerializerBase.pool.size) {
                error("Pool empty! Release one of taken serializers")
            }
            return SerializerBase.pool[SerializerBase.poolTop++]
        }
    }

    fun length(): Int {
        return _position
    }
    fun asBuffer(): KSerializerBuffer {
        return _buffer
    }
    private fun checkCapacity(value: Int) {
        if (value < 1) {
            error("SerializerBase.checkCapacity: checked capacity value must be greater than 0 (passed $value)")
        }
        var buffSize = _length
        if (_position > buffSize - value) {
            val minSize = _position + value;
            val resizedSize = maxOf(minSize, (3.0 * buffSize / 2.0).roundToInt())
            val resizedBuffer = InteropNativeModule._Malloc(resizedSize.toLong())
            val oldBuffer = _buffer
            memcpy(resizedBuffer.toCPointer<CPointed>(), oldBuffer.toCPointer<CPointed>(), _position.toULong())
            _buffer = resizedBuffer
            _length = resizedSize
            InteropNativeModule._Free(oldBuffer)
        }
    }

    private var heldResources: ArrayList<ResourceId> = ArrayList<ResourceId>()
    private var heldResourcesCount: Int = 0
    private fun addHeldResource(resourceId: ResourceId) {
        if (heldResourcesCount == heldResources.size) {
            heldResources.add(resourceId)
        }
        else {
            heldResources[heldResourcesCount] = resourceId
        }
        heldResourcesCount++
    }
    fun holdAndWriteCallback(callback: Any, hold: pointer = 0L, release: pointer = 0L, call: pointer = 0L, callSync: pointer = 0L): ResourceId {
        val resourceId = ResourceHolder.registerAndHold(callback)
        heldResources.add(resourceId)
        writeInt32(resourceId)
        writePointer(hold)
        writePointer(release)
        writePointer(call)
        writePointer(callSync)
        return resourceId
    }
    fun holdAndWriteCallbackForPromiseVoid(hold: pointer = 0L, release: pointer = 0L, call: pointer = 0L): PromiseResourceIdHolder<Unit> {
        val resourceId: ResourceId = 0
        return PromiseResourceIdHolder(Unit, resourceId)
    }
    fun <T>holdAndWriteCallbackForPromise(hold: pointer = 0L, release: pointer = 0L, call: pointer = 0L): PromiseResourceIdHolder<Int> {
        val resourceId: ResourceId = 0
        return PromiseResourceIdHolder(42, resourceId)    
    }
    fun holdAndWriteObject(obj: Any, hold: pointer = 0L, release: pointer = 0L): ResourceId {
        val resourceId = ResourceHolder.registerAndHold(obj)
        addHeldResource(resourceId)
        writeInt32(resourceId)
        writePointer(hold)
        writePointer(release)
        return resourceId
    }
    fun writeCallbackResource(resource: CallbackResource) {
        writeInt32(resource.resourceId)
        writePointer(resource.hold)
        writePointer(resource.release)
    }
    fun writeResource(resource: Any) {
        val resourceId = ResourceHolder.registerAndHold(resource)
        addHeldResource(resourceId)
        writeInt32(resourceId)
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
    fun writeFunction(value: Any) {
        writeInt32(registerCallback(value))
    }
    fun writeTag(tag: Tag) {
        writeInt8(tag.value)
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
    fun writeInt8(value: Int) {
        checkCapacity(1)
        (_buffer + _position).toCPointer<ByteVar>()?.set(0, value.toByte())
        _position += 1
    }
    fun writeInt32(value: Int) {
        checkCapacity(4)
        (_buffer + _position).toCPointer<IntVar>()?.set(0, value)
        _position += 4
    }
    fun writeInt64(value: Long) {
        checkCapacity(8)
        (_buffer + _position).toCPointer<LongVar>()?.set(0, value)
        _position += 8
    }
    fun writeFloat32(value: Float) {
        checkCapacity(4)
        (_buffer + _position).toCPointer<FloatVar>()?.set(0, value)
        _position += 4
    }
    fun writeFloat64(value: Double) {
        checkCapacity(8)
        (_buffer + _position).toCPointer<DoubleVar>()?.set(0, value)
        _position += 8
    }
    fun writePointer(ptr: pointer) {
        checkCapacity(8)
        (_buffer + _position).toCPointer<LongVar>()?.set(0, ptr)
        _position += 8
    }
    fun writeBoolean(value: Boolean?) {
        checkCapacity(1)
        val byteValue = when {
            value == null -> { 5 }
            value -> { 1 }
            else -> { 0 }
        }.toByte()
        (_buffer + _position).toCPointer<ByteVar>()?.set(0, byteValue)
        _position += 1
    }
    fun writeString(value: String) {
        checkCapacity(4 + value.length * 4 + 1)
        val encodedLength = InteropNativeModule._ManagedStringWrite(value, asBuffer(), _position + 4)
        writeInt32(encodedLength)
        _position += encodedLength
    }
    fun writeBuffer(buffer: NativeBuffer) {
        holdAndWriteObject(buffer)
        writePointer(buffer.data)
        writeInt64(buffer.length)
    }
}
