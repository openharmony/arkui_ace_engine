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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { Resource } from "global.resource"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export class Resource_serializer {
    public static write(buffer: SerializerBase, value: Resource): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForBundleName  = value.bundleName
        valueSerializer.writeString(valueHolderForBundleName)
        const valueHolderForModuleName  = value.moduleName
        valueSerializer.writeString(valueHolderForModuleName)
        const valueHolderForId  = value.id
        valueSerializer.writeInt64(valueHolderForId)
        const valueHolderForParams  = value.params
        if (valueHolderForParams !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParamsTmpValue  = valueHolderForParams!
            valueSerializer.writeInt32((valueHolderForParamsTmpValue.length).toInt())
            for (let valueHolderForParamsTmpValueCounterI = 0; valueHolderForParamsTmpValueCounterI < valueHolderForParamsTmpValue.length; valueHolderForParamsTmpValueCounterI++) {
                const valueHolderForParamsTmpValueTmpElement : string | int32 | int64 | double | Resource = valueHolderForParamsTmpValue[valueHolderForParamsTmpValueCounterI]
                if (valueHolderForParamsTmpValueTmpElement instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForParamsTmpValueTmpElementForIdx0  = valueHolderForParamsTmpValueTmpElement as string
                    valueSerializer.writeString(valueHolderForParamsTmpValueTmpElementForIdx0)
                } else if (valueHolderForParamsTmpValueTmpElement instanceof int32) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForParamsTmpValueTmpElementForIdx1  = valueHolderForParamsTmpValueTmpElement as int32
                    valueSerializer.writeInt32(valueHolderForParamsTmpValueTmpElementForIdx1)
                } else if (valueHolderForParamsTmpValueTmpElement instanceof int64) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForParamsTmpValueTmpElementForIdx2  = valueHolderForParamsTmpValueTmpElement as int64
                    valueSerializer.writeInt64(valueHolderForParamsTmpValueTmpElementForIdx2)
                } else if (valueHolderForParamsTmpValueTmpElement instanceof double) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForParamsTmpValueTmpElementForIdx3  = valueHolderForParamsTmpValueTmpElement as double
                    valueSerializer.writeFloat64(valueHolderForParamsTmpValueTmpElementForIdx3)
                } else if (valueHolderForParamsTmpValueTmpElement instanceof Resource) {
                    valueSerializer.writeInt8((4).toByte())
                    const valueHolderForParamsTmpValueTmpElementForIdx4  = valueHolderForParamsTmpValueTmpElement as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForParamsTmpValueTmpElementForIdx4)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForType  = value.type
        if (valueHolderForType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypeTmpValue  = valueHolderForType!
            valueSerializer.writeInt32(valueHolderForTypeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): Resource {
        let valueDeserializer : DeserializerBase = buffer
        const bundleNameTmpResult : string = (valueDeserializer.readString() as string)
        const moduleNameTmpResult : string = (valueDeserializer.readString() as string)
        const idTmpResult : int64 = valueDeserializer.readInt64()
        const paramsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let paramsTmpBuf : Array<string | int32 | int64 | double | Resource> | undefined = undefined
        if ((paramsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const paramsTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let paramsTmpBuf_ : Array<string | int32 | int64 | double | Resource> = new Array<string | int32 | int64 | double | Resource>(paramsTmpBuf_Length)
            for (let paramsTmpBuf_BufCounterI = 0; paramsTmpBuf_BufCounterI < paramsTmpBuf_Length; paramsTmpBuf_BufCounterI++) {
                const paramsTmpBuf_TempBufUnionSelector : int32 = valueDeserializer.readInt8()
                let paramsTmpBuf_TempBuf : string | int32 | int64 | double | Resource | undefined
                if (paramsTmpBuf_TempBufUnionSelector == (0).toChar()) {
                    paramsTmpBuf_TempBuf = (valueDeserializer.readString() as string)
                } else if (paramsTmpBuf_TempBufUnionSelector == (1).toChar()) {
                    paramsTmpBuf_TempBuf = valueDeserializer.readInt32()
                } else if (paramsTmpBuf_TempBufUnionSelector == (2).toChar()) {
                    paramsTmpBuf_TempBuf = valueDeserializer.readInt64()
                } else if (paramsTmpBuf_TempBufUnionSelector == (3).toChar()) {
                    paramsTmpBuf_TempBuf = valueDeserializer.readFloat64()
                } else if (paramsTmpBuf_TempBufUnionSelector == (4).toChar()) {
                    paramsTmpBuf_TempBuf = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for paramsTmpBuf_TempBuf has to be chosen through deserialisation.")
                }
                paramsTmpBuf_[paramsTmpBuf_BufCounterI] = (paramsTmpBuf_TempBuf as string | int32 | int64 | double | Resource)
            }
            paramsTmpBuf = paramsTmpBuf_
        }
        const paramsTmpResult : Array<string | int32 | int64 | double | Resource> | undefined = paramsTmpBuf
        const typeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let typeTmpBuf : int32 | undefined = undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = valueDeserializer.readInt32()
        }
        const typeTmpResult : int32 | undefined = typeTmpBuf
        let value : Resource = ({bundleName: bundleNameTmpResult, moduleName: moduleNameTmpResult, id: idTmpResult, params: paramsTmpResult, type: typeTmpResult} as Resource)
        return value
    }
}
