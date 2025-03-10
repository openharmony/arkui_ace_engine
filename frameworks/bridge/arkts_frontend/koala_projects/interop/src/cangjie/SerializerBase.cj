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
import std.reflect.*
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
    protected var isHolding: Bool = false
    private var position: Int64 = 0
    private var buffer: ArrayList<UInt8> = ArrayList<UInt8>()

    private static var customSerializers: ?CustomSerializer = Option.None
    static func registerCustomSerializer(serializer: CustomSerializer) {
        //TODO
    }

    public init() {
        this.buffer = ArrayList<UInt8>(Array<UInt8>(96, repeat: UInt8(0)))
    }
    public open func release() {
        this.isHolding = false
        // todo handle release resources
        this.position = 0
    }
    public func asArray(): ArrayList<UInt8> {
        return this.buffer
    }
    public func length(): Int32 {
        return Int32(this.position)
    }
    public func currentPosition(): Int64 { return this.position }
    private func checkCapacity(value: Int64) {
        if (value < 1) {
            throw Exception("${value} is less than 1")
        }
        var buffSize = this.buffer.size
        if (this.position > buffSize - value) {
            let minSize = this.position + value
            let resizedSize = max(minSize, Int64(round(3.0 * Float64(buffSize) / 2.0)))
            var resizedBuffer =  ArrayList<UInt8>(this.buffer)
            while (resizedBuffer.size < resizedSize) {
                resizedBuffer.add(0)
            }
            this.buffer = resizedBuffer
        }
    }
    public func writeCustomObject(kind: String, value: Any): Unit {
        var current = SerializerBase.customSerializers
        // TODO
        println("Unsupported custom serialization for ${kind}, write undefined")
        this.writeInt8(Tag.UNDEFINED.value)
    }
    private var heldResources: ArrayList<ResourceId> = ArrayList<ResourceId>()
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
        // TODO
    }
    private func setBytes<V, T>(position: Int64, value: T): Unit where T <: LittleEndianOrder<V>{
        var arr = Array<Byte>(100, repeat: 0)
        let n = value.writeLittleEndian(arr)
        this.checkCapacity(n)
        for (i in 0..n) {
            this.buffer[this.position + i] = arr[i]
        }
        this.position += n
    }
    public func writeTag(tag: Int32): Unit {
        this.setBytes(this.position, tag)
    }
    public func writeNumber(value: ?Float32): Unit {
        if (let Some(value) <- value) {
            if(value == Float32(Int32(value))) {
                this.writeNumber(Int32(value))
            } else {
                this.setBytes(this.position, Tag.FLOAT32.value)
                this.setBytes(this.position, value)
            }
        }
        else {
            this.buffer[Int64(this.position)] = UInt8(RuntimeType.UNDEFINED.ordinal)
            this.position++
        }
    }
    public func writeNumber(value: ?Float64): Unit {
        if (let Some(value) <- value) {
            if(value == Float64(Int32(value))) {
                this.writeNumber(Int32(value))
            } else {
                this.setBytes(this.position, Tag.FLOAT32.value)
                this.setBytes(this.position, Float32(value))
            }
        }
        else {
            this.buffer[Int64(this.position)] = UInt8(RuntimeType.UNDEFINED.ordinal)
            this.position++
        }
    }
    public func writeNumber(value: ?Int32): Unit {
        if (let Some(value) <- value) {
            this.setBytes(this.position, Tag.INT32.value)
            this.setBytes(this.position, value)
            }
        else {
            this.buffer[Int64(this.position)] = UInt8(RuntimeType.UNDEFINED.ordinal)
            this.position++
        }
    }
    public func writeNumber(value: ?Int64): Unit {
        if (let Some(value) <- value) {
            this.setBytes(this.position, Tag.INT32.value)
            this.setBytes(this.position, Int32(value))
        }
        else {
            this.buffer[Int64(this.position)] = UInt8(RuntimeType.UNDEFINED.ordinal)
            this.position++
        }
    }
    public func writeInt8(value: Int8): Unit {
        this.setBytes(this.position, value)
    }
    public func writeInt8(value: Int32): Unit {
        this.setBytes(this.position, Int8(value))
    }
    public func writeInt32(value: Int32): Unit {
        this.setBytes(this.position, Int32(value))
    }
    public func writeInt64(value: Int64): Unit {
        this.setBytes(this.position, Int64(value))
    }
    public func writeFloat32(value: Float32): Unit {
        this.setBytes(this.position, value)
    }
    public func writePointer(ptr: UInt64): Unit {
        this.setBytes(this.position, ptr)
    }
    public func writeBoolean(value: ?Bool): Unit {
        this.checkCapacity(1)
        if(let Some(value) <- value) {
            this.setBytes(this.position, value)
        }
        else {
            this.buffer[Int64(this.position)] = UInt8(RuntimeType.UNDEFINED.ordinal)
            this.position++
        }
    }
    public func writeMaterialized(value: Object): Unit {
        // TODO
    }
    public func writeCallbackResource(resource: CallbackResource) {
        this.writeInt32(resource.resourceId)
        this.writePointer(resource.hold)
        this.writePointer(resource.release)
    }
    public func writeString(value: String): Unit {
        this.checkCapacity(4 + value.size * 4 + 1) // length, data
        this.writeInt32(Int32(value.size + 1))
        for (i in 0..value.size) {
            this.setBytes(this.position, value[i])
        }
        this.writeInt8(Int8(0))
    }
    public func writeBuffer(buffer: Array<UInt8>) {
        let resourceId = ResourceHolder.instance().registerAndHold(buffer)
        this.writeCallbackResource(CallbackResource(resourceId, 0, 0))
        unsafe {
            let ptr = acquireArrayRawData(buffer).pointer
            this.writePointer(UInt64(ptr.toUIntNative()))
            this.writeInt64(buffer.size)
        }
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
