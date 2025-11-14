/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
import { float32, int32, int64 } from "@koalaui/common"
import { pointer, nullptr, KSerializerBuffer } from "./InteropTypes"
import { ResourceId, ResourceHolder, Disposable } from "./ResourceManager"
import { NativeBuffer } from "./NativeBuffer"
import { InteropNativeModule } from "./InteropNativeModule"
import { MaterializedBase } from "./MaterializedBase"

/**
 * Value representing possible JS runtime object type.
 * Must be synced with "enum RuntimeType" in C++.
 */
export final class RuntimeType {
    static readonly UNEXPECTED = -1
    static readonly NUMBER = 1
    static readonly STRING = 2
    static readonly OBJECT = 3
    static readonly BOOLEAN = 4
    static readonly UNDEFINED = 5
    static readonly BIGINT = 6
    static readonly FUNCTION = 7
    static readonly SYMBOL = 8
    static readonly MATERIALIZED = 9
}

export function registerCallback(value: object): int32 {
    throw new Error("Should no longer be used")
}

/**
 * Value representing object type in serialized data.
 * Must be synced with "enum Tags" in C++.
 */
export enum Tags {
    UNDEFINED = 101,
    INT32 = 102,
    FLOAT32 = 103,
    STRING = 104,
    LENGTH = 105,
    RESOURCE = 106,
    OBJECT = 107,
}

const VALUE_TRUE: number = 1
const VALUE_FALSE: number = 0

export function runtimeType<T>(value: T): int32 {
    if (value === undefined)
        return RuntimeType.UNDEFINED;

    if (value === null)
        return RuntimeType.OBJECT;

    if (value instanceof String)
        return RuntimeType.STRING

    if (value instanceof Numeric)
        return RuntimeType.NUMBER

    if (value instanceof Boolean)
        return RuntimeType.BOOLEAN

    if (value instanceof BigInt)
        return RuntimeType.BIGINT

    if (value instanceof Function)
        return RuntimeType.FUNCTION

    // slow workaround for enum
    const typeName = typeof value
    if (typeName == "number")
      return RuntimeType.NUMBER

    if (typeName == "string")
      return RuntimeType.STRING

    return RuntimeType.OBJECT
}

export function toPeerPtr(value: object): pointer {
    if (value instanceof MaterializedBase) {
        const peer = (value as MaterializedBase).getPeer()
        return peer ? peer.ptr : nullptr
    } else {
        throw new Error("Value is not a MaterializedBase instance")
    }
}

export interface CallbackResource {
    resourceId: int32
    hold: pointer
    release: pointer
}

/* Serialization extension point */
export abstract class CustomSerializer {
    protected supported: Array<string>
    constructor(supported: Array<string>) {
        this.supported = supported
    }
    supports(kind: string): boolean { return this.supported.includes(kind) }
    abstract serialize(serializer: SerializerBase, value: object, kind: string): void
    next: CustomSerializer | undefined = undefined
}

class DateSerializer extends CustomSerializer {
    constructor() {
        super(new Array<string>("Date"))
    }

    serialize(serializer: SerializerBase, value: object, kind: string): void {
        serializer.writeString((value as Date).toISOString())
    }
}
SerializerBase.registerCustomSerializer(new DateSerializer())

export class SerializerBase implements Disposable {
    private _position: int64 = 0
    private _buffer: KSerializerBuffer
    private _length: int32
    private _last: int64

    private static pool: SerializerBase[] = [
        new SerializerBase(),
        new SerializerBase(),
        new SerializerBase(),
        new SerializerBase(),
        new SerializerBase(),
        new SerializerBase(),
        new SerializerBase(),
        new SerializerBase(),
    ]
    private static poolTop = 0

    static hold(): SerializerBase {
        if (SerializerBase.poolTop === SerializerBase.pool.length) {
            SerializerBase.pool.push(new SerializerBase())
        }
        return SerializerBase.pool[SerializerBase.poolTop++]
    }

    private static customSerializers: CustomSerializer | undefined = new DateSerializer()
    static registerCustomSerializer(serializer: CustomSerializer) {
        if (SerializerBase.customSerializers == undefined) {
            SerializerBase.customSerializers = serializer
        } else {
            let current = SerializerBase.customSerializers
            while (current!.next != undefined) {
                current = current!.next
            }
            current!.next = serializer
        }
    }

    constructor() {
        let length = 96
        this._buffer = InteropNativeModule._Malloc(length.toLong())
        this._length = length
        this._position = this._buffer
        this._last = this._buffer + length - 1;
    }

    public release() {
        this.releaseResources()
        this._position = this._buffer
        if (this !== SerializerBase.pool[SerializerBase.poolTop - 1]) {
            throw new Error("Serializers should be release in LIFO order")
        }
        SerializerBase.poolTop--
    }
    public final dispose() {
        InteropNativeModule._Free(this._buffer)
        this._buffer = nullptr
    }

    final asBuffer(): KSerializerBuffer {
        return this._buffer
    }
    final length(): int32 {
        return (this._position - this._buffer).toInt()
    }

    final toArray(): byte[] {
        const len = this.length()
        let result = new byte[len]
        for (let i = 0; i < len; i++) {
            result[i] = unsafeMemory.readInt8(this._buffer + i)
        }
        return result
    }

    private final updateCapacity(value: int32) {
        let buffSize = this._length
        const minSize = buffSize + value
        const resizedSize = Math.max(minSize, Math.round(3 * buffSize / 2)).toInt()
        if (value <= 0 || resizedSize <= 0) {
            throw new Error(`bug: value(${value}) resizedSize(${resizedSize}) is illegal`)
        }
        let resizedBuffer = InteropNativeModule._Malloc(resizedSize)
        let oldBuffer = this._buffer
        let offset = this._position - oldBuffer;
        for (let i = 0; i < offset; i++) {
            let val = unsafeMemory.readInt8(oldBuffer + i);
            unsafeMemory.writeInt8(resizedBuffer + i, val)
        }
        this._buffer = resizedBuffer
        this._position = this._position - oldBuffer + resizedBuffer
        this._length = resizedSize
        this._last = resizedBuffer + resizedSize - 1;
        InteropNativeModule._Free(oldBuffer)
    }

    private heldResources: Array<ResourceId> = new Array<ResourceId>()
    private heldResourcesCount: int32 = 0
    private final addHeldResource(resourceId: ResourceId) {
        if (this.heldResourcesCount == this.heldResources.length)
            this.heldResources.push(resourceId)
        else
            this.heldResources[this.heldResourcesCount] = resourceId
        this.heldResourcesCount++
    }
    final holdAndWriteCallback(callback: object, hold: pointer = 0, release: pointer = 0, call: pointer = 0, callSync: pointer = 0): ResourceId {
        const resourceId = ResourceHolder.instance().registerAndHold(callback)
        this.addHeldResource(resourceId)
        this.writeInt32(resourceId)
        this.writePointer(hold)
        this.writePointer(release)
        this.writePointer(call)
        this.writePointer(callSync)
        return resourceId
    }
    private static createErrorFromStringData(errStr: string[]): Error {
        let code: int32 = errStr.length > 0 ? Number(errStr.splice(0, 1).at(0)).toInt() : 0;
        return new Error(code, errStr.join(';'));
    }
    final holdAndWriteCallbackForPromiseVoid(hold: pointer = 0, release: pointer = 0, call: pointer = 0): [Promise<void>, ResourceId] {
        let resourceId: ResourceId = 0
        const promise = new Promise<void>((resolve: (value: PromiseLike<void>) => void, reject: (err: Error) => void) => {
            const callback = (err?: string[] | undefined) => {
                if (err)
                    reject(SerializerBase.createErrorFromStringData(err))
                else
                    resolve(Promise.resolve())
            }
            resourceId = this.holdAndWriteCallback(callback, hold, release, call)
        })
        return [promise, resourceId]
    }
    final holdAndWriteCallbackForPromise<T>(hold: pointer = 0, release: pointer = 0, call: pointer = 0): [Promise<T>, ResourceId] {
        let resourceId: ResourceId = 0
        const promise = new Promise<T>((resolve: (value: T | PromiseLike<T>) => void, reject: (err: Error) => void) => {
            const callback = (value?: T | undefined, err?: string[] | undefined) => {
                if (err)
                    reject(SerializerBase.createErrorFromStringData(err))
                else
                    resolve(value!)
            }
            resourceId = this.holdAndWriteCallback(callback, hold, release, call)
        })
        return [promise, resourceId]
    }
    final holdAndWriteObject(obj: object, hold: pointer = 0, release: pointer = 0): ResourceId {
        const resourceId = ResourceHolder.instance().registerAndHold(obj)
        this.addHeldResource(resourceId)
        this.writeInt32(resourceId)
        this.writePointer(hold)
        this.writePointer(release)
        return resourceId
    }
    final writeCallbackResource(resource: CallbackResource) {
        this.writeInt32(resource.resourceId)
        this.writePointer(resource.hold)
        this.writePointer(resource.release)
    }
    final writeResource(resource: object) {
        const resourceId = ResourceHolder.instance().registerAndHold(resource)
        this.addHeldResource(resourceId)
        this.writeInt32(resourceId)
    }
    private final releaseResources() {
        if (this.heldResourcesCount == 0) return
        for (let i = 0; i < this.heldResourcesCount; i++) {
            InteropNativeModule._ReleaseCallbackResource(this.heldResources[i])
        }
        this.heldResourcesCount = 0
    }
    final writeCustomObject(kind: string, value: object) {
        let current = SerializerBase.customSerializers
        while (current) {
            if (current!.supports(kind)) {
                current!.serialize(this, value, kind)
                return
            }
            current = current!.next
        }
        this.writeInt8(Tags.UNDEFINED.valueOf())
    }
    final writeTag(tag: int32): void {
        this.writeInt8(tag)
    }
    final writeNumber(value: number | undefined) {
        if (value == undefined) {
            this.writeTag(Tags.UNDEFINED)
            return
        }
        if (Number.isInteger(value)) {
            this.writeTag(Tags.INT32)
            this.writeInt32(value.toInt())
        } else {
            this.writeInt8(Tags.FLOAT32)
            this.writeFloat32(value.toFloat())
        }
    }

    final writeInt8(value: int32) {
        let pos = this._position
        let newPos = pos + 1
        if (newPos > this._last) {
            this.updateCapacity(1)
            pos = this._position
            newPos = pos + 1
        }

        unsafeMemory.writeInt8(pos, value.toByte())
        this._position = newPos
    }

    final writeInt32(value: int32) {
        let pos = this._position
        let newPos = pos + 4
        if (newPos > this._last) {
            this.updateCapacity(4)
            pos = this._position
            newPos = pos + 4
        }
        unsafeMemory.writeInt32(pos, value)
        this._position = newPos
    }
    final writeInt64(value: int64) {
        let pos = this._position
        let newPos = pos + 8
        if (newPos > this._last) {
            this.updateCapacity(8)
            pos = this._position
            newPos = pos + 8
        }
        unsafeMemory.writeInt64(pos, value)
        this._position = newPos
    }
    final writeFloat32(value: float32) {
        let pos = this._position
        let newPos = pos + 4
        if (newPos > this._last) {
            this.updateCapacity(4)
            pos = this._position
            newPos = pos + 4
        }
        unsafeMemory.writeFloat32(pos, value)
        this._position = newPos
    }
    final writeFloat64(value: double) {
        let pos = this._position
        let newPos = pos + 8
        if (newPos > this._last) {
            this.updateCapacity(8)
            pos = this._position
            newPos = pos + 8
        }
        unsafeMemory.writeFloat64(pos, value)
        this._position = newPos
    }
    final writePointer(value: pointer) {
        this.writeInt64(value)
    }
    final writeBoolean(value: boolean | undefined) {
        let pos = this._position
        let newPos = pos + 1
        if (newPos > this._last) {
            this.updateCapacity(1)
            pos = this._position
            newPos = pos + 1
        }
        this._position = newPos

        if (value == undefined)
            unsafeMemory.writeInt8(pos, Tags.UNDEFINED);
        else if (value == true)
            unsafeMemory.writeInt8(pos, VALUE_TRUE.toByte());
        else if (value == false)
            unsafeMemory.writeInt8(pos, VALUE_FALSE.toByte());
    }
    final writeString(value: string) {
        const encodedLength = unsafeMemory.getStringSizeInBytes(value)

        let pos = this._position
        if (pos + encodedLength + 5 > this._last) {
            this.updateCapacity(encodedLength + 5)
            pos = this._position
        }

        if (encodedLength > 0)
            unsafeMemory.writeString(pos + 4, value)
        // NOTE: add \0 for supporting C char* reading from buffer for utf8-strings,
        // need check native part fot utf16 cases and probably change this solution.
        unsafeMemory.writeInt8(pos + encodedLength + 4, 0)
        unsafeMemory.writeInt32(pos, encodedLength + 1)
        this._position = pos + encodedLength + 4 + 1
    }
    final writeBuffer(value: ArrayBuffer) {
        this.holdAndWriteObject(value)
        const ptr = InteropNativeModule._GetNativeBufferPointer(value)
        this.writePointer(ptr)
        this.writeInt64(value.byteLength)
    }
}
