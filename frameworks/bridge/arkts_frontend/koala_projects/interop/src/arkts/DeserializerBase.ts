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

import { float32, int32, int64, float32FromBits, uint8 } from "@koalaui/common"
import { pointer, KUint8ArrayPtr, KSerializerBuffer } from "./InteropTypes"
import { NativeBuffer } from "./NativeBuffer"
import { InteropNativeModule } from "./InteropNativeModule"
import { Tags, CallbackResource } from "./SerializerBase";
import { ResourceHolder } from "./ResourceManager"

export class DeserializerBase {
    private position = 0
    private readonly _buffer: KSerializerBuffer
    private readonly _length: int32
    private static customDeserializers: CustomDeserializer | undefined = new DateDeserializer()

    static registerCustomDeserializer(deserializer: CustomDeserializer) {
        let current = DeserializerBase.customDeserializers
        if (current == undefined) {
            DeserializerBase.customDeserializers = deserializer
        } else {
            while (current!.next != undefined) {
                current = current!.next
            }
            current!.next = deserializer
        }
    }

    constructor(buffer: KUint8ArrayPtr|KSerializerBuffer, length: int32) {
        if (buffer instanceof KUint8ArrayPtr) {
            this._buffer = InteropNativeModule._Malloc(length)
            for (let i = 0; i < length; i++) {
                DeserializerBase.writeu8(this._buffer, i, length, buffer[i])
            }
        } else {
            this._buffer = buffer
        }
        this._length = length
    }

    // TODO: get rid of length.
    private static writeu8(buffer: KSerializerBuffer, offset: int32, length: int32, value: int32): void {
        InteropNativeModule._WriteByte(buffer, offset as int64, length as int64, value as uint8)
    }
    // TODO: get rid of length.
    private static readu8(buffer: KSerializerBuffer, offset: int32, length: int32): int32 {
        return (InteropNativeModule._ReadByte(buffer, offset as int64, length as int64) as byte) & 0xff
    }

    final asBuffer(): KSerializerBuffer {
        return this._buffer
    }

    final currentPosition(): int32 {
        return this.position
    }

    final resetCurrentPosition(): void {
        this.position = 0
    }

    private checkCapacity(value: int32) {
        if (value > this._length) {
            throw new Error(`${value} is less than remaining buffer length`)
        }
    }

    final readInt8(): int32 {
        this.checkCapacity(1)
        const value = DeserializerBase.readu8(this._buffer, this.position, this._length)
        this.position += 1
        return value
    }

    final readInt32(): int32 {
        this.checkCapacity(4)
        let res: int32 = 0;
        for (let i = 0; i < 4; i++) {
            let byteVal = DeserializerBase.readu8(this._buffer, this.position + i, this._length) as int32
            byteVal &= 0xff
            res = (res | byteVal << (8 * i)) as int32
        }
        this.position += 4
        return res
    }

    final readPointer(): pointer {
        this.checkCapacity(8)
        let res: int64 = 0;
        for (let i = 0; i < 8; i++) {
            let byteVal = DeserializerBase.readu8(this._buffer, this.position + i, this._length) as int64;
            byteVal &= 0xff
            res = (res | byteVal << (8 * i)) as int64;
        }
        this.position += 8
        return res
    }

    final readInt64(): int64 {
        this.checkCapacity(8)
        let res: int64 = 0;
        for (let i = 0; i < 8; i++) {
            let byteVal = DeserializerBase.readu8(this._buffer, this.position + i, this._length) as int64;
            byteVal &= 0xff
            res = (res | byteVal << (8 * i)) as int64;
        }
        this.position += 8
        return res
    }

    final readFloat32(): float32 {
        this.checkCapacity(4)
        let res: int32 = 0;
        for (let i = 0; i < 4; i++) {
            let byteVal = DeserializerBase.readu8(this._buffer, this.position + i, this._length) as int32;
            byteVal &= 0xff
            res = (res | byteVal << (8 * i)) as int32;
        }
        this.position += 4
        return float32FromBits(res)
    }

    final readBoolean(): boolean {
        this.checkCapacity(1)
        const value = DeserializerBase.readu8(this._buffer, this.position, this._length)
        this.position += 1
        return value == 1
    }

    readFunction(): int32 {
        // TODO: not exactly correct.
        const id = this.readInt32()
        return id
    }

    // readMaterialized(): object {
    //     const ptr = this.readPointer()
    //     return { ptr: ptr }
    // }

    final readCallbackResource(): CallbackResource {
        return ({
            resourceId: this.readInt32(),
            hold: this.readPointer(),
            release: this.readPointer(),
        } as CallbackResource)
    }

    final readString(): string {
        const length = this.readInt32()
        this.checkCapacity(length)
        // read without null-terminated byte
        const value = InteropNativeModule._Utf8ToString(this._buffer, this.position, length)
        this.position += length
        return value
    }

    final readCustomObject(kind: string): object {
        let current = DeserializerBase.customDeserializers
        while (current) {
            if (current!.supports(kind)) {
                return current!.deserialize(this, kind)
            }
            current = current!.next
        }
        // consume tag
        const tag = this.readInt8()
        throw Error(`${kind} is not supported`)
    }

    final readNumber(): number | undefined {
        const tag = this.readInt8()
        if (tag == Tags.UNDEFINED) {
            return undefined
        } else if (tag == Tags.INT32) {
            return this.readInt32()
        } else if (tag == Tags.FLOAT32) {
            return this.readFloat32()
        } else {
            throw new Error(`Unknown number tag: ${tag}`)
        }
    }

    readObject():object {
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

    final readBuffer(): NativeBuffer {
        /* not implemented */
        const resource = this.readCallbackResource()
        const data = this.readPointer()
        const length = this.readInt64()
        return NativeBuffer.wrap(data, length, resource.resourceId, resource.hold, resource.release)
    }
}

export abstract class CustomDeserializer {
    protected supported: string
    protected constructor(supported_: string) {
        this.supported = supported_
    }

    supports(kind: string): boolean {
        return this.supported.includes(kind)
    }

    abstract deserialize(serializer: DeserializerBase, kind: string): object

    next: CustomDeserializer | undefined = undefined
}

class DateDeserializer extends CustomDeserializer {
    constructor() {
        super("Date")
    }

    deserialize(serializer: DeserializerBase, kind: string): Date {
        return new Date(serializer.readString())
    }
}