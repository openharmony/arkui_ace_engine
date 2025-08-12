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

import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Resource, Resource_serializer } from "./resource"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { GlobalScope } from "./GlobalScope"
export interface FontOptions {
    familyName: string | Resource;
    familySrc: string | Resource;
}
export interface FontInfo {
    path: string;
    postScriptName: string;
    fullName: string;
    family: string;
    subfamily: string;
    weight: number;
    width: number;
    italic: boolean;
    monoSpace: boolean;
    symbolic: boolean;
}
export class font_UIFontAdjustInfo_serializer {
    public static write(buffer: SerializerBase, value: font.UIFontAdjustInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWeight  = value.weight
        valueSerializer.writeNumber(valueHolderForWeight)
        const valueHolderForTo  = value.to
        valueSerializer.writeNumber(valueHolderForTo)
    }
    public static read(buffer: DeserializerBase): font.UIFontAdjustInfo {
        let valueDeserializer : DeserializerBase = buffer
        const weightTmpResult : number = (valueDeserializer.readNumber() as number)
        const toTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : font.UIFontAdjustInfo = ({weight: weightTmpResult, to: toTmpResult} as font.UIFontAdjustInfo)
        return value
    }
}
export class font_UIFontAliasInfo_serializer {
    public static write(buffer: SerializerBase, value: font.UIFontAliasInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForName  = value.name
        valueSerializer.writeString(valueHolderForName)
        const valueHolderForWeight  = value.weight
        valueSerializer.writeNumber(valueHolderForWeight)
    }
    public static read(buffer: DeserializerBase): font.UIFontAliasInfo {
        let valueDeserializer : DeserializerBase = buffer
        const nameTmpResult : string = (valueDeserializer.readString() as string)
        const weightTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : font.UIFontAliasInfo = ({name: nameTmpResult, weight: weightTmpResult} as font.UIFontAliasInfo)
        return value
    }
}
export class font_UIFontConfig_serializer {
    public static write(buffer: SerializerBase, value: font.UIFontConfig): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFontDir  = value.fontDir
        valueSerializer.writeInt32((valueHolderForFontDir.length).toInt())
        for (let valueHolderForFontDirCounterI = 0; valueHolderForFontDirCounterI < valueHolderForFontDir.length; valueHolderForFontDirCounterI++) {
            const valueHolderForFontDirTmpElement : string = valueHolderForFontDir[valueHolderForFontDirCounterI]
            valueSerializer.writeString(valueHolderForFontDirTmpElement)
        }
        const valueHolderForGeneric  = value.generic
        valueSerializer.writeInt32((valueHolderForGeneric.length).toInt())
        for (let valueHolderForGenericCounterI = 0; valueHolderForGenericCounterI < valueHolderForGeneric.length; valueHolderForGenericCounterI++) {
            const valueHolderForGenericTmpElement : font.UIFontGenericInfo = valueHolderForGeneric[valueHolderForGenericCounterI]
            font_UIFontGenericInfo_serializer.write(valueSerializer, valueHolderForGenericTmpElement)
        }
        const valueHolderForFallbackGroups  = value.fallbackGroups
        valueSerializer.writeInt32((valueHolderForFallbackGroups.length).toInt())
        for (let valueHolderForFallbackGroupsCounterI = 0; valueHolderForFallbackGroupsCounterI < valueHolderForFallbackGroups.length; valueHolderForFallbackGroupsCounterI++) {
            const valueHolderForFallbackGroupsTmpElement : font.UIFontFallbackGroupInfo = valueHolderForFallbackGroups[valueHolderForFallbackGroupsCounterI]
            font_UIFontFallbackGroupInfo_serializer.write(valueSerializer, valueHolderForFallbackGroupsTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): font.UIFontConfig {
        let valueDeserializer : DeserializerBase = buffer
        const fontDirTmpBufLength : int32 = valueDeserializer.readInt32()
        let fontDirTmpBuf : Array<string> = new Array<string>(fontDirTmpBufLength)
        for (let fontDirTmpBufBufCounterI = 0; fontDirTmpBufBufCounterI < fontDirTmpBufLength; fontDirTmpBufBufCounterI++) {
            fontDirTmpBuf[fontDirTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const fontDirTmpResult : Array<string> = fontDirTmpBuf
        const genericTmpBufLength : int32 = valueDeserializer.readInt32()
        let genericTmpBuf : Array<font.UIFontGenericInfo> = new Array<font.UIFontGenericInfo>(genericTmpBufLength)
        for (let genericTmpBufBufCounterI = 0; genericTmpBufBufCounterI < genericTmpBufLength; genericTmpBufBufCounterI++) {
            genericTmpBuf[genericTmpBufBufCounterI] = font_UIFontGenericInfo_serializer.read(valueDeserializer)
        }
        const genericTmpResult : Array<font.UIFontGenericInfo> = genericTmpBuf
        const fallbackGroupsTmpBufLength : int32 = valueDeserializer.readInt32()
        let fallbackGroupsTmpBuf : Array<font.UIFontFallbackGroupInfo> = new Array<font.UIFontFallbackGroupInfo>(fallbackGroupsTmpBufLength)
        for (let fallbackGroupsTmpBufBufCounterI = 0; fallbackGroupsTmpBufBufCounterI < fallbackGroupsTmpBufLength; fallbackGroupsTmpBufBufCounterI++) {
            fallbackGroupsTmpBuf[fallbackGroupsTmpBufBufCounterI] = font_UIFontFallbackGroupInfo_serializer.read(valueDeserializer)
        }
        const fallbackGroupsTmpResult : Array<font.UIFontFallbackGroupInfo> = fallbackGroupsTmpBuf
        let value : font.UIFontConfig = ({fontDir: fontDirTmpResult, generic: genericTmpResult, fallbackGroups: fallbackGroupsTmpResult} as font.UIFontConfig)
        return value
    }
}
export class font_UIFontFallbackGroupInfo_serializer {
    public static write(buffer: SerializerBase, value: font.UIFontFallbackGroupInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFontSetName  = value.fontSetName
        valueSerializer.writeString(valueHolderForFontSetName)
        const valueHolderForFallback  = value.fallback
        valueSerializer.writeInt32((valueHolderForFallback.length).toInt())
        for (let valueHolderForFallbackCounterI = 0; valueHolderForFallbackCounterI < valueHolderForFallback.length; valueHolderForFallbackCounterI++) {
            const valueHolderForFallbackTmpElement : font.UIFontFallbackInfo = valueHolderForFallback[valueHolderForFallbackCounterI]
            font_UIFontFallbackInfo_serializer.write(valueSerializer, valueHolderForFallbackTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): font.UIFontFallbackGroupInfo {
        let valueDeserializer : DeserializerBase = buffer
        const fontSetNameTmpResult : string = (valueDeserializer.readString() as string)
        const fallbackTmpBufLength : int32 = valueDeserializer.readInt32()
        let fallbackTmpBuf : Array<font.UIFontFallbackInfo> = new Array<font.UIFontFallbackInfo>(fallbackTmpBufLength)
        for (let fallbackTmpBufBufCounterI = 0; fallbackTmpBufBufCounterI < fallbackTmpBufLength; fallbackTmpBufBufCounterI++) {
            fallbackTmpBuf[fallbackTmpBufBufCounterI] = font_UIFontFallbackInfo_serializer.read(valueDeserializer)
        }
        const fallbackTmpResult : Array<font.UIFontFallbackInfo> = fallbackTmpBuf
        let value : font.UIFontFallbackGroupInfo = ({fontSetName: fontSetNameTmpResult, fallback: fallbackTmpResult} as font.UIFontFallbackGroupInfo)
        return value
    }
}
export class font_UIFontFallbackInfo_serializer {
    public static write(buffer: SerializerBase, value: font.UIFontFallbackInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForLanguage  = value.language
        valueSerializer.writeString(valueHolderForLanguage)
        const valueHolderForFamily  = value.family
        valueSerializer.writeString(valueHolderForFamily)
    }
    public static read(buffer: DeserializerBase): font.UIFontFallbackInfo {
        let valueDeserializer : DeserializerBase = buffer
        const languageTmpResult : string = (valueDeserializer.readString() as string)
        const familyTmpResult : string = (valueDeserializer.readString() as string)
        let value : font.UIFontFallbackInfo = ({language: languageTmpResult, family: familyTmpResult} as font.UIFontFallbackInfo)
        return value
    }
}
export class font_UIFontGenericInfo_serializer {
    public static write(buffer: SerializerBase, value: font.UIFontGenericInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFamily  = value.family
        valueSerializer.writeString(valueHolderForFamily)
        const valueHolderForAlias  = value.alias
        valueSerializer.writeInt32((valueHolderForAlias.length).toInt())
        for (let valueHolderForAliasCounterI = 0; valueHolderForAliasCounterI < valueHolderForAlias.length; valueHolderForAliasCounterI++) {
            const valueHolderForAliasTmpElement : font.UIFontAliasInfo = valueHolderForAlias[valueHolderForAliasCounterI]
            font_UIFontAliasInfo_serializer.write(valueSerializer, valueHolderForAliasTmpElement)
        }
        const valueHolderForAdjust  = value.adjust
        valueSerializer.writeInt32((valueHolderForAdjust.length).toInt())
        for (let valueHolderForAdjustCounterI = 0; valueHolderForAdjustCounterI < valueHolderForAdjust.length; valueHolderForAdjustCounterI++) {
            const valueHolderForAdjustTmpElement : font.UIFontAdjustInfo = valueHolderForAdjust[valueHolderForAdjustCounterI]
            font_UIFontAdjustInfo_serializer.write(valueSerializer, valueHolderForAdjustTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): font.UIFontGenericInfo {
        let valueDeserializer : DeserializerBase = buffer
        const familyTmpResult : string = (valueDeserializer.readString() as string)
        const aliasTmpBufLength : int32 = valueDeserializer.readInt32()
        let aliasTmpBuf : Array<font.UIFontAliasInfo> = new Array<font.UIFontAliasInfo>(aliasTmpBufLength)
        for (let aliasTmpBufBufCounterI = 0; aliasTmpBufBufCounterI < aliasTmpBufLength; aliasTmpBufBufCounterI++) {
            aliasTmpBuf[aliasTmpBufBufCounterI] = font_UIFontAliasInfo_serializer.read(valueDeserializer)
        }
        const aliasTmpResult : Array<font.UIFontAliasInfo> = aliasTmpBuf
        const adjustTmpBufLength : int32 = valueDeserializer.readInt32()
        let adjustTmpBuf : Array<font.UIFontAdjustInfo> = new Array<font.UIFontAdjustInfo>(adjustTmpBufLength)
        for (let adjustTmpBufBufCounterI = 0; adjustTmpBufBufCounterI < adjustTmpBufLength; adjustTmpBufBufCounterI++) {
            adjustTmpBuf[adjustTmpBufBufCounterI] = font_UIFontAdjustInfo_serializer.read(valueDeserializer)
        }
        const adjustTmpResult : Array<font.UIFontAdjustInfo> = adjustTmpBuf
        let value : font.UIFontGenericInfo = ({family: familyTmpResult, alias: aliasTmpResult, adjust: adjustTmpResult} as font.UIFontGenericInfo)
        return value
    }
}
export class FontInfo_serializer {
    public static write(buffer: SerializerBase, value: FontInfo): void {
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
        valueSerializer.writeNumber(valueHolderForWeight)
        const valueHolderForWidth  = value.width
        valueSerializer.writeNumber(valueHolderForWidth)
        const valueHolderForItalic  = value.italic
        valueSerializer.writeBoolean(valueHolderForItalic)
        const valueHolderForMonoSpace  = value.monoSpace
        valueSerializer.writeBoolean(valueHolderForMonoSpace)
        const valueHolderForSymbolic  = value.symbolic
        valueSerializer.writeBoolean(valueHolderForSymbolic)
    }
    public static read(buffer: DeserializerBase): FontInfo {
        let valueDeserializer : DeserializerBase = buffer
        const pathTmpResult : string = (valueDeserializer.readString() as string)
        const postScriptNameTmpResult : string = (valueDeserializer.readString() as string)
        const fullNameTmpResult : string = (valueDeserializer.readString() as string)
        const familyTmpResult : string = (valueDeserializer.readString() as string)
        const subfamilyTmpResult : string = (valueDeserializer.readString() as string)
        const weightTmpResult : number = (valueDeserializer.readNumber() as number)
        const widthTmpResult : number = (valueDeserializer.readNumber() as number)
        const italicTmpResult : boolean = valueDeserializer.readBoolean()
        const monoSpaceTmpResult : boolean = valueDeserializer.readBoolean()
        const symbolicTmpResult : boolean = valueDeserializer.readBoolean()
        let value : FontInfo = ({path: pathTmpResult, postScriptName: postScriptNameTmpResult, fullName: fullNameTmpResult, family: familyTmpResult, subfamily: subfamilyTmpResult, weight: weightTmpResult, width: widthTmpResult, italic: italicTmpResult, monoSpace: monoSpaceTmpResult, symbolic: symbolicTmpResult} as FontInfo)
        return value
    }
}
export class FontOptions_serializer {
    public static write(buffer: SerializerBase, value: FontOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFamilyName  = value.familyName
        if (valueHolderForFamilyName instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForFamilyNameForIdx0  = valueHolderForFamilyName as string
            valueSerializer.writeString(valueHolderForFamilyNameForIdx0)
        } else if (valueHolderForFamilyName instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForFamilyNameForIdx1  = valueHolderForFamilyName as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFamilyNameForIdx1)
        }
        const valueHolderForFamilySrc  = value.familySrc
        if (valueHolderForFamilySrc instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForFamilySrcForIdx0  = valueHolderForFamilySrc as string
            valueSerializer.writeString(valueHolderForFamilySrcForIdx0)
        } else if (valueHolderForFamilySrc instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForFamilySrcForIdx1  = valueHolderForFamilySrc as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFamilySrcForIdx1)
        }
    }
    public static read(buffer: DeserializerBase): FontOptions {
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
        let value : FontOptions = ({familyName: familyNameTmpResult, familySrc: familySrcTmpResult} as FontOptions)
        return value
    }
}
export namespace font {
    export interface UIFontFallbackInfo {
        language: string;
        family: string;
    }
    export interface UIFontAliasInfo {
        name: string;
        weight: number;
    }
    export interface UIFontAdjustInfo {
        weight: number;
        to: number;
    }
    export interface UIFontGenericInfo {
        family: string;
        alias: Array<font.UIFontAliasInfo>;
        adjust: Array<font.UIFontAdjustInfo>;
    }
    export interface UIFontFallbackGroupInfo {
        fontSetName: string;
        fallback: Array<font.UIFontFallbackInfo>;
    }
    export interface UIFontConfig {
        fontDir: Array<string>;
        generic: Array<font.UIFontGenericInfo>;
        fallbackGroups: Array<font.UIFontFallbackGroupInfo>;
    }
    export function getUIFontConfig(): UIFontConfig {
        return GlobalScope.font_getUIFontConfig()
    }
}
