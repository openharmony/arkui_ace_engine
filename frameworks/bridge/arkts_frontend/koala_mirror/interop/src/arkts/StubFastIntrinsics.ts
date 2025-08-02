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

import { int8, int32, int64, uint8, int32BitsFromFloat, float32FromBits } from "@koalaui/common"
import { KSerializerBuffer } from "./InteropTypes"
import { InteropNativeModule } from "./InteropNativeModule"

export class StubFastIntrinsics {

    public static writeBoolean(address: long, value: boolean|undefined): void {
        if (value == undefined) {
            StubFastIntrinsics.writeu8(address, 0, 1, 5) // RuntimeType.UNDEFINED is 5
        } else {
            StubFastIntrinsics.writeu8(address, 0, 1, (value ? 1 : 0) as int8)
        }
    }

    public static writeInt8(address: long, value: byte): void {
        StubFastIntrinsics.writeu8(address,  0, 1 , value as int8)
    }

    public static writeInt32(address: long, value: int): void {
        StubFastIntrinsics.writeu32(address, 0, 4, value)
    }

    public static writeInt64(address: long, value: long): void {
        StubFastIntrinsics.writeu64(address, 0, 8, value)
    }

    public static writeFloat32(address: long, value: float): void {
        let bits = int32BitsFromFloat(value)
        StubFastIntrinsics.writeu32(address, 0, 4, bits)
    }

    public static getByteCapacityOfString(value: string): int32 {
        return value.length as int32 * 4 + 1 + 4
    }

    public static writeString(address: long, value: string): int {
        return StubFastIntrinsics.writeString(address, 0, value);
    }

    public static readBoolean(address: long): boolean|undefined {
        const value = StubFastIntrinsics.readu8(address, 0, 1)
        return value === 1
    }

    public static readInt8(address: long): byte {
        return StubFastIntrinsics.readu8(address, 0, 1) as byte;
    }

    public static readInt32(address: long): int {
        return StubFastIntrinsics.readu32(address, 0, 4)
    }

    public static readInt64(address: long): long {
        return StubFastIntrinsics.readu64(address, 0, 8)
    }

    public static readFloat32(address: long): float {
        let result = StubFastIntrinsics.readu32(address, 0, 4)
        return float32FromBits(result)
    }

    public static readString(address: long, byteSize: int): String {
        return StubFastIntrinsics.readString(address, 0, byteSize)
    }

    // TODO: get rid of length.
    private static writeu8(buffer: KSerializerBuffer, offset: int32, length: int32, value: int32) {
        InteropNativeModule._WriteByte(buffer, offset as int64, length as int64, value as uint8)
    }

    private static writeu32(buffer: KSerializerBuffer, offset: int32, length: int32, value: int32) {
        InteropNativeModule._WriteByte(buffer, offset,     length as int64, (value & 0xff) as uint8)
        InteropNativeModule._WriteByte(buffer, offset + 1, length as int64, ((value >> 8) & 0xff) as uint8)
        InteropNativeModule._WriteByte(buffer, offset + 2, length as int64, ((value >> 16) & 0xff) as uint8)
        InteropNativeModule._WriteByte(buffer, offset + 3, length as int64, ((value >> 24) & 0xff) as uint8)
    }

    private static writeu64(buffer: KSerializerBuffer, offset: int32, length: int32, value: int64) {
        StubFastIntrinsics.writeu8(buffer,  offset + 0, length, ((value      ) & 0xff) as int8)
        StubFastIntrinsics.writeu8(buffer,  offset + 1, length, ((value >>  8) & 0xff) as int8)
        StubFastIntrinsics.writeu8(buffer,  offset + 2, length, ((value >> 16) & 0xff) as int8)
        StubFastIntrinsics.writeu8(buffer,  offset + 3, length, ((value >> 24) & 0xff) as int8)
        StubFastIntrinsics.writeu8(buffer,  offset + 4, length, ((value >> 32) & 0xff) as int8)
        StubFastIntrinsics.writeu8(buffer,  offset + 5, length, ((value >> 40) & 0xff) as int8)
        StubFastIntrinsics.writeu8(buffer,  offset + 6, length, ((value >> 48) & 0xff) as int8)
        StubFastIntrinsics.writeu8(buffer,  offset + 7, length, ((value >> 56) & 0xff) as int8)
     }

     private static writeString(buffer: KSerializerBuffer, offset: int32, value: string) {
        let encodedLength = InteropNativeModule._ManagedStringWrite(value, buffer, offset)
        return encodedLength;
    }

    // TODO: get rid of length.
    private static readu8(buffer: KSerializerBuffer, offset: int32, length: int32): int32 {
        let byteValue: byte = InteropNativeModule._ReadByte(buffer, offset as int64, length as int64) as byte 
        byteValue &= 0xff
        return byteValue
    }

    private static readu32(buffer: KSerializerBuffer, offset: int32, length: int32): int32 {
        let result: int32 = 0;
        for (let i = 0; i < 4; i++) {
            let byteValue = StubFastIntrinsics.readu8(buffer, offset + i, length) as int32
            byteValue &= 0xff
            result = (result | byteValue << (8 * i)) as int32
        }

        return result;
    }
 
    private static readu64(buffer: KSerializerBuffer, offset: int32, length: int32): int64 {
        let result: int64 = 0;
        for (let i = 0; i < 8; i++) {
            let byteValue = StubFastIntrinsics.readu8(buffer, offset + i, length) as int64;
            byteValue &= 0xff
            result = (result | byteValue << (8 * i)) as int64;
        }
        return result;
    }   
    
    private static readString(buffer: KSerializerBuffer, offset: int32, length: int32):string {
        return InteropNativeModule._Utf8ToString(buffer, offset, length)
    }
}