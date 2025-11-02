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

import { default as font } from "@ohos.font"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer } from "./resource"
import { Resource } from "global.resource"
export class font_FontInfo_serializer {
    public static write(buffer: SerializerBase, value: font.FontInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPath  = value.path
        valueSerializer.writeString(valueHolderForPath)
        const valueHolderForPostScriptName  = value.postScriptName
        valueSerializer.writeString(valueHolderForPostScriptName)
        const valueHolderForFullName  = value.fullName
        valueSerializer.writeString(valueHolderForFullName)
        const valueHolderForFamily  = value.family
        valueSerializer.writeString(valueHolderForFamily)
        const valueHolderForSubfamily  = value.subfamily
        valueSerializer.writeString(valueHolderForSubfamily)
        const valueHolderForWeight  = value.weight
        valueSerializer.writeInt32(valueHolderForWeight)
        const valueHolderForWidth  = value.width
        valueSerializer.writeInt32(valueHolderForWidth)
        const valueHolderForItalic  = value.italic
        valueSerializer.writeBoolean(valueHolderForItalic)
        const valueHolderForMonoSpace  = value.monoSpace
        valueSerializer.writeBoolean(valueHolderForMonoSpace)
        const valueHolderForSymbolic  = value.symbolic
        valueSerializer.writeBoolean(valueHolderForSymbolic)
    }
    public static read(buffer: DeserializerBase): font.FontInfo {
        let valueDeserializer : DeserializerBase = buffer
        const pathTmpResult : string = (valueDeserializer.readString() as string)
        const postScriptNameTmpResult : string = (valueDeserializer.readString() as string)
        const fullNameTmpResult : string = (valueDeserializer.readString() as string)
        const familyTmpResult : string = (valueDeserializer.readString() as string)
        const subfamilyTmpResult : string = (valueDeserializer.readString() as string)
        const weightTmpResult : int32 = valueDeserializer.readInt32()
        const widthTmpResult : int32 = valueDeserializer.readInt32()
        const italicTmpResult : boolean = valueDeserializer.readBoolean()
        const monoSpaceTmpResult : boolean = valueDeserializer.readBoolean()
        const symbolicTmpResult : boolean = valueDeserializer.readBoolean()
        let value : font.FontInfo = ({path: pathTmpResult, postScriptName: postScriptNameTmpResult, fullName: fullNameTmpResult, family: familyTmpResult, subfamily: subfamilyTmpResult, weight: weightTmpResult, width: widthTmpResult, italic: italicTmpResult, monoSpace: monoSpaceTmpResult, symbolic: symbolicTmpResult} as font.FontInfo)
        return value
    }
}
export class font_FontOptions_serializer {
    public static write(buffer: SerializerBase, value: font.FontOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFamilyName  = value.familyName
        if (valueHolderForFamilyName instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForFamilyNameForIdx0  = valueHolderForFamilyName as string
            valueSerializer.writeString(valueHolderForFamilyNameForIdx0)
        } else if (valueHolderForFamilyName instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForFamilyNameForIdx1  = valueHolderForFamilyName as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFamilyNameForIdx1)
        }
        const valueHolderForFamilySrc  = value.familySrc
        if (valueHolderForFamilySrc instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForFamilySrcForIdx0  = valueHolderForFamilySrc as string
            valueSerializer.writeString(valueHolderForFamilySrcForIdx0)
        } else if (valueHolderForFamilySrc instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForFamilySrcForIdx1  = valueHolderForFamilySrc as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFamilySrcForIdx1)
        }
    }
    public static read(buffer: DeserializerBase): font.FontOptions {
        let valueDeserializer : DeserializerBase = buffer
        const familyNameTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let familyNameTmpBuf : string | Resource | undefined
        if (familyNameTmpBufUnionSelector == (0).toChar()) {
            familyNameTmpBuf = (valueDeserializer.readString() as string)
        } else if (familyNameTmpBufUnionSelector == (1).toChar()) {
            familyNameTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for familyNameTmpBuf has to be chosen through deserialisation.")
        }
        const familyNameTmpResult : string | Resource = (familyNameTmpBuf as string | Resource)
        const familySrcTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let familySrcTmpBuf : string | Resource | undefined
        if (familySrcTmpBufUnionSelector == (0).toChar()) {
            familySrcTmpBuf = (valueDeserializer.readString() as string)
        } else if (familySrcTmpBufUnionSelector == (1).toChar()) {
            familySrcTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for familySrcTmpBuf has to be chosen through deserialisation.")
        }
        const familySrcTmpResult : string | Resource = (familySrcTmpBuf as string | Resource)
        let value : font.FontOptions = ({familyName: familyNameTmpResult, familySrc: familySrcTmpResult} as font.FontOptions)
        return value
    }
}
