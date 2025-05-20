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
import { float32, float64, int8, int32, int64, uint8, int32BitsFromFloat } from "@koalaui/common"
import { pointer, nullptr, KSerializerBuffer } from "./InteropTypes"
import { ResourceId, ResourceHolder, Disposable } from "./ResourceManager"
import { NativeBuffer } from "./NativeBuffer"
import { InteropNativeModule } from "./InteropNativeModule"
import { MaterializedBase } from "./MaterializedBase"
import { StubFastIntrinsics } from "./StubFastIntrinsics"

/**
 * Value representing possible JS runtime object type.
 * Must be synced with "enum RuntimeType" in C++.
 */
export class RuntimeType {
    static UNEXPECTED = -1
    static NUMBER = 1
    static STRING = 2
    static OBJECT = 3
    static BOOLEAN = 4
    static UNDEFINED = 5
    static BIGINT = 6
    static FUNCTION = 7
    static SYMBOL = 8
    static MATERIALIZED = 9
}

/**
 * Value representing object type in serialized data.
 * Must be synced with "enum Tags" in C++.
 */
export class Tags {
    static UNDEFINED = 101
    static INT32 = 102
    static FLOAT32 = 103
    static STRING = 104
    static LENGTH = 105
    static RESOURCE = 106
    static OBJECT = 107
}

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

    if (value instanceof Object)
        return RuntimeType.OBJECT

    throw new Error(`bug: ${value} is ${typeof value}`)
}

export function registerCallback(value: object): int32 {
    // TODO: fix me!
    return 42
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
        super(new Array<string>("Date" as string))
    }

    serialize(serializer: SerializerBase, value: object, kind: string): void {
        serializer.writeString((value as Date).toISOString())
    }
}
SerializerBase.registerCustomSerializer(new DateSerializer())

export class SerializerBase implements Disposable {
    private position: int32 = 0
    private _buffer: KSerializerBuffer
    private _length: int32

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
        this._buffer = InteropNativeModule._Malloc(length as int64)
        this._length = length
    }
    public release() {
        this.releaseResources()
        this.position = 0
    }
    public dispose() {
        InteropNativeModule._Free(this._buffer)
        this._buffer = nullptr
    }

    final asBuffer(): KSerializerBuffer {
        return this._buffer
    }
    final length(): int32 {
        return this.position
    }
    final currentPosition(): int32 {
        return this.position
    }

    final getByte(offset: int32): byte {
        return StubFastIntrinsics.readInt8(this._buffer + offset)
    }
    final toArray(): byte[] {
        let result = new byte[this.currentPosition()]
        for (let i = 0; i < this.currentPosition(); i++) {
            result[i] = this.getByte(i) as byte
        }
        return result
    }
    private checkCapacity(value: int32) {
        if (value < 1) {
            throw new Error(`${value} is less than 1`)
        }
        let buffSize = this._length
        if (this.position > buffSize - value) {
            const minSize = this.position + value
            const resizedSize = Math.max(minSize, Math.round(3 * buffSize / 2)) as int32
            let resizedBuffer = InteropNativeModule._Malloc(resizedSize)
            let oldBuffer = this._buffer
            for (let i = 0; i < this.position; i++) {
                let val = StubFastIntrinsics.readInt8(oldBuffer + i);
                StubFastIntrinsics.writeInt8(resizedBuffer + i, val)
            }
            this._buffer = resizedBuffer
            this._length = resizedSize
            InteropNativeModule._Free(oldBuffer)
        }
    }
    private heldResources: Array<ResourceId> = new Array<ResourceId>()
    private heldResourcesCount: int32 = 0
    private addHeldResource(resourceId: ResourceId) {
        if (this.heldResourcesCount == this.heldResources.length)
            this.heldResources.push(resourceId)
        else
            this.heldResources[this.heldResourcesCount] = resourceId
        this.heldResourcesCount++
    }
    holdAndWriteCallback(callback: object, hold: pointer = 0, release: pointer = 0, call: pointer = 0, callSync: pointer = 0): ResourceId {
        const resourceId = ResourceHolder.instance().registerAndHold(callback)
        this.addHeldResource(resourceId)
        this.writeInt32(resourceId)
        this.writePointer(hold)
        this.writePointer(release)
        this.writePointer(call)
        this.writePointer(callSync)
        return resourceId
    }
    holdAndWriteCallbackForPromiseVoid(hold: pointer = 0, release: pointer = 0, call: pointer = 0): [Promise<void>, ResourceId] {
        let resourceId: ResourceId = 0
        const promise = new Promise<void>((resolve: (value: PromiseLike<void>) => void, reject: (err: Error) => void) => {
            const callback = (err: Error|undefined) => {
                if (err !== undefined)
                    reject(err!)
                else
                    resolve(Promise.resolve())
            }
            resourceId = this.holdAndWriteCallback(callback, hold, release, call)
        })
        return [promise, resourceId]
    }
    holdAndWriteCallbackForPromise<T>(hold: pointer = 0, release: pointer = 0, call: pointer = 0): [Promise<T>, ResourceId] {
        let resourceId: ResourceId = 0
        const promise = new Promise<T>((resolve: (value: T|PromiseLike<T>) => void, reject: (err: Error) => void) => {
            const callback = (value?: T|undefined, err?: Error|undefined) => {
                if (err !== undefined)
                    reject(err!)
                else
                    resolve(value!)
            }
            resourceId = this.holdAndWriteCallback(callback, hold, release, call)
        })
        return [promise, resourceId]
    }
    holdAndWriteObject(obj:object, hold: pointer = 0, release: pointer = 0): ResourceId {
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
    private releaseResources() {
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
        // console.log(`Unsupported custom serialization for ${kind}, write undefined`)
        this.writeInt8(Tags.UNDEFINED as int32)
    }
    writeFunction(value: Object) {
        this.writeInt32(registerCallback(value))
    }
    final writeTag(tag: int32): void {
        StubFastIntrinsics.writeInt8(this._buffer + this.position, tag as byte)
        this.position++
    }
    final writeNumber(value: number|undefined) {
        this.checkCapacity(5)
        if (value == undefined) {
            this.writeTag(Tags.UNDEFINED)
            this.position++
            return
        }
        if ((value as float64) == Math.round(value)) {
            this.writeTag(Tags.INT32)
            this.writeInt32(value as int32)
            return
        } else {
            this.writeTag(Tags.FLOAT32)
            this.writeFloat32(value as float32)
        }
    }
    final writeInt8(value: int32) {
        this.checkCapacity(1)
        StubFastIntrinsics.writeInt8(this._buffer + this.position, value as byte)
        this.position += 1
    }

    final writeInt32(value: int32) {
        this.checkCapacity(4)
        StubFastIntrinsics.writeInt32(this._buffer + this.position, value)
        this.position += 4
    }
    final writeInt64(value: int64) {
        this.checkCapacity(8)
        StubFastIntrinsics.writeInt64(this._buffer + this.position, value)
        this.position += 8
    }
    final writeFloat32(value: float32) {
        this.checkCapacity(4)
        StubFastIntrinsics.writeFloat32(this._buffer + this.position, value)
        this.position += 4
    }
    final writePointer(value: pointer) {
        this.writeInt64(value)
    }
    final writeBoolean(value: boolean|undefined) {
        this.checkCapacity(1)
        StubFastIntrinsics.writeBoolean(this._buffer + this.position, value);
        this.position++
    }
    final writeString(value: string) {
        let encodedCapacity = StubFastIntrinsics.getByteCapacityOfString(value);
        this.checkCapacity(encodedCapacity) // length, data
        let encodedLength = StubFastIntrinsics.writeString(this._buffer + this.position + 4, value)
        this.writeInt32(encodedLength)
        this.position += encodedLength
    }
    //TODO: Needs to be implemented
    final writeBuffer(value: NativeBuffer) {
        this.writeCallbackResource({
            resourceId: value.resourceId,
            hold: value.hold,
            release: value.release
        })
        this.writePointer(value.data)
        this.writeInt64(value.length as int64)
    }
}

