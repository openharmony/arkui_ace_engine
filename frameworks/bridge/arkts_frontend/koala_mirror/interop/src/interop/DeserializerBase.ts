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
import { CustomTextDecoder, float32, int32, int64 } from "@koalaui/common"
import { Tags, CallbackResource } from "./SerializerBase";
import { pointer, KUint8ArrayPtr, KSerializerBuffer } from "./InteropTypes"
import { NativeBuffer } from "./NativeBuffer";
import { ResourceHolder } from "../arkts/ResourceManager";
import { InteropNativeModule } from "./InteropNativeModule";

export class DeserializerBase {
    private position = 0
    private readonly buffer: ArrayBuffer
    private readonly length: int32
    private view: DataView
    private static textDecoder = new CustomTextDecoder()
    private static customDeserializers: CustomDeserializer | undefined = undefined

    static registerCustomDeserializer(deserializer: CustomDeserializer) {
        let current = DeserializerBase.customDeserializers
        if (current == undefined) {
            DeserializerBase.customDeserializers = deserializer
        } else {
            while (current.next != undefined) {
                current = current.next
            }
            current.next = deserializer
        }
    }

    constructor(buffer: ArrayBuffer|KSerializerBuffer|KUint8ArrayPtr, length: int32) {
        if (typeof buffer != 'object')
            throw new Error('Must be used only with ArrayBuffer')
        if (buffer && ("buffer" in buffer)) {
            buffer = buffer.buffer as ArrayBuffer
        }
        this.buffer = buffer as ArrayBuffer
        this.length = length
        this.view = new DataView(this.buffer)
    }

    static get<T extends DeserializerBase>(
        factory: (args: Uint8Array, length: int32) => T,
        args: Uint8Array, length: int32): T {

        // Improve: Use cache
        return factory(args, length);
    }

    asBuffer(position?: int32, length?: int32): KSerializerBuffer {
        return new Uint8Array(this.buffer, position, length)
    }

    asArray(position?: int32, length?: int32): Uint8Array {
        return new Uint8Array(this.buffer, position, length)
    }

    currentPosition(): int32 {
        return this.position
    }

    resetCurrentPosition(): void {
        this.position = 0
    }

    private checkCapacity(value: int32) {
        if (value > this.length) {
            throw new Error(`${value} is less than remaining buffer length`)
        }
    }

    readInt8(): int32 {
        this.checkCapacity(1)
        const value = this.view.getInt8(this.position)
        this.position += 1
        return value
    }

    readInt32(): int32 {
        this.checkCapacity(4)
        const value = this.view.getInt32(this.position, true)
        this.position += 4
        return value
    }

    readInt64(): int64 {
        this.checkCapacity(8)
        const value = this.view.getBigInt64(this.position, true)
        this.position += 8
        return Number(value)
    }

    readPointer(): pointer {
        this.checkCapacity(8)
        const value = this.view.getBigInt64(this.position, true)
        this.position += 8
        return value
    }

    readFloat32(): float32 {
        this.checkCapacity(4)
        const value = this.view.getFloat32(this.position, true)
        this.position += 4
        return value
    }

    readBoolean(): boolean {
        this.checkCapacity(1)
        const value = this.view.getInt8(this.position)
        this.position += 1
        return value == 1
    }

    readFunction(): any {
        // Improve: not exactly correct.
        const id = this.readInt32()
        return id
    }

    readMaterialized(): object {
        const ptr = this.readPointer()
        return { ptr: ptr }
    }

    readString(): string {
        const length = this.readInt32()
        this.checkCapacity(length)
        // read without null-terminated byte
        const value = DeserializerBase.textDecoder.decode(this.asArray(this.position, length - 1));
        this.position += length
        return value
    }

    readCustomObject(kind: string): any {
        let current = DeserializerBase.customDeserializers
        while (current) {
            if (current.supports(kind)) {
                return current.deserialize(this, kind)
            }
            current = current.next
        }
        // consume tag
        const tag = this.readInt8()
        return undefined
    }

    readNumber(): int32 | undefined {
        const tag = this.readInt8()
        switch (tag) {
            case Tags.UNDEFINED:
                return undefined;
            case Tags.INT32:
                return this.readInt32()
            case Tags.FLOAT32:
                return this.readFloat32()
            default:
                throw new Error(`Unknown number tag: ${tag}`)
                break
        }
    }

    readCallbackResource(): CallbackResource {
        return {
            resourceId: this.readInt32(),
            hold: this.readPointer(),
            release: this.readPointer(),
        }
    }
    readObject():any {
        const resource = this.readCallbackResource()
        return ResourceHolder.instance().get(resource.resourceId)
    }

    static lengthUnitFromInt(unit: int32): string {
        let suffix: string
        switch (unit) {
            case 0:
                suffix = "px"
                break
            case 1:
                suffix = "vp"
                break
            case 3:
                suffix = "%"
                break
            case 4:
                suffix = "lpx"
                break
            default:
                suffix = "<unknown>"
        }
        return suffix
    }
    readBuffer(): NativeBuffer {
        const resource = this.readCallbackResource()
        const data = this.readPointer()
        const length = this.readInt64()
        InteropNativeModule._CallCallbackResourceHolder(resource.hold, resource.resourceId)
        return new NativeBuffer(data, length, resource.release)
    }
}

export abstract class CustomDeserializer {
    protected constructor(protected supported: Array<string>) {
    }

    supports(kind: string): boolean {
        return this.supported.includes(kind)
    }

    abstract deserialize(serializer: DeserializerBase, kind: string): any

    next: CustomDeserializer | undefined = undefined
}

class DateDeserializer extends CustomDeserializer {
    constructor() {
        super(["Date"]);
    }

    deserialize(serializer: DeserializerBase, kind: string): any {
        return new Date(serializer.readString())
    }
}
DeserializerBase.registerCustomDeserializer(new DateDeserializer())
