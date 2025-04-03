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
import { float32, int32, int64 } from "@koalaui/common"
import { pointer, KPointer, KSerializerBuffer } from "./InteropTypes"
import { wrapCallback } from "./InteropOps"
import { InteropNativeModule } from "./InteropNativeModule"
import { ResourceHolder, ResourceId } from "../arkts/ResourceManager"
import { MaterializedBase } from "./MaterializedBase"
import { nullptr } from "./Wrapper"
import { NativeBuffer } from "./NativeBuffer"

// imports required interfaces (now generation is disabled)
// import { Resource } from "@arkoala/arkui"
/**
 * Value representing possible JS runtime object type.
 * Must be synced with "enum RuntimeType" in C++.
 */
export enum RuntimeType {
    UNEXPECTED = -1,
    NUMBER = 1,
    STRING = 2,
    OBJECT = 3,
    BOOLEAN = 4,
    UNDEFINED = 5,
    BIGINT = 6,
    FUNCTION = 7,
    SYMBOL = 8,
    MATERIALIZED = 9,
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

export function runtimeType(value: any): int32 {
    let type = typeof value
    if (type == "number") return RuntimeType.NUMBER
    if (type == "string") return RuntimeType.STRING
    if (type == "undefined") return RuntimeType.UNDEFINED
    if (type == "object") return RuntimeType.OBJECT
    if (type == "boolean") return RuntimeType.BOOLEAN
    if (type == "bigint") return RuntimeType.BIGINT
    if (type == "function") return RuntimeType.FUNCTION
    if (type == "symbol") return RuntimeType.SYMBOL

    throw new Error(`bug: ${value} is ${type}`)
}

// Poor man's instanceof, fails on subclasses
export function isInstanceOf(className: string, value: object | undefined): boolean {
    return value?.constructor.name === className
}

export function registerCallback(value: object|undefined): int32 {
    return wrapCallback((args: Uint8Array, length: int32) => {
        // TBD: deserialize the callback arguments and call the callback
        return 42
    })
}

export function toPeerPtr(value: object): KPointer {
    if (value.hasOwnProperty("peer"))
        return unsafeCast<MaterializedBase>(value).getPeer()?.ptr ?? nullptr
    else
        throw new Error("Value is not a MaterializedBase instance")
}

export interface CallbackResource {
    resourceId: int32
    hold: pointer
    release: pointer
}

/* Serialization extension point */
export abstract class CustomSerializer {
    constructor(protected supported: Array<string>) {}
    supports(kind: string): boolean { return this.supported.includes(kind) }
    abstract serialize(serializer: SerializerBase, value: any, kind: string): void
    next: CustomSerializer | undefined = undefined
}

export class SerializerBase {
    private position = 0
    private buffer: ArrayBuffer
    private view: DataView

    private static customSerializers: CustomSerializer | undefined = undefined
    static registerCustomSerializer(serializer: CustomSerializer) {
        if (SerializerBase.customSerializers == undefined) {
            SerializerBase.customSerializers = serializer
        } else {
            let current = SerializerBase.customSerializers
            while (current.next != undefined) { current = current.next }
            current.next = serializer
        }
    }
    constructor() {
        this.buffer = new ArrayBuffer(96)
        this.view = new DataView(this.buffer)
    }
    public release() {
        this.releaseResources()
        this.position = 0
    }
    asBuffer(): KSerializerBuffer {
        return new Uint8Array(this.buffer)
    }
    length(): int32 {
        return this.position
    }
    getByte(offset: int32): int32 {
        return this.view.getUint8(offset) as int32
    }
    toArray(): Uint8Array {
        return new Uint8Array(this.buffer.slice(0, this.currentPosition()))
    }
    currentPosition(): int32 { return this.position }

    private checkCapacity(value: int32) {
        if (value < 1) {
            throw new Error(`${value} is less than 1`)
        }
        let buffSize = this.buffer.byteLength
        if (this.position > buffSize - value) {
            const minSize = this.position + value
            const resizedSize = Math.max(minSize, Math.round(3 * buffSize / 2))
            let resizedBuffer = new ArrayBuffer(resizedSize)
            // TODO: can we grow without new?
            // TODO: check the status of ArrayBuffer.transfer function implementation in STS
            new Uint8Array(resizedBuffer).set(new Uint8Array(this.buffer))
            this.buffer = resizedBuffer
            this.view = new DataView(resizedBuffer)
        }
    }
    private heldResources: ResourceId[] = []
    holdAndWriteCallback(callback: object, hold: KPointer = 0, release: KPointer = 0, call: KPointer = 0, callSync: KPointer = 0): ResourceId {
        const resourceId = ResourceHolder.instance().registerAndHold(callback)
        this.heldResources.push(resourceId)
        this.writeInt32(resourceId)
        this.writePointer(hold)
        this.writePointer(release)
        this.writePointer(call)
        this.writePointer(callSync)
        return resourceId
    }
    holdAndWriteCallbackForPromiseVoid(hold: KPointer = 0, release: KPointer = 0, call: KPointer = 0, callSync = 0): [Promise<void>, ResourceId] {
        let resourceId: ResourceId
        const promise = new Promise<void>((resolve, reject) => {
            const callback = (err: string[]|undefined) => {
                if (err !== undefined)
                    reject(err)
                else
                    resolve()
            }
            resourceId = this.holdAndWriteCallback(callback, hold, release, call, callSync)
        })
        return [promise, resourceId]
    }
    holdAndWriteCallbackForPromise<T>(hold: KPointer = 0, release: KPointer = 0, call: KPointer = 0): [Promise<T>, ResourceId] {
        let resourceId: ResourceId
        const promise = new Promise<T>((resolve, reject) => {
            const callback = (value: T|undefined, err: string[]|undefined) => {
                if (err !== undefined)
                    reject(err)
                else
                    resolve(value!)
            }
            resourceId = this.holdAndWriteCallback(callback, hold, release, call)
        })
        return [promise, resourceId]
    }
    writeCallbackResource(resource: CallbackResource) {
        this.writeInt32(resource.resourceId)
        this.writePointer(resource.hold)
        this.writePointer(resource.release)
    }
    holdAndWriteObject(obj:any, hold: KPointer = 0, release: KPointer = 0): ResourceId {
        const resourceId = ResourceHolder.instance().registerAndHold(obj)
        this.heldResources.push(resourceId)
        this.writeInt32(resourceId)
        this.writePointer(hold)
        this.writePointer(release)
        return resourceId
    }
    private releaseResources() {
        for (const resourceId of this.heldResources)
            InteropNativeModule._ReleaseCallbackResource(resourceId)
        // todo think about effective array clearing/pushing
        this.heldResources = []
    }
    writeCustomObject(kind: string, value: any) {
        let current = SerializerBase.customSerializers
        while (current) {
            if (current.supports(kind)) {
                current.serialize(this, value, kind)
                return
            }
            current = current.next
        }
        console.log(`Unsupported custom serialization for ${kind}, write undefined`)
        this.writeInt8(Tags.UNDEFINED)
    }
    writeNumber(value: number|undefined) {
        this.checkCapacity(5)
        if (value == undefined) {
            this.view.setInt8(this.position, Tags.UNDEFINED)
            this.position++
            return
        }
        if (value == Math.round(value)) {
            this.view.setInt8(this.position, Tags.INT32)
            this.view.setInt32(this.position + 1, value, true)
            this.position += 5
            return
        }
        this.view.setInt8(this.position, Tags.FLOAT32)
        this.view.setFloat32(this.position + 1, value, true)
        this.position += 5
    }
    writeInt8(value: int32) {
        this.checkCapacity(1)
        this.view.setInt8(this.position, value)
        this.position += 1
    }
    writeInt32(value: int32) {
        this.checkCapacity(4)
        this.view.setInt32(this.position, value, true)
        this.position += 4
    }
    writeInt64(value: int64) {
        this.checkCapacity(8)
        this.view.setBigInt64(this.position, BigInt(value), true)
        this.position += 8
    }
    writePointer(value: pointer) {
        this.checkCapacity(8)
        this.view.setBigInt64(this.position, BigInt(value ?? 0), true)
        this.position += 8
    }
    writeFloat32(value: float32) {
        this.checkCapacity(4)
        this.view.setFloat32(this.position, value, true)
        this.position += 4
    }
    writeBoolean(value: boolean|undefined) {
        this.checkCapacity(1)
        this.view.setInt8(this.position, value == undefined ? RuntimeType.UNDEFINED : +value)
        this.position++
    }
    writeFunction(value: object | undefined) {
        this.writeInt32(registerCallback(value))
    }
    writeString(value: string) {
        this.checkCapacity(4 + value.length * 4) // length, data
        let encodedLength =
            InteropNativeModule._ManagedStringWrite(value, new Uint8Array(this.view.buffer, 0), this.position + 4)
        this.view.setInt32(this.position, encodedLength, true)
        this.position += encodedLength + 4
    }
    writeBuffer(buffer: NativeBuffer) {
        this.writeCallbackResource({
            resourceId: buffer.resourceId,
            hold: buffer.hold,
            release: buffer.release,
        })
        this.writePointer(buffer.data)
        this.writeInt64(buffer.length)
    }
}

class DateSerializer extends CustomSerializer {
    constructor() {
        super(["Date"])
    }

    serialize(serializer: SerializerBase, value: object, kind: string): void {
        serializer.writeString((value as Date).toISOString())
    }
}
SerializerBase.registerCustomSerializer(new DateSerializer())

export function unsafeCast<T>(value: unknown) {
    return value as unknown as T
}
