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
import { pointer, KUint8ArrayPtr, KSerializerBuffer, nullptr } from "./InteropTypes"
import { NativeBuffer } from "./NativeBuffer"
import { InteropNativeModule } from "./InteropNativeModule"
import { Tags, CallbackResource } from "./SerializerBase";
import { ResourceHolder, Disposable } from "./ResourceManager"

export class DeserializerBase implements Disposable {
    private position : int64 = 0
    private _buffer: KSerializerBuffer
    private readonly _isOwnBuffer: boolean;
    private readonly _length: int32
    private readonly _end: int64
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
            const newBuffer = InteropNativeModule._Malloc(length)
            this._isOwnBuffer = true
            for (let i = 0; i < length; i++) {
                unsafeMemory.writeInt8(newBuffer + i, buffer[i] as byte)
            }
            this._buffer = newBuffer
        } else {
            this._buffer = buffer
        }

        const newBuffer =  this._buffer;
        this._length = length
        this.position = newBuffer
        this._end = newBuffer + length;
    }

    public final dispose() {
        if (this._isOwnBuffer) {
            InteropNativeModule._Free(this._buffer)
            this._buffer = 0
            this.position = 0
        }
    }

    final asBuffer(): KSerializerBuffer {
        return this._buffer
    }

    final resetCurrentPosition(): void {
        this.position = this._buffer
    }

    final readInt8(): int32 {
        const pos = this.position
        const newPos = pos + 1

        if (newPos > this._end) {
            throw new Error(`value size(1) is less than remaining buffer length`)
        }

        this.position = newPos
        return unsafeMemory.readInt8(pos)
    }

    final readInt32(): int32 {
        const pos = this.position
        const newPos = pos + 4

        if (newPos > this._end) {
            throw new Error(`value size(4) is less than remaining buffer length`)
        }

        this.position = newPos
        return unsafeMemory.readInt32(pos)
    }

    final readPointer(): pointer {
        const pos = this.position
        const newPos = pos + 8

        if (newPos > this._end) {
            throw new Error(`value size(8) is less than remaining buffer length`)
        }

        this.position = newPos
        return unsafeMemory.readInt64(pos)
    }

    final readInt64(): int64 {
        const pos = this.position
        const newPos = pos + 8

        if (newPos > this._end) {
            throw new Error(`value size(8) is less than remaining buffer length`)
        }

        this.position = newPos
        return unsafeMemory.readInt64(pos)
    }

    final readFloat32(): float32 {
        const pos = this.position
        const newPos = pos + 4

        if (newPos > this._end) {
            throw new Error(`value size(4) is less than remaining buffer length`)
        }


        this.position = newPos
        return unsafeMemory.readFloat32(pos)
    }

    final readFloat64(): double {
        const pos = this.position
        const newPos = pos + 8

        if (newPos > this._end) {
            throw new Error(`value size(8) is less than remaining buffer length`)
        }


        this.position = newPos
        return unsafeMemory.readFloat64(pos)
    }

    final readBoolean(): boolean {
        const pos = this.position
        const newPos = pos + 1

        if (newPos > this._end) {
            throw new Error(`value size(1) is less than remaining buffer length`)
        }


        this.position = newPos
        const value = unsafeMemory.readInt8(pos);
        if (value == 5)
            return false;

        return value == 1
    }

    final readFunction(): int32 {
        // Improve: not exactly correct.
        return this.readInt32()
    }

    final readCallbackResource(): CallbackResource {
        return ({
            resourceId: this.readInt32(),
            hold: this.readPointer(),
            release: this.readPointer(),
        } as CallbackResource)
    }

    final readString(): string {
        const encodedLength = this.readInt32();
        const pos = this.position
        const newPos = pos + encodedLength

        if (newPos > this._end) {
            throw new Error(`value size(${encodedLength}) is less than remaining buffer length`)
        }

        this.position = newPos
        // NOTE: skip null-terminated byte
        return unsafeMemory.readString(pos, encodedLength - 1)
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
        const pos = this.position
        const tag = this.readInt8() as int
        switch (tag) {
            case Tags.UNDEFINED as int:
                return undefined;
            case Tags.INT32  as int:
                return this.readInt32()
            case Tags.FLOAT32  as int:
                return this.readFloat32()
            default:
                throw new Error(`Unknown number tag: ${tag}`)
        }
    }

    final readObject():object {
        const resource = this.readCallbackResource()
        return ResourceHolder.instance().get(resource.resourceId)
    }

    final readBuffer(): NativeBuffer {
        const resource = this.readCallbackResource()
        const data = this.readPointer()
        const length = this.readInt64()
        InteropNativeModule._CallCallbackResourceHolder(resource.hold, resource.resourceId)
        return new NativeBuffer(data, length, resource.release)
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