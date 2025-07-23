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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, KInt, KBoolean, KStringPtr, wrapCallback } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { GlobalScope } from "./GlobalScope"
export class font_UIFontAdjustInfo_serializer {
    public static write(buffer: SerializerBase, value: font.UIFontAdjustInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_weight  = value.weight
        valueSerializer.writeNumber(value_weight)
        const value_to  = value.to
        valueSerializer.writeNumber(value_to)
    }
    public static read(buffer: DeserializerBase): font.UIFontAdjustInfo {
        let valueDeserializer : DeserializerBase = buffer
        const weight_result : number = (valueDeserializer.readNumber() as number)
        const to_result : number = (valueDeserializer.readNumber() as number)
        let value : font.UIFontAdjustInfo = ({weight: weight_result, to: to_result} as font.UIFontAdjustInfo)
        return value
    }
}
export class font_UIFontAliasInfo_serializer {
    public static write(buffer: SerializerBase, value: font.UIFontAliasInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_name  = value.name
        valueSerializer.writeString(value_name)
        const value_weight  = value.weight
        valueSerializer.writeNumber(value_weight)
    }
    public static read(buffer: DeserializerBase): font.UIFontAliasInfo {
        let valueDeserializer : DeserializerBase = buffer
        const name_result : string = (valueDeserializer.readString() as string)
        const weight_result : number = (valueDeserializer.readNumber() as number)
        let value : font.UIFontAliasInfo = ({name: name_result, weight: weight_result} as font.UIFontAliasInfo)
        return value
    }
}
export class font_UIFontConfig_serializer {
    public static write(buffer: SerializerBase, value: font.UIFontConfig): void {
        let valueSerializer : SerializerBase = buffer
        const value_fontDir  = value.fontDir
        valueSerializer.writeInt32((value_fontDir.length).toInt())
        for (let value_fontDir_counter_i = 0; value_fontDir_counter_i < value_fontDir.length; value_fontDir_counter_i++) {
            const value_fontDir_element : string = value_fontDir[value_fontDir_counter_i]
            valueSerializer.writeString(value_fontDir_element)
        }
        const value_generic  = value.generic
        valueSerializer.writeInt32((value_generic.length).toInt())
        for (let value_generic_counter_i = 0; value_generic_counter_i < value_generic.length; value_generic_counter_i++) {
            const value_generic_element : font.UIFontGenericInfo = value_generic[value_generic_counter_i]
            font_UIFontGenericInfo_serializer.write(valueSerializer, value_generic_element)
        }
        const value_fallbackGroups  = value.fallbackGroups
        valueSerializer.writeInt32((value_fallbackGroups.length).toInt())
        for (let value_fallbackGroups_counter_i = 0; value_fallbackGroups_counter_i < value_fallbackGroups.length; value_fallbackGroups_counter_i++) {
            const value_fallbackGroups_element : font.UIFontFallbackGroupInfo = value_fallbackGroups[value_fallbackGroups_counter_i]
            font_UIFontFallbackGroupInfo_serializer.write(valueSerializer, value_fallbackGroups_element)
        }
    }
    public static read(buffer: DeserializerBase): font.UIFontConfig {
        let valueDeserializer : DeserializerBase = buffer
        const fontDir_buf_length : int32 = valueDeserializer.readInt32()
        let fontDir_buf : Array<string> = new Array<string>(fontDir_buf_length)
        for (let fontDir_buf_i = 0; fontDir_buf_i < fontDir_buf_length; fontDir_buf_i++) {
            fontDir_buf[fontDir_buf_i] = (valueDeserializer.readString() as string)
        }
        const fontDir_result : Array<string> = fontDir_buf
        const generic_buf_length : int32 = valueDeserializer.readInt32()
        let generic_buf : Array<font.UIFontGenericInfo> = new Array<font.UIFontGenericInfo>(generic_buf_length)
        for (let generic_buf_i = 0; generic_buf_i < generic_buf_length; generic_buf_i++) {
            generic_buf[generic_buf_i] = font_UIFontGenericInfo_serializer.read(valueDeserializer)
        }
        const generic_result : Array<font.UIFontGenericInfo> = generic_buf
        const fallbackGroups_buf_length : int32 = valueDeserializer.readInt32()
        let fallbackGroups_buf : Array<font.UIFontFallbackGroupInfo> = new Array<font.UIFontFallbackGroupInfo>(fallbackGroups_buf_length)
        for (let fallbackGroups_buf_i = 0; fallbackGroups_buf_i < fallbackGroups_buf_length; fallbackGroups_buf_i++) {
            fallbackGroups_buf[fallbackGroups_buf_i] = font_UIFontFallbackGroupInfo_serializer.read(valueDeserializer)
        }
        const fallbackGroups_result : Array<font.UIFontFallbackGroupInfo> = fallbackGroups_buf
        let value : font.UIFontConfig = ({fontDir: fontDir_result, generic: generic_result, fallbackGroups: fallbackGroups_result} as font.UIFontConfig)
        return value
    }
}
export class font_UIFontFallbackGroupInfo_serializer {
    public static write(buffer: SerializerBase, value: font.UIFontFallbackGroupInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_fontSetName  = value.fontSetName
        valueSerializer.writeString(value_fontSetName)
        const value_fallback  = value.fallback
        valueSerializer.writeInt32((value_fallback.length).toInt())
        for (let value_fallback_counter_i = 0; value_fallback_counter_i < value_fallback.length; value_fallback_counter_i++) {
            const value_fallback_element : font.UIFontFallbackInfo = value_fallback[value_fallback_counter_i]
            font_UIFontFallbackInfo_serializer.write(valueSerializer, value_fallback_element)
        }
    }
    public static read(buffer: DeserializerBase): font.UIFontFallbackGroupInfo {
        let valueDeserializer : DeserializerBase = buffer
        const fontSetName_result : string = (valueDeserializer.readString() as string)
        const fallback_buf_length : int32 = valueDeserializer.readInt32()
        let fallback_buf : Array<font.UIFontFallbackInfo> = new Array<font.UIFontFallbackInfo>(fallback_buf_length)
        for (let fallback_buf_i = 0; fallback_buf_i < fallback_buf_length; fallback_buf_i++) {
            fallback_buf[fallback_buf_i] = font_UIFontFallbackInfo_serializer.read(valueDeserializer)
        }
        const fallback_result : Array<font.UIFontFallbackInfo> = fallback_buf
        let value : font.UIFontFallbackGroupInfo = ({fontSetName: fontSetName_result, fallback: fallback_result} as font.UIFontFallbackGroupInfo)
        return value
    }
}
export class font_UIFontFallbackInfo_serializer {
    public static write(buffer: SerializerBase, value: font.UIFontFallbackInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_language  = value.language
        valueSerializer.writeString(value_language)
        const value_family  = value.family
        valueSerializer.writeString(value_family)
    }
    public static read(buffer: DeserializerBase): font.UIFontFallbackInfo {
        let valueDeserializer : DeserializerBase = buffer
        const language_result : string = (valueDeserializer.readString() as string)
        const family_result : string = (valueDeserializer.readString() as string)
        let value : font.UIFontFallbackInfo = ({language: language_result, family: family_result} as font.UIFontFallbackInfo)
        return value
    }
}
export class font_UIFontGenericInfo_serializer {
    public static write(buffer: SerializerBase, value: font.UIFontGenericInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_family  = value.family
        valueSerializer.writeString(value_family)
        const value_alias  = value.alias
        valueSerializer.writeInt32((value_alias.length).toInt())
        for (let value_alias_counter_i = 0; value_alias_counter_i < value_alias.length; value_alias_counter_i++) {
            const value_alias_element : font.UIFontAliasInfo = value_alias[value_alias_counter_i]
            font_UIFontAliasInfo_serializer.write(valueSerializer, value_alias_element)
        }
        const value_adjust  = value.adjust
        valueSerializer.writeInt32((value_adjust.length).toInt())
        for (let value_adjust_counter_i = 0; value_adjust_counter_i < value_adjust.length; value_adjust_counter_i++) {
            const value_adjust_element : font.UIFontAdjustInfo = value_adjust[value_adjust_counter_i]
            font_UIFontAdjustInfo_serializer.write(valueSerializer, value_adjust_element)
        }
    }
    public static read(buffer: DeserializerBase): font.UIFontGenericInfo {
        let valueDeserializer : DeserializerBase = buffer
        const family_result : string = (valueDeserializer.readString() as string)
        const alias_buf_length : int32 = valueDeserializer.readInt32()
        let alias_buf : Array<font.UIFontAliasInfo> = new Array<font.UIFontAliasInfo>(alias_buf_length)
        for (let alias_buf_i = 0; alias_buf_i < alias_buf_length; alias_buf_i++) {
            alias_buf[alias_buf_i] = font_UIFontAliasInfo_serializer.read(valueDeserializer)
        }
        const alias_result : Array<font.UIFontAliasInfo> = alias_buf
        const adjust_buf_length : int32 = valueDeserializer.readInt32()
        let adjust_buf : Array<font.UIFontAdjustInfo> = new Array<font.UIFontAdjustInfo>(adjust_buf_length)
        for (let adjust_buf_i = 0; adjust_buf_i < adjust_buf_length; adjust_buf_i++) {
            adjust_buf[adjust_buf_i] = font_UIFontAdjustInfo_serializer.read(valueDeserializer)
        }
        const adjust_result : Array<font.UIFontAdjustInfo> = adjust_buf
        let value : font.UIFontGenericInfo = ({family: family_result, alias: alias_result, adjust: adjust_result} as font.UIFontGenericInfo)
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
