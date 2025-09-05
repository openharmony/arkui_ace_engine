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
import std.math.*   
import std.collection.*

public enum RuntimeType {
    |UNEXPECTED
    |NUMBER
    |STRING
    |OBJECT
    |BOOLEAN
    |UNDEFINED
    |BIGINT
    |FUNCTION
    |SYMBOL
    |MATERIALIZED
    public prop ordinal: Int32 {
        get() {
            match (this) {
                case UNEXPECTED => -1
                case NUMBER => 1
                case STRING => 2
                case OBJECT => 3
                case BOOLEAN => 4
                case UNDEFINED => 5
                case BIGINT => 6
                case FUNCTION => 7
                case SYMBOL => 8
                case MATERIALIZED => 9
            }
        }
    }
}

public class PromiseAndResourceId<T> {
    public var promise: Any
    public var resourceId: ResourceId
    init (promise: Any, resourceId: ResourceId) {
        this.promise = promise
        this.resourceId = resourceId
    }
}


/* Serialization extension point */
public abstract class CustomSerializer {
    public var supported: Array<String>
    init(supported: Array<String>) {
        this.supported = supported
    }
    public func supports(kind: String): Bool { return this.supported.contains(kind) }
    public func serialize(serializer: SerializerBase, value: Object, kind: String): Unit {}
    var next: ?CustomSerializer = Option.None
}

public open class SerializerBase {
    private var position: Int32 = 0
    private var _buffer: pointer
    private var _length: Int32

    private static var customSerializers: ?CustomSerializer = Option.None
    static func registerCustomSerializer(serializer: CustomSerializer) {
        // Improve:
    }

    public init() {
        let length: Int32 = 96
        this._buffer = InteropNativeModule._Malloc(length)
        this._length = length
    }

    private static func writeu8(_buffer: pointer, offset: Int32, length: Int32, value: Int32): Unit {
        InteropNativeModule._WriteByte(_buffer, Int64(offset), Int64(length), value)
    }
    private static func readu8(_buffer: pointer, offset: Int32, length: Int32): Int32 {
        return InteropNativeModule._ReadByte(_buffer, Int64(offset), Int64(length))
    }

    public open func release() {
        this.releaseResources()
        this.position = 0
    }
    private func releaseResources() {
        if (this.heldResourcesCount == 0) {
            return
        }
        for (i in 0..this.heldResourcesCount) {
            InteropNativeModule._ReleaseCallbackResource(this.heldResources[i])
        }
        this.heldResourcesCount = 0
    }
    public func asBuffer(): KSerializerBuffer {
        this._buffer
    }
    public func length(): Int32 {
        return Int32(this.position)
    }
    public func currentPosition(): Int32 { return this.position }
    private func checkCapacity(value: Int32) {
        if (value < 1) {
            throw Exception("${value} is less than 1")
        }
        var buffSize = this._length
        if (this.position > buffSize - value) {
            let minSize: Int32 = this.position + value
            let resizedSize: Int32 = max<Int32>(minSize, Int32(round(1.5 * Float64(buffSize))))
            let resizedBuffer = InteropNativeModule._Malloc(resizedSize)
            let oldBuffer = this._buffer
            for (i in 0..this.position) {
                SerializerBase.writeu8(resizedBuffer, Int32(i), resizedSize, SerializerBase.readu8(oldBuffer, i, this.position))
            }
            this._buffer = resizedBuffer
            this._length = resizedSize
            InteropNativeModule._Free(oldBuffer)
        }
    }
    public func writeCustomObject(kind: String, value: Any): Unit {
        var current = SerializerBase.customSerializers
        // Improve:
        println("Unsupported custom serialization for ${kind}, write undefined")
        this.writeInt8(Tag.UNDEFINED.value)
    }

    private var heldResources: ArrayList<ResourceId> = ArrayList<ResourceId>()
    private var heldResourcesCount: Int64 = 0
    private func addHeldResource(resourceId: ResourceId) {
        if (this.heldResourcesCount == this.heldResources.size) {
            this.heldResources.add(resourceId)
        }
        else {
            this.heldResources[this.heldResourcesCount] = resourceId
        }
        this.heldResourcesCount += 1
    }

    public func holdAndWriteCallback(callback: Any): ResourceId {
        let resourceId = ResourceHolder.instance().registerAndHold(callback)
        this.heldResources.add(resourceId)
        this.writeInt32(resourceId)
        this.writePointer(0)
        this.writePointer(0)
        this.writePointer(0)
        this.writePointer(0)
        return resourceId
    }
    public func holdAndWriteCallback(callback: Any, hold: KPointer, release: KPointer, call: KPointer, callSync: KPointer): ResourceId {
        let resourceId = ResourceHolder.instance().registerAndHold(callback)
        this.heldResources.add(resourceId)
        this.writeInt32(resourceId)
        this.writePointer(hold)
        this.writePointer(release)
        this.writePointer(call)
        this.writePointer(callSync)
        return resourceId
    }
    public func holdAndWriteCallbackForPromiseVoid(): PromiseAndResourceId<Unit> {
        return holdAndWriteCallbackForPromiseVoid(0, 0, 0, 0)
    }
    public func holdAndWriteCallbackForPromiseVoid(hold: KPointer, release: KPointer, call: KPointer, callSync: KPointer): PromiseAndResourceId<Unit> {
        var resourceId: ResourceId = 0
        let promise = { => }
        return PromiseAndResourceId<Unit>(promise, resourceId)
    }
    public func holdAndWriteCallbackForPromise<T>(): PromiseAndResourceId<T> {
        return holdAndWriteCallbackForPromise<T>(0, 0, 0)
    }
    public func holdAndWriteCallbackForPromise<T>(hold: KPointer, release: KPointer, call: KPointer): PromiseAndResourceId<T> {
        var resourceId: ResourceId = 0
        let promise = { => }
        return PromiseAndResourceId<T>(promise, resourceId)
    }
    public func writeFunction(value: Any): Unit {
        // Improve:
    }
    public func writeTag(tag: Int32): Unit {
        this.checkCapacity(1)
        SerializerBase.writeu8(this._buffer, this.position, this._length, tag)  
        this.position++
    }
    public func writeTag(tag: Int8): Unit {
        this.checkCapacity(1)
        SerializerBase.writeu8(this._buffer, this.position, this._length, Int32(tag))
        this.position++
    }
    public func writeNumber(value: ?Float32): Unit {
        if (let Some(value) <- value) {
            if(value == Float32(Int32(value))) {
                this.writeNumber(Int32(value))
            } else {
                this.writeTag(Tag.FLOAT32.value)
                this.writeInt32(Int64(value.toBits()))
            }
        }
        else {
            this.writeTag(Tag.UNDEFINED.value)
        }
    }
    public func writeNumber(value: ?Float64): Unit {
        if (let Some(value) <- value) {
            if(value == Float64(Int32(value))) {
                this.writeNumber(Int32(value))
            } else {
                this.writeTag(Tag.FLOAT32.value)
                this.writeInt32(Int64(Float32(value).toBits()))
            }
        }
        else {
            this.writeTag(Tag.UNDEFINED.value)
        }
    }
    public func writeNumber(value: ?Int32): Unit {
        if (let Some(value) <- value) {
            this.writeTag(Tag.INT32.value)
            this.writeInt32(Int32(value))
        }
        else {
            this.writeTag(Tag.UNDEFINED.value)
        }
    }
    public func writeNumber(value: ?Int64): Unit {
        this.checkCapacity(5)
        if (let Some(value) <- value) {
            this.writeTag(Tag.INT32.value)
            this.writeInt32(Int32(value))
        }
        else {
            this.writeTag(Tag.UNDEFINED.value)
        }
    }
    public func writeInt8(value: Int8): Unit {
        this.checkCapacity(1)
        SerializerBase.writeu8(this._buffer, this.position, this._length, Int32(value))
        this.position += 1
    }
    public func writeInt8(value: Int32): Unit {
        this.checkCapacity(1)
        SerializerBase.writeu8(this._buffer, this.position, this._length, Int32(value))
        this.position += 1
    }
    public func writeInt32(value: Int32): Unit {
        this.checkCapacity(4)
        let arr = Array<UInt8>(4, repeat: 0)
        value.writeLittleEndian(arr)
        for (idx in 0..4) {
            SerializerBase.writeu8(this._buffer, this.position + Int32(idx), this._length, Int32(arr[idx]))
        }
        this.position += 4
    }
    public func writeInt32(value: Int64): Unit {
        this.checkCapacity(4)
        let arr = Array<UInt8>(4, repeat: 0)
        Int32(value).writeLittleEndian(arr)
        for (idx in 0..4) {
            SerializerBase.writeu8(this._buffer, this.position + Int32(idx), this._length, Int32(arr[idx]))
        }
        this.position += 4
    }
    public func writeInt64(value: Int64): Unit {
        this.checkCapacity(8)
        let arr = Array<UInt8>(8, repeat: 0)
        value.writeLittleEndian(arr)
        for (idx in 0..8) {
            SerializerBase.writeu8(this._buffer, this.position + Int32(idx), this._length, Int32(arr[idx]))
        }
        this.position += 8
    }
    public func writeFloat32(value: Float32): Unit {
        this.checkCapacity(4)
        this.position += 4
    }
    public func writePointer(ptr: UInt64): Unit {
        this.checkCapacity(8)
        let arr = Array<UInt8>(8, repeat: 0)
        ptr.writeLittleEndian(arr)
        for (idx in 0..8) {
            SerializerBase.writeu8(this._buffer, this.position + Int32(idx), this._length, Int32(arr[idx]))
        }
        this.position += 8
    }
    public func writeBoolean(value: ?Bool): Unit {
        this.checkCapacity(1)
        if(let Some(value) <- value) {
            SerializerBase.writeu8(this._buffer, this.position, this._length, if (value) {1} else {0})
        }
        else {
            SerializerBase.writeu8(this._buffer, this.position, this._length, RuntimeType.UNDEFINED.ordinal)
        }
        this.position++
    }
    public func writeMaterialized(value: Object): Unit {
        // Improve:
    }
    public func writeCallbackResource(resource: CallbackResource) {
        this.writeInt32(resource.resourceId)
        this.writePointer(resource.hold)
        this.writePointer(resource.release)
    }
    public func writeString(value: String): Unit {
        this.checkCapacity(Int32(4 + value.size * 4 + 1)) // length, data
        let encodedLength = InteropNativeModule._ManagedStringWrite(value, this.asBuffer(), this._length, this.position + 4)
        this.writeInt32(encodedLength)
        this.position += encodedLength
    }
    public func writeBuffer(_buffer: Array<UInt8>) {
        // let resourceId = ResourceHolder.instance().registerAndHold(_buffer)
        // this.writeCallbackResource(CallbackResource(resourceId, 0, 0))
        // unsafe {
        //     let ptr = acquireArrayRawData(_buffer).pointer
        //     this.writePointer(UInt64(ptr.toUIntNative()))
        //     this.writeInt64(_buffer.size)
        // }
    }
    public func holdAndWriteObject(obj: Any): ResourceId {
        return this.holdAndWriteObject(obj, 0, 0)
    }
    public func holdAndWriteObject(obj: Any, hold: pointer, release: pointer): ResourceId {
        let resourceId = ResourceHolder.instance().registerAndHold(obj)
        this.addHeldResource(resourceId)
        this.writeInt32(resourceId)
        this.writePointer(hold)
        this.writePointer(release)
        return resourceId
    }
}

public open class DateCustomSerializer <: CustomSerializer {
    public DateCustomSerializer() {
        super(["Date"])
    }
    public func serialize(serializer: SerializerBase, value: Ark_CustomObject, kind: String): Unit {
        serializer.writeString("{}")
    }
}

public open class Ark_CustomObject {
    init() {
        SerializerBase.registerCustomSerializer(DateCustomSerializer())     
    }
}
