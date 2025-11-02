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

import { extractors } from "#handwritten"
import { UIContext, TargetInfo } from "@ohos.arkui.UIContext"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export class UIContext_serializer {
    public static write(buffer: SerializerBase, value: UIContext): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toUIContextPtr(value))
    }
    public static read(buffer: DeserializerBase): UIContext {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromUIContextPtr(ptr)
    }
}
export class TargetInfo_serializer {
    public static write(buffer: SerializerBase, value: TargetInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        if (valueHolderForId instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForIdForIdx0  = valueHolderForId as string
            valueSerializer.writeString(valueHolderForIdForIdx0)
        } else if (valueHolderForId instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForIdForIdx1  = valueHolderForId as number
            valueSerializer.writeNumber(valueHolderForIdForIdx1)
        }
        const valueHolderForComponentId  = value.componentId
        if (valueHolderForComponentId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForComponentIdTmpValue  = valueHolderForComponentId!
            valueSerializer.writeNumber(valueHolderForComponentIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TargetInfo {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let idTmpBuf : string | number | undefined
        if (idTmpBufUnionSelector == (0).toChar()) {
            idTmpBuf = (valueDeserializer.readString() as string)
        } else if (idTmpBufUnionSelector == (1).toChar()) {
            idTmpBuf = (valueDeserializer.readNumber() as number)
        } else {
            throw new Error("One of the branches for idTmpBuf has to be chosen through deserialisation.")
        }
        const idTmpResult : string | number = (idTmpBuf as string | number)
        const componentIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let componentIdTmpBuf : number | undefined = undefined
        if ((componentIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            componentIdTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const componentIdTmpResult : number | undefined = componentIdTmpBuf
        let value : TargetInfo = ({id: idTmpResult, componentId: componentIdTmpResult} as TargetInfo)
        return value
    }
}
