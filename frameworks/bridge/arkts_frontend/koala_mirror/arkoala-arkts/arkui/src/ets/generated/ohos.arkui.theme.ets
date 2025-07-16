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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { ResourceColor } from "./../component/units"
import { Color } from "./../component/enums"
import { Resource, Resource_serializer } from "./resource"
export class ThemeControlInternal {
    public static fromPtr(ptr: KPointer): ThemeControl {
        return new ThemeControl(ptr)
    }
}
export class ThemeControl implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ThemeControl.getFinalizer())
    }
    constructor() {
        this(ThemeControl.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ThemeControl_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ThemeControl_getFinalizer()
    }
    private static setDefaultTheme_serialize(theme: CustomTheme): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        CustomTheme_serializer.write(thisSerializer, theme)
        ArkUIGeneratedNativeModule._ThemeControl_setDefaultTheme(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static setDefaultTheme(theme: CustomTheme): void {
        const theme_casted = theme as (CustomTheme)
        ThemeControl.setDefaultTheme_serialize(theme_casted)
        return
    }
}
export interface Theme {
    colors: Colors;
}
export interface Colors {
    brand: ResourceColor;
    warning: ResourceColor;
    alert: ResourceColor;
    confirm: ResourceColor;
    fontPrimary: ResourceColor;
    fontSecondary: ResourceColor;
    fontTertiary: ResourceColor;
    fontFourth: ResourceColor;
    fontEmphasize: ResourceColor;
    fontOnPrimary: ResourceColor;
    fontOnSecondary: ResourceColor;
    fontOnTertiary: ResourceColor;
    fontOnFourth: ResourceColor;
    iconPrimary: ResourceColor;
    iconSecondary: ResourceColor;
    iconTertiary: ResourceColor;
    iconFourth: ResourceColor;
    iconEmphasize: ResourceColor;
    iconSubEmphasize: ResourceColor;
    iconOnPrimary: ResourceColor;
    iconOnSecondary: ResourceColor;
    iconOnTertiary: ResourceColor;
    iconOnFourth: ResourceColor;
    backgroundPrimary: ResourceColor;
    backgroundSecondary: ResourceColor;
    backgroundTertiary: ResourceColor;
    backgroundFourth: ResourceColor;
    backgroundEmphasize: ResourceColor;
    compForegroundPrimary: ResourceColor;
    compBackgroundPrimary: ResourceColor;
    compBackgroundPrimaryTran: ResourceColor;
    compBackgroundPrimaryContrary: ResourceColor;
    compBackgroundGray: ResourceColor;
    compBackgroundSecondary: ResourceColor;
    compBackgroundTertiary: ResourceColor;
    compBackgroundEmphasize: ResourceColor;
    compBackgroundNeutral: ResourceColor;
    compEmphasizeSecondary: ResourceColor;
    compEmphasizeTertiary: ResourceColor;
    compDivider: ResourceColor;
    compCommonContrary: ResourceColor;
    compBackgroundFocus: ResourceColor;
    compFocusedPrimary: ResourceColor;
    compFocusedSecondary: ResourceColor;
    compFocusedTertiary: ResourceColor;
    interactiveHover: ResourceColor;
    interactivePressed: ResourceColor;
    interactiveFocus: ResourceColor;
    interactiveActive: ResourceColor;
    interactiveSelect: ResourceColor;
    interactiveClick: ResourceColor;
}
export interface CustomTheme {
    colors?: Colors;
}
export type CustomColors = Colors;
export class ThemeControl_serializer {
    public static write(buffer: SerializerBase, value: ThemeControl): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ThemeControl {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ThemeControlInternal.fromPtr(ptr)
    }
}
export class Colors_serializer {
    public static write(buffer: SerializerBase, value: Colors): void {
        let valueSerializer : SerializerBase = buffer
        const value_brand  = value.brand
        let value_brand_type : int32 = RuntimeType.UNDEFINED
        value_brand_type = runtimeType(value_brand)
        if (TypeChecker.isColor(value_brand)) {
            valueSerializer.writeInt8((0).toChar())
            const value_brand_0  = value_brand as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_brand_0))
        }
        else if (RuntimeType.NUMBER == value_brand_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_brand_1  = value_brand as number
            valueSerializer.writeNumber(value_brand_1)
        }
        else if (RuntimeType.STRING == value_brand_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_brand_2  = value_brand as string
            valueSerializer.writeString(value_brand_2)
        }
        else if (RuntimeType.OBJECT == value_brand_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_brand_3  = value_brand as Resource
            Resource_serializer.write(valueSerializer, value_brand_3)
        }
        const value_warning  = value.warning
        let value_warning_type : int32 = RuntimeType.UNDEFINED
        value_warning_type = runtimeType(value_warning)
        if (TypeChecker.isColor(value_warning)) {
            valueSerializer.writeInt8((0).toChar())
            const value_warning_0  = value_warning as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_warning_0))
        }
        else if (RuntimeType.NUMBER == value_warning_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_warning_1  = value_warning as number
            valueSerializer.writeNumber(value_warning_1)
        }
        else if (RuntimeType.STRING == value_warning_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_warning_2  = value_warning as string
            valueSerializer.writeString(value_warning_2)
        }
        else if (RuntimeType.OBJECT == value_warning_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_warning_3  = value_warning as Resource
            Resource_serializer.write(valueSerializer, value_warning_3)
        }
        const value_alert  = value.alert
        let value_alert_type : int32 = RuntimeType.UNDEFINED
        value_alert_type = runtimeType(value_alert)
        if (TypeChecker.isColor(value_alert)) {
            valueSerializer.writeInt8((0).toChar())
            const value_alert_0  = value_alert as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_alert_0))
        }
        else if (RuntimeType.NUMBER == value_alert_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_alert_1  = value_alert as number
            valueSerializer.writeNumber(value_alert_1)
        }
        else if (RuntimeType.STRING == value_alert_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_alert_2  = value_alert as string
            valueSerializer.writeString(value_alert_2)
        }
        else if (RuntimeType.OBJECT == value_alert_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_alert_3  = value_alert as Resource
            Resource_serializer.write(valueSerializer, value_alert_3)
        }
        const value_confirm  = value.confirm
        let value_confirm_type : int32 = RuntimeType.UNDEFINED
        value_confirm_type = runtimeType(value_confirm)
        if (TypeChecker.isColor(value_confirm)) {
            valueSerializer.writeInt8((0).toChar())
            const value_confirm_0  = value_confirm as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_confirm_0))
        }
        else if (RuntimeType.NUMBER == value_confirm_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_confirm_1  = value_confirm as number
            valueSerializer.writeNumber(value_confirm_1)
        }
        else if (RuntimeType.STRING == value_confirm_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_confirm_2  = value_confirm as string
            valueSerializer.writeString(value_confirm_2)
        }
        else if (RuntimeType.OBJECT == value_confirm_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_confirm_3  = value_confirm as Resource
            Resource_serializer.write(valueSerializer, value_confirm_3)
        }
        const value_fontPrimary  = value.fontPrimary
        let value_fontPrimary_type : int32 = RuntimeType.UNDEFINED
        value_fontPrimary_type = runtimeType(value_fontPrimary)
        if (TypeChecker.isColor(value_fontPrimary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_fontPrimary_0  = value_fontPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontPrimary_0))
        }
        else if (RuntimeType.NUMBER == value_fontPrimary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_fontPrimary_1  = value_fontPrimary as number
            valueSerializer.writeNumber(value_fontPrimary_1)
        }
        else if (RuntimeType.STRING == value_fontPrimary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_fontPrimary_2  = value_fontPrimary as string
            valueSerializer.writeString(value_fontPrimary_2)
        }
        else if (RuntimeType.OBJECT == value_fontPrimary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_fontPrimary_3  = value_fontPrimary as Resource
            Resource_serializer.write(valueSerializer, value_fontPrimary_3)
        }
        const value_fontSecondary  = value.fontSecondary
        let value_fontSecondary_type : int32 = RuntimeType.UNDEFINED
        value_fontSecondary_type = runtimeType(value_fontSecondary)
        if (TypeChecker.isColor(value_fontSecondary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_fontSecondary_0  = value_fontSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontSecondary_0))
        }
        else if (RuntimeType.NUMBER == value_fontSecondary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_fontSecondary_1  = value_fontSecondary as number
            valueSerializer.writeNumber(value_fontSecondary_1)
        }
        else if (RuntimeType.STRING == value_fontSecondary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_fontSecondary_2  = value_fontSecondary as string
            valueSerializer.writeString(value_fontSecondary_2)
        }
        else if (RuntimeType.OBJECT == value_fontSecondary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_fontSecondary_3  = value_fontSecondary as Resource
            Resource_serializer.write(valueSerializer, value_fontSecondary_3)
        }
        const value_fontTertiary  = value.fontTertiary
        let value_fontTertiary_type : int32 = RuntimeType.UNDEFINED
        value_fontTertiary_type = runtimeType(value_fontTertiary)
        if (TypeChecker.isColor(value_fontTertiary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_fontTertiary_0  = value_fontTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontTertiary_0))
        }
        else if (RuntimeType.NUMBER == value_fontTertiary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_fontTertiary_1  = value_fontTertiary as number
            valueSerializer.writeNumber(value_fontTertiary_1)
        }
        else if (RuntimeType.STRING == value_fontTertiary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_fontTertiary_2  = value_fontTertiary as string
            valueSerializer.writeString(value_fontTertiary_2)
        }
        else if (RuntimeType.OBJECT == value_fontTertiary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_fontTertiary_3  = value_fontTertiary as Resource
            Resource_serializer.write(valueSerializer, value_fontTertiary_3)
        }
        const value_fontFourth  = value.fontFourth
        let value_fontFourth_type : int32 = RuntimeType.UNDEFINED
        value_fontFourth_type = runtimeType(value_fontFourth)
        if (TypeChecker.isColor(value_fontFourth)) {
            valueSerializer.writeInt8((0).toChar())
            const value_fontFourth_0  = value_fontFourth as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontFourth_0))
        }
        else if (RuntimeType.NUMBER == value_fontFourth_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_fontFourth_1  = value_fontFourth as number
            valueSerializer.writeNumber(value_fontFourth_1)
        }
        else if (RuntimeType.STRING == value_fontFourth_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_fontFourth_2  = value_fontFourth as string
            valueSerializer.writeString(value_fontFourth_2)
        }
        else if (RuntimeType.OBJECT == value_fontFourth_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_fontFourth_3  = value_fontFourth as Resource
            Resource_serializer.write(valueSerializer, value_fontFourth_3)
        }
        const value_fontEmphasize  = value.fontEmphasize
        let value_fontEmphasize_type : int32 = RuntimeType.UNDEFINED
        value_fontEmphasize_type = runtimeType(value_fontEmphasize)
        if (TypeChecker.isColor(value_fontEmphasize)) {
            valueSerializer.writeInt8((0).toChar())
            const value_fontEmphasize_0  = value_fontEmphasize as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontEmphasize_0))
        }
        else if (RuntimeType.NUMBER == value_fontEmphasize_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_fontEmphasize_1  = value_fontEmphasize as number
            valueSerializer.writeNumber(value_fontEmphasize_1)
        }
        else if (RuntimeType.STRING == value_fontEmphasize_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_fontEmphasize_2  = value_fontEmphasize as string
            valueSerializer.writeString(value_fontEmphasize_2)
        }
        else if (RuntimeType.OBJECT == value_fontEmphasize_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_fontEmphasize_3  = value_fontEmphasize as Resource
            Resource_serializer.write(valueSerializer, value_fontEmphasize_3)
        }
        const value_fontOnPrimary  = value.fontOnPrimary
        let value_fontOnPrimary_type : int32 = RuntimeType.UNDEFINED
        value_fontOnPrimary_type = runtimeType(value_fontOnPrimary)
        if (TypeChecker.isColor(value_fontOnPrimary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_fontOnPrimary_0  = value_fontOnPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontOnPrimary_0))
        }
        else if (RuntimeType.NUMBER == value_fontOnPrimary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_fontOnPrimary_1  = value_fontOnPrimary as number
            valueSerializer.writeNumber(value_fontOnPrimary_1)
        }
        else if (RuntimeType.STRING == value_fontOnPrimary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_fontOnPrimary_2  = value_fontOnPrimary as string
            valueSerializer.writeString(value_fontOnPrimary_2)
        }
        else if (RuntimeType.OBJECT == value_fontOnPrimary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_fontOnPrimary_3  = value_fontOnPrimary as Resource
            Resource_serializer.write(valueSerializer, value_fontOnPrimary_3)
        }
        const value_fontOnSecondary  = value.fontOnSecondary
        let value_fontOnSecondary_type : int32 = RuntimeType.UNDEFINED
        value_fontOnSecondary_type = runtimeType(value_fontOnSecondary)
        if (TypeChecker.isColor(value_fontOnSecondary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_fontOnSecondary_0  = value_fontOnSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontOnSecondary_0))
        }
        else if (RuntimeType.NUMBER == value_fontOnSecondary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_fontOnSecondary_1  = value_fontOnSecondary as number
            valueSerializer.writeNumber(value_fontOnSecondary_1)
        }
        else if (RuntimeType.STRING == value_fontOnSecondary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_fontOnSecondary_2  = value_fontOnSecondary as string
            valueSerializer.writeString(value_fontOnSecondary_2)
        }
        else if (RuntimeType.OBJECT == value_fontOnSecondary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_fontOnSecondary_3  = value_fontOnSecondary as Resource
            Resource_serializer.write(valueSerializer, value_fontOnSecondary_3)
        }
        const value_fontOnTertiary  = value.fontOnTertiary
        let value_fontOnTertiary_type : int32 = RuntimeType.UNDEFINED
        value_fontOnTertiary_type = runtimeType(value_fontOnTertiary)
        if (TypeChecker.isColor(value_fontOnTertiary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_fontOnTertiary_0  = value_fontOnTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontOnTertiary_0))
        }
        else if (RuntimeType.NUMBER == value_fontOnTertiary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_fontOnTertiary_1  = value_fontOnTertiary as number
            valueSerializer.writeNumber(value_fontOnTertiary_1)
        }
        else if (RuntimeType.STRING == value_fontOnTertiary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_fontOnTertiary_2  = value_fontOnTertiary as string
            valueSerializer.writeString(value_fontOnTertiary_2)
        }
        else if (RuntimeType.OBJECT == value_fontOnTertiary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_fontOnTertiary_3  = value_fontOnTertiary as Resource
            Resource_serializer.write(valueSerializer, value_fontOnTertiary_3)
        }
        const value_fontOnFourth  = value.fontOnFourth
        let value_fontOnFourth_type : int32 = RuntimeType.UNDEFINED
        value_fontOnFourth_type = runtimeType(value_fontOnFourth)
        if (TypeChecker.isColor(value_fontOnFourth)) {
            valueSerializer.writeInt8((0).toChar())
            const value_fontOnFourth_0  = value_fontOnFourth as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontOnFourth_0))
        }
        else if (RuntimeType.NUMBER == value_fontOnFourth_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_fontOnFourth_1  = value_fontOnFourth as number
            valueSerializer.writeNumber(value_fontOnFourth_1)
        }
        else if (RuntimeType.STRING == value_fontOnFourth_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_fontOnFourth_2  = value_fontOnFourth as string
            valueSerializer.writeString(value_fontOnFourth_2)
        }
        else if (RuntimeType.OBJECT == value_fontOnFourth_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_fontOnFourth_3  = value_fontOnFourth as Resource
            Resource_serializer.write(valueSerializer, value_fontOnFourth_3)
        }
        const value_iconPrimary  = value.iconPrimary
        let value_iconPrimary_type : int32 = RuntimeType.UNDEFINED
        value_iconPrimary_type = runtimeType(value_iconPrimary)
        if (TypeChecker.isColor(value_iconPrimary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_iconPrimary_0  = value_iconPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_iconPrimary_0))
        }
        else if (RuntimeType.NUMBER == value_iconPrimary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_iconPrimary_1  = value_iconPrimary as number
            valueSerializer.writeNumber(value_iconPrimary_1)
        }
        else if (RuntimeType.STRING == value_iconPrimary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_iconPrimary_2  = value_iconPrimary as string
            valueSerializer.writeString(value_iconPrimary_2)
        }
        else if (RuntimeType.OBJECT == value_iconPrimary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_iconPrimary_3  = value_iconPrimary as Resource
            Resource_serializer.write(valueSerializer, value_iconPrimary_3)
        }
        const value_iconSecondary  = value.iconSecondary
        let value_iconSecondary_type : int32 = RuntimeType.UNDEFINED
        value_iconSecondary_type = runtimeType(value_iconSecondary)
        if (TypeChecker.isColor(value_iconSecondary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_iconSecondary_0  = value_iconSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_iconSecondary_0))
        }
        else if (RuntimeType.NUMBER == value_iconSecondary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_iconSecondary_1  = value_iconSecondary as number
            valueSerializer.writeNumber(value_iconSecondary_1)
        }
        else if (RuntimeType.STRING == value_iconSecondary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_iconSecondary_2  = value_iconSecondary as string
            valueSerializer.writeString(value_iconSecondary_2)
        }
        else if (RuntimeType.OBJECT == value_iconSecondary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_iconSecondary_3  = value_iconSecondary as Resource
            Resource_serializer.write(valueSerializer, value_iconSecondary_3)
        }
        const value_iconTertiary  = value.iconTertiary
        let value_iconTertiary_type : int32 = RuntimeType.UNDEFINED
        value_iconTertiary_type = runtimeType(value_iconTertiary)
        if (TypeChecker.isColor(value_iconTertiary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_iconTertiary_0  = value_iconTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_iconTertiary_0))
        }
        else if (RuntimeType.NUMBER == value_iconTertiary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_iconTertiary_1  = value_iconTertiary as number
            valueSerializer.writeNumber(value_iconTertiary_1)
        }
        else if (RuntimeType.STRING == value_iconTertiary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_iconTertiary_2  = value_iconTertiary as string
            valueSerializer.writeString(value_iconTertiary_2)
        }
        else if (RuntimeType.OBJECT == value_iconTertiary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_iconTertiary_3  = value_iconTertiary as Resource
            Resource_serializer.write(valueSerializer, value_iconTertiary_3)
        }
        const value_iconFourth  = value.iconFourth
        let value_iconFourth_type : int32 = RuntimeType.UNDEFINED
        value_iconFourth_type = runtimeType(value_iconFourth)
        if (TypeChecker.isColor(value_iconFourth)) {
            valueSerializer.writeInt8((0).toChar())
            const value_iconFourth_0  = value_iconFourth as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_iconFourth_0))
        }
        else if (RuntimeType.NUMBER == value_iconFourth_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_iconFourth_1  = value_iconFourth as number
            valueSerializer.writeNumber(value_iconFourth_1)
        }
        else if (RuntimeType.STRING == value_iconFourth_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_iconFourth_2  = value_iconFourth as string
            valueSerializer.writeString(value_iconFourth_2)
        }
        else if (RuntimeType.OBJECT == value_iconFourth_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_iconFourth_3  = value_iconFourth as Resource
            Resource_serializer.write(valueSerializer, value_iconFourth_3)
        }
        const value_iconEmphasize  = value.iconEmphasize
        let value_iconEmphasize_type : int32 = RuntimeType.UNDEFINED
        value_iconEmphasize_type = runtimeType(value_iconEmphasize)
        if (TypeChecker.isColor(value_iconEmphasize)) {
            valueSerializer.writeInt8((0).toChar())
            const value_iconEmphasize_0  = value_iconEmphasize as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_iconEmphasize_0))
        }
        else if (RuntimeType.NUMBER == value_iconEmphasize_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_iconEmphasize_1  = value_iconEmphasize as number
            valueSerializer.writeNumber(value_iconEmphasize_1)
        }
        else if (RuntimeType.STRING == value_iconEmphasize_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_iconEmphasize_2  = value_iconEmphasize as string
            valueSerializer.writeString(value_iconEmphasize_2)
        }
        else if (RuntimeType.OBJECT == value_iconEmphasize_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_iconEmphasize_3  = value_iconEmphasize as Resource
            Resource_serializer.write(valueSerializer, value_iconEmphasize_3)
        }
        const value_iconSubEmphasize  = value.iconSubEmphasize
        let value_iconSubEmphasize_type : int32 = RuntimeType.UNDEFINED
        value_iconSubEmphasize_type = runtimeType(value_iconSubEmphasize)
        if (TypeChecker.isColor(value_iconSubEmphasize)) {
            valueSerializer.writeInt8((0).toChar())
            const value_iconSubEmphasize_0  = value_iconSubEmphasize as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_iconSubEmphasize_0))
        }
        else if (RuntimeType.NUMBER == value_iconSubEmphasize_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_iconSubEmphasize_1  = value_iconSubEmphasize as number
            valueSerializer.writeNumber(value_iconSubEmphasize_1)
        }
        else if (RuntimeType.STRING == value_iconSubEmphasize_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_iconSubEmphasize_2  = value_iconSubEmphasize as string
            valueSerializer.writeString(value_iconSubEmphasize_2)
        }
        else if (RuntimeType.OBJECT == value_iconSubEmphasize_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_iconSubEmphasize_3  = value_iconSubEmphasize as Resource
            Resource_serializer.write(valueSerializer, value_iconSubEmphasize_3)
        }
        const value_iconOnPrimary  = value.iconOnPrimary
        let value_iconOnPrimary_type : int32 = RuntimeType.UNDEFINED
        value_iconOnPrimary_type = runtimeType(value_iconOnPrimary)
        if (TypeChecker.isColor(value_iconOnPrimary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_iconOnPrimary_0  = value_iconOnPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_iconOnPrimary_0))
        }
        else if (RuntimeType.NUMBER == value_iconOnPrimary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_iconOnPrimary_1  = value_iconOnPrimary as number
            valueSerializer.writeNumber(value_iconOnPrimary_1)
        }
        else if (RuntimeType.STRING == value_iconOnPrimary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_iconOnPrimary_2  = value_iconOnPrimary as string
            valueSerializer.writeString(value_iconOnPrimary_2)
        }
        else if (RuntimeType.OBJECT == value_iconOnPrimary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_iconOnPrimary_3  = value_iconOnPrimary as Resource
            Resource_serializer.write(valueSerializer, value_iconOnPrimary_3)
        }
        const value_iconOnSecondary  = value.iconOnSecondary
        let value_iconOnSecondary_type : int32 = RuntimeType.UNDEFINED
        value_iconOnSecondary_type = runtimeType(value_iconOnSecondary)
        if (TypeChecker.isColor(value_iconOnSecondary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_iconOnSecondary_0  = value_iconOnSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_iconOnSecondary_0))
        }
        else if (RuntimeType.NUMBER == value_iconOnSecondary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_iconOnSecondary_1  = value_iconOnSecondary as number
            valueSerializer.writeNumber(value_iconOnSecondary_1)
        }
        else if (RuntimeType.STRING == value_iconOnSecondary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_iconOnSecondary_2  = value_iconOnSecondary as string
            valueSerializer.writeString(value_iconOnSecondary_2)
        }
        else if (RuntimeType.OBJECT == value_iconOnSecondary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_iconOnSecondary_3  = value_iconOnSecondary as Resource
            Resource_serializer.write(valueSerializer, value_iconOnSecondary_3)
        }
        const value_iconOnTertiary  = value.iconOnTertiary
        let value_iconOnTertiary_type : int32 = RuntimeType.UNDEFINED
        value_iconOnTertiary_type = runtimeType(value_iconOnTertiary)
        if (TypeChecker.isColor(value_iconOnTertiary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_iconOnTertiary_0  = value_iconOnTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_iconOnTertiary_0))
        }
        else if (RuntimeType.NUMBER == value_iconOnTertiary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_iconOnTertiary_1  = value_iconOnTertiary as number
            valueSerializer.writeNumber(value_iconOnTertiary_1)
        }
        else if (RuntimeType.STRING == value_iconOnTertiary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_iconOnTertiary_2  = value_iconOnTertiary as string
            valueSerializer.writeString(value_iconOnTertiary_2)
        }
        else if (RuntimeType.OBJECT == value_iconOnTertiary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_iconOnTertiary_3  = value_iconOnTertiary as Resource
            Resource_serializer.write(valueSerializer, value_iconOnTertiary_3)
        }
        const value_iconOnFourth  = value.iconOnFourth
        let value_iconOnFourth_type : int32 = RuntimeType.UNDEFINED
        value_iconOnFourth_type = runtimeType(value_iconOnFourth)
        if (TypeChecker.isColor(value_iconOnFourth)) {
            valueSerializer.writeInt8((0).toChar())
            const value_iconOnFourth_0  = value_iconOnFourth as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_iconOnFourth_0))
        }
        else if (RuntimeType.NUMBER == value_iconOnFourth_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_iconOnFourth_1  = value_iconOnFourth as number
            valueSerializer.writeNumber(value_iconOnFourth_1)
        }
        else if (RuntimeType.STRING == value_iconOnFourth_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_iconOnFourth_2  = value_iconOnFourth as string
            valueSerializer.writeString(value_iconOnFourth_2)
        }
        else if (RuntimeType.OBJECT == value_iconOnFourth_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_iconOnFourth_3  = value_iconOnFourth as Resource
            Resource_serializer.write(valueSerializer, value_iconOnFourth_3)
        }
        const value_backgroundPrimary  = value.backgroundPrimary
        let value_backgroundPrimary_type : int32 = RuntimeType.UNDEFINED
        value_backgroundPrimary_type = runtimeType(value_backgroundPrimary)
        if (TypeChecker.isColor(value_backgroundPrimary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_backgroundPrimary_0  = value_backgroundPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundPrimary_0))
        }
        else if (RuntimeType.NUMBER == value_backgroundPrimary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_backgroundPrimary_1  = value_backgroundPrimary as number
            valueSerializer.writeNumber(value_backgroundPrimary_1)
        }
        else if (RuntimeType.STRING == value_backgroundPrimary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_backgroundPrimary_2  = value_backgroundPrimary as string
            valueSerializer.writeString(value_backgroundPrimary_2)
        }
        else if (RuntimeType.OBJECT == value_backgroundPrimary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_backgroundPrimary_3  = value_backgroundPrimary as Resource
            Resource_serializer.write(valueSerializer, value_backgroundPrimary_3)
        }
        const value_backgroundSecondary  = value.backgroundSecondary
        let value_backgroundSecondary_type : int32 = RuntimeType.UNDEFINED
        value_backgroundSecondary_type = runtimeType(value_backgroundSecondary)
        if (TypeChecker.isColor(value_backgroundSecondary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_backgroundSecondary_0  = value_backgroundSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundSecondary_0))
        }
        else if (RuntimeType.NUMBER == value_backgroundSecondary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_backgroundSecondary_1  = value_backgroundSecondary as number
            valueSerializer.writeNumber(value_backgroundSecondary_1)
        }
        else if (RuntimeType.STRING == value_backgroundSecondary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_backgroundSecondary_2  = value_backgroundSecondary as string
            valueSerializer.writeString(value_backgroundSecondary_2)
        }
        else if (RuntimeType.OBJECT == value_backgroundSecondary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_backgroundSecondary_3  = value_backgroundSecondary as Resource
            Resource_serializer.write(valueSerializer, value_backgroundSecondary_3)
        }
        const value_backgroundTertiary  = value.backgroundTertiary
        let value_backgroundTertiary_type : int32 = RuntimeType.UNDEFINED
        value_backgroundTertiary_type = runtimeType(value_backgroundTertiary)
        if (TypeChecker.isColor(value_backgroundTertiary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_backgroundTertiary_0  = value_backgroundTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundTertiary_0))
        }
        else if (RuntimeType.NUMBER == value_backgroundTertiary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_backgroundTertiary_1  = value_backgroundTertiary as number
            valueSerializer.writeNumber(value_backgroundTertiary_1)
        }
        else if (RuntimeType.STRING == value_backgroundTertiary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_backgroundTertiary_2  = value_backgroundTertiary as string
            valueSerializer.writeString(value_backgroundTertiary_2)
        }
        else if (RuntimeType.OBJECT == value_backgroundTertiary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_backgroundTertiary_3  = value_backgroundTertiary as Resource
            Resource_serializer.write(valueSerializer, value_backgroundTertiary_3)
        }
        const value_backgroundFourth  = value.backgroundFourth
        let value_backgroundFourth_type : int32 = RuntimeType.UNDEFINED
        value_backgroundFourth_type = runtimeType(value_backgroundFourth)
        if (TypeChecker.isColor(value_backgroundFourth)) {
            valueSerializer.writeInt8((0).toChar())
            const value_backgroundFourth_0  = value_backgroundFourth as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundFourth_0))
        }
        else if (RuntimeType.NUMBER == value_backgroundFourth_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_backgroundFourth_1  = value_backgroundFourth as number
            valueSerializer.writeNumber(value_backgroundFourth_1)
        }
        else if (RuntimeType.STRING == value_backgroundFourth_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_backgroundFourth_2  = value_backgroundFourth as string
            valueSerializer.writeString(value_backgroundFourth_2)
        }
        else if (RuntimeType.OBJECT == value_backgroundFourth_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_backgroundFourth_3  = value_backgroundFourth as Resource
            Resource_serializer.write(valueSerializer, value_backgroundFourth_3)
        }
        const value_backgroundEmphasize  = value.backgroundEmphasize
        let value_backgroundEmphasize_type : int32 = RuntimeType.UNDEFINED
        value_backgroundEmphasize_type = runtimeType(value_backgroundEmphasize)
        if (TypeChecker.isColor(value_backgroundEmphasize)) {
            valueSerializer.writeInt8((0).toChar())
            const value_backgroundEmphasize_0  = value_backgroundEmphasize as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundEmphasize_0))
        }
        else if (RuntimeType.NUMBER == value_backgroundEmphasize_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_backgroundEmphasize_1  = value_backgroundEmphasize as number
            valueSerializer.writeNumber(value_backgroundEmphasize_1)
        }
        else if (RuntimeType.STRING == value_backgroundEmphasize_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_backgroundEmphasize_2  = value_backgroundEmphasize as string
            valueSerializer.writeString(value_backgroundEmphasize_2)
        }
        else if (RuntimeType.OBJECT == value_backgroundEmphasize_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_backgroundEmphasize_3  = value_backgroundEmphasize as Resource
            Resource_serializer.write(valueSerializer, value_backgroundEmphasize_3)
        }
        const value_compForegroundPrimary  = value.compForegroundPrimary
        let value_compForegroundPrimary_type : int32 = RuntimeType.UNDEFINED
        value_compForegroundPrimary_type = runtimeType(value_compForegroundPrimary)
        if (TypeChecker.isColor(value_compForegroundPrimary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compForegroundPrimary_0  = value_compForegroundPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compForegroundPrimary_0))
        }
        else if (RuntimeType.NUMBER == value_compForegroundPrimary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compForegroundPrimary_1  = value_compForegroundPrimary as number
            valueSerializer.writeNumber(value_compForegroundPrimary_1)
        }
        else if (RuntimeType.STRING == value_compForegroundPrimary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compForegroundPrimary_2  = value_compForegroundPrimary as string
            valueSerializer.writeString(value_compForegroundPrimary_2)
        }
        else if (RuntimeType.OBJECT == value_compForegroundPrimary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compForegroundPrimary_3  = value_compForegroundPrimary as Resource
            Resource_serializer.write(valueSerializer, value_compForegroundPrimary_3)
        }
        const value_compBackgroundPrimary  = value.compBackgroundPrimary
        let value_compBackgroundPrimary_type : int32 = RuntimeType.UNDEFINED
        value_compBackgroundPrimary_type = runtimeType(value_compBackgroundPrimary)
        if (TypeChecker.isColor(value_compBackgroundPrimary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compBackgroundPrimary_0  = value_compBackgroundPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compBackgroundPrimary_0))
        }
        else if (RuntimeType.NUMBER == value_compBackgroundPrimary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compBackgroundPrimary_1  = value_compBackgroundPrimary as number
            valueSerializer.writeNumber(value_compBackgroundPrimary_1)
        }
        else if (RuntimeType.STRING == value_compBackgroundPrimary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compBackgroundPrimary_2  = value_compBackgroundPrimary as string
            valueSerializer.writeString(value_compBackgroundPrimary_2)
        }
        else if (RuntimeType.OBJECT == value_compBackgroundPrimary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compBackgroundPrimary_3  = value_compBackgroundPrimary as Resource
            Resource_serializer.write(valueSerializer, value_compBackgroundPrimary_3)
        }
        const value_compBackgroundPrimaryTran  = value.compBackgroundPrimaryTran
        let value_compBackgroundPrimaryTran_type : int32 = RuntimeType.UNDEFINED
        value_compBackgroundPrimaryTran_type = runtimeType(value_compBackgroundPrimaryTran)
        if (TypeChecker.isColor(value_compBackgroundPrimaryTran)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compBackgroundPrimaryTran_0  = value_compBackgroundPrimaryTran as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compBackgroundPrimaryTran_0))
        }
        else if (RuntimeType.NUMBER == value_compBackgroundPrimaryTran_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compBackgroundPrimaryTran_1  = value_compBackgroundPrimaryTran as number
            valueSerializer.writeNumber(value_compBackgroundPrimaryTran_1)
        }
        else if (RuntimeType.STRING == value_compBackgroundPrimaryTran_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compBackgroundPrimaryTran_2  = value_compBackgroundPrimaryTran as string
            valueSerializer.writeString(value_compBackgroundPrimaryTran_2)
        }
        else if (RuntimeType.OBJECT == value_compBackgroundPrimaryTran_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compBackgroundPrimaryTran_3  = value_compBackgroundPrimaryTran as Resource
            Resource_serializer.write(valueSerializer, value_compBackgroundPrimaryTran_3)
        }
        const value_compBackgroundPrimaryContrary  = value.compBackgroundPrimaryContrary
        let value_compBackgroundPrimaryContrary_type : int32 = RuntimeType.UNDEFINED
        value_compBackgroundPrimaryContrary_type = runtimeType(value_compBackgroundPrimaryContrary)
        if (TypeChecker.isColor(value_compBackgroundPrimaryContrary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compBackgroundPrimaryContrary_0  = value_compBackgroundPrimaryContrary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compBackgroundPrimaryContrary_0))
        }
        else if (RuntimeType.NUMBER == value_compBackgroundPrimaryContrary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compBackgroundPrimaryContrary_1  = value_compBackgroundPrimaryContrary as number
            valueSerializer.writeNumber(value_compBackgroundPrimaryContrary_1)
        }
        else if (RuntimeType.STRING == value_compBackgroundPrimaryContrary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compBackgroundPrimaryContrary_2  = value_compBackgroundPrimaryContrary as string
            valueSerializer.writeString(value_compBackgroundPrimaryContrary_2)
        }
        else if (RuntimeType.OBJECT == value_compBackgroundPrimaryContrary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compBackgroundPrimaryContrary_3  = value_compBackgroundPrimaryContrary as Resource
            Resource_serializer.write(valueSerializer, value_compBackgroundPrimaryContrary_3)
        }
        const value_compBackgroundGray  = value.compBackgroundGray
        let value_compBackgroundGray_type : int32 = RuntimeType.UNDEFINED
        value_compBackgroundGray_type = runtimeType(value_compBackgroundGray)
        if (TypeChecker.isColor(value_compBackgroundGray)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compBackgroundGray_0  = value_compBackgroundGray as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compBackgroundGray_0))
        }
        else if (RuntimeType.NUMBER == value_compBackgroundGray_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compBackgroundGray_1  = value_compBackgroundGray as number
            valueSerializer.writeNumber(value_compBackgroundGray_1)
        }
        else if (RuntimeType.STRING == value_compBackgroundGray_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compBackgroundGray_2  = value_compBackgroundGray as string
            valueSerializer.writeString(value_compBackgroundGray_2)
        }
        else if (RuntimeType.OBJECT == value_compBackgroundGray_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compBackgroundGray_3  = value_compBackgroundGray as Resource
            Resource_serializer.write(valueSerializer, value_compBackgroundGray_3)
        }
        const value_compBackgroundSecondary  = value.compBackgroundSecondary
        let value_compBackgroundSecondary_type : int32 = RuntimeType.UNDEFINED
        value_compBackgroundSecondary_type = runtimeType(value_compBackgroundSecondary)
        if (TypeChecker.isColor(value_compBackgroundSecondary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compBackgroundSecondary_0  = value_compBackgroundSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compBackgroundSecondary_0))
        }
        else if (RuntimeType.NUMBER == value_compBackgroundSecondary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compBackgroundSecondary_1  = value_compBackgroundSecondary as number
            valueSerializer.writeNumber(value_compBackgroundSecondary_1)
        }
        else if (RuntimeType.STRING == value_compBackgroundSecondary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compBackgroundSecondary_2  = value_compBackgroundSecondary as string
            valueSerializer.writeString(value_compBackgroundSecondary_2)
        }
        else if (RuntimeType.OBJECT == value_compBackgroundSecondary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compBackgroundSecondary_3  = value_compBackgroundSecondary as Resource
            Resource_serializer.write(valueSerializer, value_compBackgroundSecondary_3)
        }
        const value_compBackgroundTertiary  = value.compBackgroundTertiary
        let value_compBackgroundTertiary_type : int32 = RuntimeType.UNDEFINED
        value_compBackgroundTertiary_type = runtimeType(value_compBackgroundTertiary)
        if (TypeChecker.isColor(value_compBackgroundTertiary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compBackgroundTertiary_0  = value_compBackgroundTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compBackgroundTertiary_0))
        }
        else if (RuntimeType.NUMBER == value_compBackgroundTertiary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compBackgroundTertiary_1  = value_compBackgroundTertiary as number
            valueSerializer.writeNumber(value_compBackgroundTertiary_1)
        }
        else if (RuntimeType.STRING == value_compBackgroundTertiary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compBackgroundTertiary_2  = value_compBackgroundTertiary as string
            valueSerializer.writeString(value_compBackgroundTertiary_2)
        }
        else if (RuntimeType.OBJECT == value_compBackgroundTertiary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compBackgroundTertiary_3  = value_compBackgroundTertiary as Resource
            Resource_serializer.write(valueSerializer, value_compBackgroundTertiary_3)
        }
        const value_compBackgroundEmphasize  = value.compBackgroundEmphasize
        let value_compBackgroundEmphasize_type : int32 = RuntimeType.UNDEFINED
        value_compBackgroundEmphasize_type = runtimeType(value_compBackgroundEmphasize)
        if (TypeChecker.isColor(value_compBackgroundEmphasize)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compBackgroundEmphasize_0  = value_compBackgroundEmphasize as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compBackgroundEmphasize_0))
        }
        else if (RuntimeType.NUMBER == value_compBackgroundEmphasize_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compBackgroundEmphasize_1  = value_compBackgroundEmphasize as number
            valueSerializer.writeNumber(value_compBackgroundEmphasize_1)
        }
        else if (RuntimeType.STRING == value_compBackgroundEmphasize_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compBackgroundEmphasize_2  = value_compBackgroundEmphasize as string
            valueSerializer.writeString(value_compBackgroundEmphasize_2)
        }
        else if (RuntimeType.OBJECT == value_compBackgroundEmphasize_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compBackgroundEmphasize_3  = value_compBackgroundEmphasize as Resource
            Resource_serializer.write(valueSerializer, value_compBackgroundEmphasize_3)
        }
        const value_compBackgroundNeutral  = value.compBackgroundNeutral
        let value_compBackgroundNeutral_type : int32 = RuntimeType.UNDEFINED
        value_compBackgroundNeutral_type = runtimeType(value_compBackgroundNeutral)
        if (TypeChecker.isColor(value_compBackgroundNeutral)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compBackgroundNeutral_0  = value_compBackgroundNeutral as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compBackgroundNeutral_0))
        }
        else if (RuntimeType.NUMBER == value_compBackgroundNeutral_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compBackgroundNeutral_1  = value_compBackgroundNeutral as number
            valueSerializer.writeNumber(value_compBackgroundNeutral_1)
        }
        else if (RuntimeType.STRING == value_compBackgroundNeutral_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compBackgroundNeutral_2  = value_compBackgroundNeutral as string
            valueSerializer.writeString(value_compBackgroundNeutral_2)
        }
        else if (RuntimeType.OBJECT == value_compBackgroundNeutral_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compBackgroundNeutral_3  = value_compBackgroundNeutral as Resource
            Resource_serializer.write(valueSerializer, value_compBackgroundNeutral_3)
        }
        const value_compEmphasizeSecondary  = value.compEmphasizeSecondary
        let value_compEmphasizeSecondary_type : int32 = RuntimeType.UNDEFINED
        value_compEmphasizeSecondary_type = runtimeType(value_compEmphasizeSecondary)
        if (TypeChecker.isColor(value_compEmphasizeSecondary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compEmphasizeSecondary_0  = value_compEmphasizeSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compEmphasizeSecondary_0))
        }
        else if (RuntimeType.NUMBER == value_compEmphasizeSecondary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compEmphasizeSecondary_1  = value_compEmphasizeSecondary as number
            valueSerializer.writeNumber(value_compEmphasizeSecondary_1)
        }
        else if (RuntimeType.STRING == value_compEmphasizeSecondary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compEmphasizeSecondary_2  = value_compEmphasizeSecondary as string
            valueSerializer.writeString(value_compEmphasizeSecondary_2)
        }
        else if (RuntimeType.OBJECT == value_compEmphasizeSecondary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compEmphasizeSecondary_3  = value_compEmphasizeSecondary as Resource
            Resource_serializer.write(valueSerializer, value_compEmphasizeSecondary_3)
        }
        const value_compEmphasizeTertiary  = value.compEmphasizeTertiary
        let value_compEmphasizeTertiary_type : int32 = RuntimeType.UNDEFINED
        value_compEmphasizeTertiary_type = runtimeType(value_compEmphasizeTertiary)
        if (TypeChecker.isColor(value_compEmphasizeTertiary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compEmphasizeTertiary_0  = value_compEmphasizeTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compEmphasizeTertiary_0))
        }
        else if (RuntimeType.NUMBER == value_compEmphasizeTertiary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compEmphasizeTertiary_1  = value_compEmphasizeTertiary as number
            valueSerializer.writeNumber(value_compEmphasizeTertiary_1)
        }
        else if (RuntimeType.STRING == value_compEmphasizeTertiary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compEmphasizeTertiary_2  = value_compEmphasizeTertiary as string
            valueSerializer.writeString(value_compEmphasizeTertiary_2)
        }
        else if (RuntimeType.OBJECT == value_compEmphasizeTertiary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compEmphasizeTertiary_3  = value_compEmphasizeTertiary as Resource
            Resource_serializer.write(valueSerializer, value_compEmphasizeTertiary_3)
        }
        const value_compDivider  = value.compDivider
        let value_compDivider_type : int32 = RuntimeType.UNDEFINED
        value_compDivider_type = runtimeType(value_compDivider)
        if (TypeChecker.isColor(value_compDivider)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compDivider_0  = value_compDivider as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compDivider_0))
        }
        else if (RuntimeType.NUMBER == value_compDivider_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compDivider_1  = value_compDivider as number
            valueSerializer.writeNumber(value_compDivider_1)
        }
        else if (RuntimeType.STRING == value_compDivider_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compDivider_2  = value_compDivider as string
            valueSerializer.writeString(value_compDivider_2)
        }
        else if (RuntimeType.OBJECT == value_compDivider_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compDivider_3  = value_compDivider as Resource
            Resource_serializer.write(valueSerializer, value_compDivider_3)
        }
        const value_compCommonContrary  = value.compCommonContrary
        let value_compCommonContrary_type : int32 = RuntimeType.UNDEFINED
        value_compCommonContrary_type = runtimeType(value_compCommonContrary)
        if (TypeChecker.isColor(value_compCommonContrary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compCommonContrary_0  = value_compCommonContrary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compCommonContrary_0))
        }
        else if (RuntimeType.NUMBER == value_compCommonContrary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compCommonContrary_1  = value_compCommonContrary as number
            valueSerializer.writeNumber(value_compCommonContrary_1)
        }
        else if (RuntimeType.STRING == value_compCommonContrary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compCommonContrary_2  = value_compCommonContrary as string
            valueSerializer.writeString(value_compCommonContrary_2)
        }
        else if (RuntimeType.OBJECT == value_compCommonContrary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compCommonContrary_3  = value_compCommonContrary as Resource
            Resource_serializer.write(valueSerializer, value_compCommonContrary_3)
        }
        const value_compBackgroundFocus  = value.compBackgroundFocus
        let value_compBackgroundFocus_type : int32 = RuntimeType.UNDEFINED
        value_compBackgroundFocus_type = runtimeType(value_compBackgroundFocus)
        if (TypeChecker.isColor(value_compBackgroundFocus)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compBackgroundFocus_0  = value_compBackgroundFocus as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compBackgroundFocus_0))
        }
        else if (RuntimeType.NUMBER == value_compBackgroundFocus_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compBackgroundFocus_1  = value_compBackgroundFocus as number
            valueSerializer.writeNumber(value_compBackgroundFocus_1)
        }
        else if (RuntimeType.STRING == value_compBackgroundFocus_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compBackgroundFocus_2  = value_compBackgroundFocus as string
            valueSerializer.writeString(value_compBackgroundFocus_2)
        }
        else if (RuntimeType.OBJECT == value_compBackgroundFocus_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compBackgroundFocus_3  = value_compBackgroundFocus as Resource
            Resource_serializer.write(valueSerializer, value_compBackgroundFocus_3)
        }
        const value_compFocusedPrimary  = value.compFocusedPrimary
        let value_compFocusedPrimary_type : int32 = RuntimeType.UNDEFINED
        value_compFocusedPrimary_type = runtimeType(value_compFocusedPrimary)
        if (TypeChecker.isColor(value_compFocusedPrimary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compFocusedPrimary_0  = value_compFocusedPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compFocusedPrimary_0))
        }
        else if (RuntimeType.NUMBER == value_compFocusedPrimary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compFocusedPrimary_1  = value_compFocusedPrimary as number
            valueSerializer.writeNumber(value_compFocusedPrimary_1)
        }
        else if (RuntimeType.STRING == value_compFocusedPrimary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compFocusedPrimary_2  = value_compFocusedPrimary as string
            valueSerializer.writeString(value_compFocusedPrimary_2)
        }
        else if (RuntimeType.OBJECT == value_compFocusedPrimary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compFocusedPrimary_3  = value_compFocusedPrimary as Resource
            Resource_serializer.write(valueSerializer, value_compFocusedPrimary_3)
        }
        const value_compFocusedSecondary  = value.compFocusedSecondary
        let value_compFocusedSecondary_type : int32 = RuntimeType.UNDEFINED
        value_compFocusedSecondary_type = runtimeType(value_compFocusedSecondary)
        if (TypeChecker.isColor(value_compFocusedSecondary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compFocusedSecondary_0  = value_compFocusedSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compFocusedSecondary_0))
        }
        else if (RuntimeType.NUMBER == value_compFocusedSecondary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compFocusedSecondary_1  = value_compFocusedSecondary as number
            valueSerializer.writeNumber(value_compFocusedSecondary_1)
        }
        else if (RuntimeType.STRING == value_compFocusedSecondary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compFocusedSecondary_2  = value_compFocusedSecondary as string
            valueSerializer.writeString(value_compFocusedSecondary_2)
        }
        else if (RuntimeType.OBJECT == value_compFocusedSecondary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compFocusedSecondary_3  = value_compFocusedSecondary as Resource
            Resource_serializer.write(valueSerializer, value_compFocusedSecondary_3)
        }
        const value_compFocusedTertiary  = value.compFocusedTertiary
        let value_compFocusedTertiary_type : int32 = RuntimeType.UNDEFINED
        value_compFocusedTertiary_type = runtimeType(value_compFocusedTertiary)
        if (TypeChecker.isColor(value_compFocusedTertiary)) {
            valueSerializer.writeInt8((0).toChar())
            const value_compFocusedTertiary_0  = value_compFocusedTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_compFocusedTertiary_0))
        }
        else if (RuntimeType.NUMBER == value_compFocusedTertiary_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_compFocusedTertiary_1  = value_compFocusedTertiary as number
            valueSerializer.writeNumber(value_compFocusedTertiary_1)
        }
        else if (RuntimeType.STRING == value_compFocusedTertiary_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_compFocusedTertiary_2  = value_compFocusedTertiary as string
            valueSerializer.writeString(value_compFocusedTertiary_2)
        }
        else if (RuntimeType.OBJECT == value_compFocusedTertiary_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_compFocusedTertiary_3  = value_compFocusedTertiary as Resource
            Resource_serializer.write(valueSerializer, value_compFocusedTertiary_3)
        }
        const value_interactiveHover  = value.interactiveHover
        let value_interactiveHover_type : int32 = RuntimeType.UNDEFINED
        value_interactiveHover_type = runtimeType(value_interactiveHover)
        if (TypeChecker.isColor(value_interactiveHover)) {
            valueSerializer.writeInt8((0).toChar())
            const value_interactiveHover_0  = value_interactiveHover as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_interactiveHover_0))
        }
        else if (RuntimeType.NUMBER == value_interactiveHover_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_interactiveHover_1  = value_interactiveHover as number
            valueSerializer.writeNumber(value_interactiveHover_1)
        }
        else if (RuntimeType.STRING == value_interactiveHover_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_interactiveHover_2  = value_interactiveHover as string
            valueSerializer.writeString(value_interactiveHover_2)
        }
        else if (RuntimeType.OBJECT == value_interactiveHover_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_interactiveHover_3  = value_interactiveHover as Resource
            Resource_serializer.write(valueSerializer, value_interactiveHover_3)
        }
        const value_interactivePressed  = value.interactivePressed
        let value_interactivePressed_type : int32 = RuntimeType.UNDEFINED
        value_interactivePressed_type = runtimeType(value_interactivePressed)
        if (TypeChecker.isColor(value_interactivePressed)) {
            valueSerializer.writeInt8((0).toChar())
            const value_interactivePressed_0  = value_interactivePressed as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_interactivePressed_0))
        }
        else if (RuntimeType.NUMBER == value_interactivePressed_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_interactivePressed_1  = value_interactivePressed as number
            valueSerializer.writeNumber(value_interactivePressed_1)
        }
        else if (RuntimeType.STRING == value_interactivePressed_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_interactivePressed_2  = value_interactivePressed as string
            valueSerializer.writeString(value_interactivePressed_2)
        }
        else if (RuntimeType.OBJECT == value_interactivePressed_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_interactivePressed_3  = value_interactivePressed as Resource
            Resource_serializer.write(valueSerializer, value_interactivePressed_3)
        }
        const value_interactiveFocus  = value.interactiveFocus
        let value_interactiveFocus_type : int32 = RuntimeType.UNDEFINED
        value_interactiveFocus_type = runtimeType(value_interactiveFocus)
        if (TypeChecker.isColor(value_interactiveFocus)) {
            valueSerializer.writeInt8((0).toChar())
            const value_interactiveFocus_0  = value_interactiveFocus as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_interactiveFocus_0))
        }
        else if (RuntimeType.NUMBER == value_interactiveFocus_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_interactiveFocus_1  = value_interactiveFocus as number
            valueSerializer.writeNumber(value_interactiveFocus_1)
        }
        else if (RuntimeType.STRING == value_interactiveFocus_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_interactiveFocus_2  = value_interactiveFocus as string
            valueSerializer.writeString(value_interactiveFocus_2)
        }
        else if (RuntimeType.OBJECT == value_interactiveFocus_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_interactiveFocus_3  = value_interactiveFocus as Resource
            Resource_serializer.write(valueSerializer, value_interactiveFocus_3)
        }
        const value_interactiveActive  = value.interactiveActive
        let value_interactiveActive_type : int32 = RuntimeType.UNDEFINED
        value_interactiveActive_type = runtimeType(value_interactiveActive)
        if (TypeChecker.isColor(value_interactiveActive)) {
            valueSerializer.writeInt8((0).toChar())
            const value_interactiveActive_0  = value_interactiveActive as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_interactiveActive_0))
        }
        else if (RuntimeType.NUMBER == value_interactiveActive_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_interactiveActive_1  = value_interactiveActive as number
            valueSerializer.writeNumber(value_interactiveActive_1)
        }
        else if (RuntimeType.STRING == value_interactiveActive_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_interactiveActive_2  = value_interactiveActive as string
            valueSerializer.writeString(value_interactiveActive_2)
        }
        else if (RuntimeType.OBJECT == value_interactiveActive_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_interactiveActive_3  = value_interactiveActive as Resource
            Resource_serializer.write(valueSerializer, value_interactiveActive_3)
        }
        const value_interactiveSelect  = value.interactiveSelect
        let value_interactiveSelect_type : int32 = RuntimeType.UNDEFINED
        value_interactiveSelect_type = runtimeType(value_interactiveSelect)
        if (TypeChecker.isColor(value_interactiveSelect)) {
            valueSerializer.writeInt8((0).toChar())
            const value_interactiveSelect_0  = value_interactiveSelect as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_interactiveSelect_0))
        }
        else if (RuntimeType.NUMBER == value_interactiveSelect_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_interactiveSelect_1  = value_interactiveSelect as number
            valueSerializer.writeNumber(value_interactiveSelect_1)
        }
        else if (RuntimeType.STRING == value_interactiveSelect_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_interactiveSelect_2  = value_interactiveSelect as string
            valueSerializer.writeString(value_interactiveSelect_2)
        }
        else if (RuntimeType.OBJECT == value_interactiveSelect_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_interactiveSelect_3  = value_interactiveSelect as Resource
            Resource_serializer.write(valueSerializer, value_interactiveSelect_3)
        }
        const value_interactiveClick  = value.interactiveClick
        let value_interactiveClick_type : int32 = RuntimeType.UNDEFINED
        value_interactiveClick_type = runtimeType(value_interactiveClick)
        if (TypeChecker.isColor(value_interactiveClick)) {
            valueSerializer.writeInt8((0).toChar())
            const value_interactiveClick_0  = value_interactiveClick as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_interactiveClick_0))
        }
        else if (RuntimeType.NUMBER == value_interactiveClick_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_interactiveClick_1  = value_interactiveClick as number
            valueSerializer.writeNumber(value_interactiveClick_1)
        }
        else if (RuntimeType.STRING == value_interactiveClick_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_interactiveClick_2  = value_interactiveClick as string
            valueSerializer.writeString(value_interactiveClick_2)
        }
        else if (RuntimeType.OBJECT == value_interactiveClick_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_interactiveClick_3  = value_interactiveClick as Resource
            Resource_serializer.write(valueSerializer, value_interactiveClick_3)
        }
    }
    public static read(buffer: DeserializerBase): Colors {
        let valueDeserializer : DeserializerBase = buffer
        const brand_buf_selector : int32 = valueDeserializer.readInt8()
        let brand_buf : Color | number | string | Resource | undefined
        if (brand_buf_selector == (0).toChar()) {
            brand_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (brand_buf_selector == (1).toChar()) {
            brand_buf = (valueDeserializer.readNumber() as number)
        }
        else if (brand_buf_selector == (2).toChar()) {
            brand_buf = (valueDeserializer.readString() as string)
        }
        else if (brand_buf_selector == (3).toChar()) {
            brand_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for brand_buf has to be chosen through deserialisation.")
        }
        const brand_result : ResourceColor = (brand_buf as Color | number | string | Resource)
        const warning_buf_selector : int32 = valueDeserializer.readInt8()
        let warning_buf : Color | number | string | Resource | undefined
        if (warning_buf_selector == (0).toChar()) {
            warning_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (warning_buf_selector == (1).toChar()) {
            warning_buf = (valueDeserializer.readNumber() as number)
        }
        else if (warning_buf_selector == (2).toChar()) {
            warning_buf = (valueDeserializer.readString() as string)
        }
        else if (warning_buf_selector == (3).toChar()) {
            warning_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for warning_buf has to be chosen through deserialisation.")
        }
        const warning_result : ResourceColor = (warning_buf as Color | number | string | Resource)
        const alert_buf_selector : int32 = valueDeserializer.readInt8()
        let alert_buf : Color | number | string | Resource | undefined
        if (alert_buf_selector == (0).toChar()) {
            alert_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (alert_buf_selector == (1).toChar()) {
            alert_buf = (valueDeserializer.readNumber() as number)
        }
        else if (alert_buf_selector == (2).toChar()) {
            alert_buf = (valueDeserializer.readString() as string)
        }
        else if (alert_buf_selector == (3).toChar()) {
            alert_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for alert_buf has to be chosen through deserialisation.")
        }
        const alert_result : ResourceColor = (alert_buf as Color | number | string | Resource)
        const confirm_buf_selector : int32 = valueDeserializer.readInt8()
        let confirm_buf : Color | number | string | Resource | undefined
        if (confirm_buf_selector == (0).toChar()) {
            confirm_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (confirm_buf_selector == (1).toChar()) {
            confirm_buf = (valueDeserializer.readNumber() as number)
        }
        else if (confirm_buf_selector == (2).toChar()) {
            confirm_buf = (valueDeserializer.readString() as string)
        }
        else if (confirm_buf_selector == (3).toChar()) {
            confirm_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for confirm_buf has to be chosen through deserialisation.")
        }
        const confirm_result : ResourceColor = (confirm_buf as Color | number | string | Resource)
        const fontPrimary_buf_selector : int32 = valueDeserializer.readInt8()
        let fontPrimary_buf : Color | number | string | Resource | undefined
        if (fontPrimary_buf_selector == (0).toChar()) {
            fontPrimary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (fontPrimary_buf_selector == (1).toChar()) {
            fontPrimary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (fontPrimary_buf_selector == (2).toChar()) {
            fontPrimary_buf = (valueDeserializer.readString() as string)
        }
        else if (fontPrimary_buf_selector == (3).toChar()) {
            fontPrimary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for fontPrimary_buf has to be chosen through deserialisation.")
        }
        const fontPrimary_result : ResourceColor = (fontPrimary_buf as Color | number | string | Resource)
        const fontSecondary_buf_selector : int32 = valueDeserializer.readInt8()
        let fontSecondary_buf : Color | number | string | Resource | undefined
        if (fontSecondary_buf_selector == (0).toChar()) {
            fontSecondary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (fontSecondary_buf_selector == (1).toChar()) {
            fontSecondary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (fontSecondary_buf_selector == (2).toChar()) {
            fontSecondary_buf = (valueDeserializer.readString() as string)
        }
        else if (fontSecondary_buf_selector == (3).toChar()) {
            fontSecondary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for fontSecondary_buf has to be chosen through deserialisation.")
        }
        const fontSecondary_result : ResourceColor = (fontSecondary_buf as Color | number | string | Resource)
        const fontTertiary_buf_selector : int32 = valueDeserializer.readInt8()
        let fontTertiary_buf : Color | number | string | Resource | undefined
        if (fontTertiary_buf_selector == (0).toChar()) {
            fontTertiary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (fontTertiary_buf_selector == (1).toChar()) {
            fontTertiary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (fontTertiary_buf_selector == (2).toChar()) {
            fontTertiary_buf = (valueDeserializer.readString() as string)
        }
        else if (fontTertiary_buf_selector == (3).toChar()) {
            fontTertiary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for fontTertiary_buf has to be chosen through deserialisation.")
        }
        const fontTertiary_result : ResourceColor = (fontTertiary_buf as Color | number | string | Resource)
        const fontFourth_buf_selector : int32 = valueDeserializer.readInt8()
        let fontFourth_buf : Color | number | string | Resource | undefined
        if (fontFourth_buf_selector == (0).toChar()) {
            fontFourth_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (fontFourth_buf_selector == (1).toChar()) {
            fontFourth_buf = (valueDeserializer.readNumber() as number)
        }
        else if (fontFourth_buf_selector == (2).toChar()) {
            fontFourth_buf = (valueDeserializer.readString() as string)
        }
        else if (fontFourth_buf_selector == (3).toChar()) {
            fontFourth_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for fontFourth_buf has to be chosen through deserialisation.")
        }
        const fontFourth_result : ResourceColor = (fontFourth_buf as Color | number | string | Resource)
        const fontEmphasize_buf_selector : int32 = valueDeserializer.readInt8()
        let fontEmphasize_buf : Color | number | string | Resource | undefined
        if (fontEmphasize_buf_selector == (0).toChar()) {
            fontEmphasize_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (fontEmphasize_buf_selector == (1).toChar()) {
            fontEmphasize_buf = (valueDeserializer.readNumber() as number)
        }
        else if (fontEmphasize_buf_selector == (2).toChar()) {
            fontEmphasize_buf = (valueDeserializer.readString() as string)
        }
        else if (fontEmphasize_buf_selector == (3).toChar()) {
            fontEmphasize_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for fontEmphasize_buf has to be chosen through deserialisation.")
        }
        const fontEmphasize_result : ResourceColor = (fontEmphasize_buf as Color | number | string | Resource)
        const fontOnPrimary_buf_selector : int32 = valueDeserializer.readInt8()
        let fontOnPrimary_buf : Color | number | string | Resource | undefined
        if (fontOnPrimary_buf_selector == (0).toChar()) {
            fontOnPrimary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (fontOnPrimary_buf_selector == (1).toChar()) {
            fontOnPrimary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (fontOnPrimary_buf_selector == (2).toChar()) {
            fontOnPrimary_buf = (valueDeserializer.readString() as string)
        }
        else if (fontOnPrimary_buf_selector == (3).toChar()) {
            fontOnPrimary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for fontOnPrimary_buf has to be chosen through deserialisation.")
        }
        const fontOnPrimary_result : ResourceColor = (fontOnPrimary_buf as Color | number | string | Resource)
        const fontOnSecondary_buf_selector : int32 = valueDeserializer.readInt8()
        let fontOnSecondary_buf : Color | number | string | Resource | undefined
        if (fontOnSecondary_buf_selector == (0).toChar()) {
            fontOnSecondary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (fontOnSecondary_buf_selector == (1).toChar()) {
            fontOnSecondary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (fontOnSecondary_buf_selector == (2).toChar()) {
            fontOnSecondary_buf = (valueDeserializer.readString() as string)
        }
        else if (fontOnSecondary_buf_selector == (3).toChar()) {
            fontOnSecondary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for fontOnSecondary_buf has to be chosen through deserialisation.")
        }
        const fontOnSecondary_result : ResourceColor = (fontOnSecondary_buf as Color | number | string | Resource)
        const fontOnTertiary_buf_selector : int32 = valueDeserializer.readInt8()
        let fontOnTertiary_buf : Color | number | string | Resource | undefined
        if (fontOnTertiary_buf_selector == (0).toChar()) {
            fontOnTertiary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (fontOnTertiary_buf_selector == (1).toChar()) {
            fontOnTertiary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (fontOnTertiary_buf_selector == (2).toChar()) {
            fontOnTertiary_buf = (valueDeserializer.readString() as string)
        }
        else if (fontOnTertiary_buf_selector == (3).toChar()) {
            fontOnTertiary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for fontOnTertiary_buf has to be chosen through deserialisation.")
        }
        const fontOnTertiary_result : ResourceColor = (fontOnTertiary_buf as Color | number | string | Resource)
        const fontOnFourth_buf_selector : int32 = valueDeserializer.readInt8()
        let fontOnFourth_buf : Color | number | string | Resource | undefined
        if (fontOnFourth_buf_selector == (0).toChar()) {
            fontOnFourth_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (fontOnFourth_buf_selector == (1).toChar()) {
            fontOnFourth_buf = (valueDeserializer.readNumber() as number)
        }
        else if (fontOnFourth_buf_selector == (2).toChar()) {
            fontOnFourth_buf = (valueDeserializer.readString() as string)
        }
        else if (fontOnFourth_buf_selector == (3).toChar()) {
            fontOnFourth_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for fontOnFourth_buf has to be chosen through deserialisation.")
        }
        const fontOnFourth_result : ResourceColor = (fontOnFourth_buf as Color | number | string | Resource)
        const iconPrimary_buf_selector : int32 = valueDeserializer.readInt8()
        let iconPrimary_buf : Color | number | string | Resource | undefined
        if (iconPrimary_buf_selector == (0).toChar()) {
            iconPrimary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (iconPrimary_buf_selector == (1).toChar()) {
            iconPrimary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (iconPrimary_buf_selector == (2).toChar()) {
            iconPrimary_buf = (valueDeserializer.readString() as string)
        }
        else if (iconPrimary_buf_selector == (3).toChar()) {
            iconPrimary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for iconPrimary_buf has to be chosen through deserialisation.")
        }
        const iconPrimary_result : ResourceColor = (iconPrimary_buf as Color | number | string | Resource)
        const iconSecondary_buf_selector : int32 = valueDeserializer.readInt8()
        let iconSecondary_buf : Color | number | string | Resource | undefined
        if (iconSecondary_buf_selector == (0).toChar()) {
            iconSecondary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (iconSecondary_buf_selector == (1).toChar()) {
            iconSecondary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (iconSecondary_buf_selector == (2).toChar()) {
            iconSecondary_buf = (valueDeserializer.readString() as string)
        }
        else if (iconSecondary_buf_selector == (3).toChar()) {
            iconSecondary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for iconSecondary_buf has to be chosen through deserialisation.")
        }
        const iconSecondary_result : ResourceColor = (iconSecondary_buf as Color | number | string | Resource)
        const iconTertiary_buf_selector : int32 = valueDeserializer.readInt8()
        let iconTertiary_buf : Color | number | string | Resource | undefined
        if (iconTertiary_buf_selector == (0).toChar()) {
            iconTertiary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (iconTertiary_buf_selector == (1).toChar()) {
            iconTertiary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (iconTertiary_buf_selector == (2).toChar()) {
            iconTertiary_buf = (valueDeserializer.readString() as string)
        }
        else if (iconTertiary_buf_selector == (3).toChar()) {
            iconTertiary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for iconTertiary_buf has to be chosen through deserialisation.")
        }
        const iconTertiary_result : ResourceColor = (iconTertiary_buf as Color | number | string | Resource)
        const iconFourth_buf_selector : int32 = valueDeserializer.readInt8()
        let iconFourth_buf : Color | number | string | Resource | undefined
        if (iconFourth_buf_selector == (0).toChar()) {
            iconFourth_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (iconFourth_buf_selector == (1).toChar()) {
            iconFourth_buf = (valueDeserializer.readNumber() as number)
        }
        else if (iconFourth_buf_selector == (2).toChar()) {
            iconFourth_buf = (valueDeserializer.readString() as string)
        }
        else if (iconFourth_buf_selector == (3).toChar()) {
            iconFourth_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for iconFourth_buf has to be chosen through deserialisation.")
        }
        const iconFourth_result : ResourceColor = (iconFourth_buf as Color | number | string | Resource)
        const iconEmphasize_buf_selector : int32 = valueDeserializer.readInt8()
        let iconEmphasize_buf : Color | number | string | Resource | undefined
        if (iconEmphasize_buf_selector == (0).toChar()) {
            iconEmphasize_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (iconEmphasize_buf_selector == (1).toChar()) {
            iconEmphasize_buf = (valueDeserializer.readNumber() as number)
        }
        else if (iconEmphasize_buf_selector == (2).toChar()) {
            iconEmphasize_buf = (valueDeserializer.readString() as string)
        }
        else if (iconEmphasize_buf_selector == (3).toChar()) {
            iconEmphasize_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for iconEmphasize_buf has to be chosen through deserialisation.")
        }
        const iconEmphasize_result : ResourceColor = (iconEmphasize_buf as Color | number | string | Resource)
        const iconSubEmphasize_buf_selector : int32 = valueDeserializer.readInt8()
        let iconSubEmphasize_buf : Color | number | string | Resource | undefined
        if (iconSubEmphasize_buf_selector == (0).toChar()) {
            iconSubEmphasize_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (iconSubEmphasize_buf_selector == (1).toChar()) {
            iconSubEmphasize_buf = (valueDeserializer.readNumber() as number)
        }
        else if (iconSubEmphasize_buf_selector == (2).toChar()) {
            iconSubEmphasize_buf = (valueDeserializer.readString() as string)
        }
        else if (iconSubEmphasize_buf_selector == (3).toChar()) {
            iconSubEmphasize_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for iconSubEmphasize_buf has to be chosen through deserialisation.")
        }
        const iconSubEmphasize_result : ResourceColor = (iconSubEmphasize_buf as Color | number | string | Resource)
        const iconOnPrimary_buf_selector : int32 = valueDeserializer.readInt8()
        let iconOnPrimary_buf : Color | number | string | Resource | undefined
        if (iconOnPrimary_buf_selector == (0).toChar()) {
            iconOnPrimary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (iconOnPrimary_buf_selector == (1).toChar()) {
            iconOnPrimary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (iconOnPrimary_buf_selector == (2).toChar()) {
            iconOnPrimary_buf = (valueDeserializer.readString() as string)
        }
        else if (iconOnPrimary_buf_selector == (3).toChar()) {
            iconOnPrimary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for iconOnPrimary_buf has to be chosen through deserialisation.")
        }
        const iconOnPrimary_result : ResourceColor = (iconOnPrimary_buf as Color | number | string | Resource)
        const iconOnSecondary_buf_selector : int32 = valueDeserializer.readInt8()
        let iconOnSecondary_buf : Color | number | string | Resource | undefined
        if (iconOnSecondary_buf_selector == (0).toChar()) {
            iconOnSecondary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (iconOnSecondary_buf_selector == (1).toChar()) {
            iconOnSecondary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (iconOnSecondary_buf_selector == (2).toChar()) {
            iconOnSecondary_buf = (valueDeserializer.readString() as string)
        }
        else if (iconOnSecondary_buf_selector == (3).toChar()) {
            iconOnSecondary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for iconOnSecondary_buf has to be chosen through deserialisation.")
        }
        const iconOnSecondary_result : ResourceColor = (iconOnSecondary_buf as Color | number | string | Resource)
        const iconOnTertiary_buf_selector : int32 = valueDeserializer.readInt8()
        let iconOnTertiary_buf : Color | number | string | Resource | undefined
        if (iconOnTertiary_buf_selector == (0).toChar()) {
            iconOnTertiary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (iconOnTertiary_buf_selector == (1).toChar()) {
            iconOnTertiary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (iconOnTertiary_buf_selector == (2).toChar()) {
            iconOnTertiary_buf = (valueDeserializer.readString() as string)
        }
        else if (iconOnTertiary_buf_selector == (3).toChar()) {
            iconOnTertiary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for iconOnTertiary_buf has to be chosen through deserialisation.")
        }
        const iconOnTertiary_result : ResourceColor = (iconOnTertiary_buf as Color | number | string | Resource)
        const iconOnFourth_buf_selector : int32 = valueDeserializer.readInt8()
        let iconOnFourth_buf : Color | number | string | Resource | undefined
        if (iconOnFourth_buf_selector == (0).toChar()) {
            iconOnFourth_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (iconOnFourth_buf_selector == (1).toChar()) {
            iconOnFourth_buf = (valueDeserializer.readNumber() as number)
        }
        else if (iconOnFourth_buf_selector == (2).toChar()) {
            iconOnFourth_buf = (valueDeserializer.readString() as string)
        }
        else if (iconOnFourth_buf_selector == (3).toChar()) {
            iconOnFourth_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for iconOnFourth_buf has to be chosen through deserialisation.")
        }
        const iconOnFourth_result : ResourceColor = (iconOnFourth_buf as Color | number | string | Resource)
        const backgroundPrimary_buf_selector : int32 = valueDeserializer.readInt8()
        let backgroundPrimary_buf : Color | number | string | Resource | undefined
        if (backgroundPrimary_buf_selector == (0).toChar()) {
            backgroundPrimary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (backgroundPrimary_buf_selector == (1).toChar()) {
            backgroundPrimary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (backgroundPrimary_buf_selector == (2).toChar()) {
            backgroundPrimary_buf = (valueDeserializer.readString() as string)
        }
        else if (backgroundPrimary_buf_selector == (3).toChar()) {
            backgroundPrimary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for backgroundPrimary_buf has to be chosen through deserialisation.")
        }
        const backgroundPrimary_result : ResourceColor = (backgroundPrimary_buf as Color | number | string | Resource)
        const backgroundSecondary_buf_selector : int32 = valueDeserializer.readInt8()
        let backgroundSecondary_buf : Color | number | string | Resource | undefined
        if (backgroundSecondary_buf_selector == (0).toChar()) {
            backgroundSecondary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (backgroundSecondary_buf_selector == (1).toChar()) {
            backgroundSecondary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (backgroundSecondary_buf_selector == (2).toChar()) {
            backgroundSecondary_buf = (valueDeserializer.readString() as string)
        }
        else if (backgroundSecondary_buf_selector == (3).toChar()) {
            backgroundSecondary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for backgroundSecondary_buf has to be chosen through deserialisation.")
        }
        const backgroundSecondary_result : ResourceColor = (backgroundSecondary_buf as Color | number | string | Resource)
        const backgroundTertiary_buf_selector : int32 = valueDeserializer.readInt8()
        let backgroundTertiary_buf : Color | number | string | Resource | undefined
        if (backgroundTertiary_buf_selector == (0).toChar()) {
            backgroundTertiary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (backgroundTertiary_buf_selector == (1).toChar()) {
            backgroundTertiary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (backgroundTertiary_buf_selector == (2).toChar()) {
            backgroundTertiary_buf = (valueDeserializer.readString() as string)
        }
        else if (backgroundTertiary_buf_selector == (3).toChar()) {
            backgroundTertiary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for backgroundTertiary_buf has to be chosen through deserialisation.")
        }
        const backgroundTertiary_result : ResourceColor = (backgroundTertiary_buf as Color | number | string | Resource)
        const backgroundFourth_buf_selector : int32 = valueDeserializer.readInt8()
        let backgroundFourth_buf : Color | number | string | Resource | undefined
        if (backgroundFourth_buf_selector == (0).toChar()) {
            backgroundFourth_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (backgroundFourth_buf_selector == (1).toChar()) {
            backgroundFourth_buf = (valueDeserializer.readNumber() as number)
        }
        else if (backgroundFourth_buf_selector == (2).toChar()) {
            backgroundFourth_buf = (valueDeserializer.readString() as string)
        }
        else if (backgroundFourth_buf_selector == (3).toChar()) {
            backgroundFourth_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for backgroundFourth_buf has to be chosen through deserialisation.")
        }
        const backgroundFourth_result : ResourceColor = (backgroundFourth_buf as Color | number | string | Resource)
        const backgroundEmphasize_buf_selector : int32 = valueDeserializer.readInt8()
        let backgroundEmphasize_buf : Color | number | string | Resource | undefined
        if (backgroundEmphasize_buf_selector == (0).toChar()) {
            backgroundEmphasize_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (backgroundEmphasize_buf_selector == (1).toChar()) {
            backgroundEmphasize_buf = (valueDeserializer.readNumber() as number)
        }
        else if (backgroundEmphasize_buf_selector == (2).toChar()) {
            backgroundEmphasize_buf = (valueDeserializer.readString() as string)
        }
        else if (backgroundEmphasize_buf_selector == (3).toChar()) {
            backgroundEmphasize_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for backgroundEmphasize_buf has to be chosen through deserialisation.")
        }
        const backgroundEmphasize_result : ResourceColor = (backgroundEmphasize_buf as Color | number | string | Resource)
        const compForegroundPrimary_buf_selector : int32 = valueDeserializer.readInt8()
        let compForegroundPrimary_buf : Color | number | string | Resource | undefined
        if (compForegroundPrimary_buf_selector == (0).toChar()) {
            compForegroundPrimary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compForegroundPrimary_buf_selector == (1).toChar()) {
            compForegroundPrimary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compForegroundPrimary_buf_selector == (2).toChar()) {
            compForegroundPrimary_buf = (valueDeserializer.readString() as string)
        }
        else if (compForegroundPrimary_buf_selector == (3).toChar()) {
            compForegroundPrimary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compForegroundPrimary_buf has to be chosen through deserialisation.")
        }
        const compForegroundPrimary_result : ResourceColor = (compForegroundPrimary_buf as Color | number | string | Resource)
        const compBackgroundPrimary_buf_selector : int32 = valueDeserializer.readInt8()
        let compBackgroundPrimary_buf : Color | number | string | Resource | undefined
        if (compBackgroundPrimary_buf_selector == (0).toChar()) {
            compBackgroundPrimary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compBackgroundPrimary_buf_selector == (1).toChar()) {
            compBackgroundPrimary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compBackgroundPrimary_buf_selector == (2).toChar()) {
            compBackgroundPrimary_buf = (valueDeserializer.readString() as string)
        }
        else if (compBackgroundPrimary_buf_selector == (3).toChar()) {
            compBackgroundPrimary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compBackgroundPrimary_buf has to be chosen through deserialisation.")
        }
        const compBackgroundPrimary_result : ResourceColor = (compBackgroundPrimary_buf as Color | number | string | Resource)
        const compBackgroundPrimaryTran_buf_selector : int32 = valueDeserializer.readInt8()
        let compBackgroundPrimaryTran_buf : Color | number | string | Resource | undefined
        if (compBackgroundPrimaryTran_buf_selector == (0).toChar()) {
            compBackgroundPrimaryTran_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compBackgroundPrimaryTran_buf_selector == (1).toChar()) {
            compBackgroundPrimaryTran_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compBackgroundPrimaryTran_buf_selector == (2).toChar()) {
            compBackgroundPrimaryTran_buf = (valueDeserializer.readString() as string)
        }
        else if (compBackgroundPrimaryTran_buf_selector == (3).toChar()) {
            compBackgroundPrimaryTran_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compBackgroundPrimaryTran_buf has to be chosen through deserialisation.")
        }
        const compBackgroundPrimaryTran_result : ResourceColor = (compBackgroundPrimaryTran_buf as Color | number | string | Resource)
        const compBackgroundPrimaryContrary_buf_selector : int32 = valueDeserializer.readInt8()
        let compBackgroundPrimaryContrary_buf : Color | number | string | Resource | undefined
        if (compBackgroundPrimaryContrary_buf_selector == (0).toChar()) {
            compBackgroundPrimaryContrary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compBackgroundPrimaryContrary_buf_selector == (1).toChar()) {
            compBackgroundPrimaryContrary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compBackgroundPrimaryContrary_buf_selector == (2).toChar()) {
            compBackgroundPrimaryContrary_buf = (valueDeserializer.readString() as string)
        }
        else if (compBackgroundPrimaryContrary_buf_selector == (3).toChar()) {
            compBackgroundPrimaryContrary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compBackgroundPrimaryContrary_buf has to be chosen through deserialisation.")
        }
        const compBackgroundPrimaryContrary_result : ResourceColor = (compBackgroundPrimaryContrary_buf as Color | number | string | Resource)
        const compBackgroundGray_buf_selector : int32 = valueDeserializer.readInt8()
        let compBackgroundGray_buf : Color | number | string | Resource | undefined
        if (compBackgroundGray_buf_selector == (0).toChar()) {
            compBackgroundGray_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compBackgroundGray_buf_selector == (1).toChar()) {
            compBackgroundGray_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compBackgroundGray_buf_selector == (2).toChar()) {
            compBackgroundGray_buf = (valueDeserializer.readString() as string)
        }
        else if (compBackgroundGray_buf_selector == (3).toChar()) {
            compBackgroundGray_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compBackgroundGray_buf has to be chosen through deserialisation.")
        }
        const compBackgroundGray_result : ResourceColor = (compBackgroundGray_buf as Color | number | string | Resource)
        const compBackgroundSecondary_buf_selector : int32 = valueDeserializer.readInt8()
        let compBackgroundSecondary_buf : Color | number | string | Resource | undefined
        if (compBackgroundSecondary_buf_selector == (0).toChar()) {
            compBackgroundSecondary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compBackgroundSecondary_buf_selector == (1).toChar()) {
            compBackgroundSecondary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compBackgroundSecondary_buf_selector == (2).toChar()) {
            compBackgroundSecondary_buf = (valueDeserializer.readString() as string)
        }
        else if (compBackgroundSecondary_buf_selector == (3).toChar()) {
            compBackgroundSecondary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compBackgroundSecondary_buf has to be chosen through deserialisation.")
        }
        const compBackgroundSecondary_result : ResourceColor = (compBackgroundSecondary_buf as Color | number | string | Resource)
        const compBackgroundTertiary_buf_selector : int32 = valueDeserializer.readInt8()
        let compBackgroundTertiary_buf : Color | number | string | Resource | undefined
        if (compBackgroundTertiary_buf_selector == (0).toChar()) {
            compBackgroundTertiary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compBackgroundTertiary_buf_selector == (1).toChar()) {
            compBackgroundTertiary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compBackgroundTertiary_buf_selector == (2).toChar()) {
            compBackgroundTertiary_buf = (valueDeserializer.readString() as string)
        }
        else if (compBackgroundTertiary_buf_selector == (3).toChar()) {
            compBackgroundTertiary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compBackgroundTertiary_buf has to be chosen through deserialisation.")
        }
        const compBackgroundTertiary_result : ResourceColor = (compBackgroundTertiary_buf as Color | number | string | Resource)
        const compBackgroundEmphasize_buf_selector : int32 = valueDeserializer.readInt8()
        let compBackgroundEmphasize_buf : Color | number | string | Resource | undefined
        if (compBackgroundEmphasize_buf_selector == (0).toChar()) {
            compBackgroundEmphasize_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compBackgroundEmphasize_buf_selector == (1).toChar()) {
            compBackgroundEmphasize_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compBackgroundEmphasize_buf_selector == (2).toChar()) {
            compBackgroundEmphasize_buf = (valueDeserializer.readString() as string)
        }
        else if (compBackgroundEmphasize_buf_selector == (3).toChar()) {
            compBackgroundEmphasize_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compBackgroundEmphasize_buf has to be chosen through deserialisation.")
        }
        const compBackgroundEmphasize_result : ResourceColor = (compBackgroundEmphasize_buf as Color | number | string | Resource)
        const compBackgroundNeutral_buf_selector : int32 = valueDeserializer.readInt8()
        let compBackgroundNeutral_buf : Color | number | string | Resource | undefined
        if (compBackgroundNeutral_buf_selector == (0).toChar()) {
            compBackgroundNeutral_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compBackgroundNeutral_buf_selector == (1).toChar()) {
            compBackgroundNeutral_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compBackgroundNeutral_buf_selector == (2).toChar()) {
            compBackgroundNeutral_buf = (valueDeserializer.readString() as string)
        }
        else if (compBackgroundNeutral_buf_selector == (3).toChar()) {
            compBackgroundNeutral_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compBackgroundNeutral_buf has to be chosen through deserialisation.")
        }
        const compBackgroundNeutral_result : ResourceColor = (compBackgroundNeutral_buf as Color | number | string | Resource)
        const compEmphasizeSecondary_buf_selector : int32 = valueDeserializer.readInt8()
        let compEmphasizeSecondary_buf : Color | number | string | Resource | undefined
        if (compEmphasizeSecondary_buf_selector == (0).toChar()) {
            compEmphasizeSecondary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compEmphasizeSecondary_buf_selector == (1).toChar()) {
            compEmphasizeSecondary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compEmphasizeSecondary_buf_selector == (2).toChar()) {
            compEmphasizeSecondary_buf = (valueDeserializer.readString() as string)
        }
        else if (compEmphasizeSecondary_buf_selector == (3).toChar()) {
            compEmphasizeSecondary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compEmphasizeSecondary_buf has to be chosen through deserialisation.")
        }
        const compEmphasizeSecondary_result : ResourceColor = (compEmphasizeSecondary_buf as Color | number | string | Resource)
        const compEmphasizeTertiary_buf_selector : int32 = valueDeserializer.readInt8()
        let compEmphasizeTertiary_buf : Color | number | string | Resource | undefined
        if (compEmphasizeTertiary_buf_selector == (0).toChar()) {
            compEmphasizeTertiary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compEmphasizeTertiary_buf_selector == (1).toChar()) {
            compEmphasizeTertiary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compEmphasizeTertiary_buf_selector == (2).toChar()) {
            compEmphasizeTertiary_buf = (valueDeserializer.readString() as string)
        }
        else if (compEmphasizeTertiary_buf_selector == (3).toChar()) {
            compEmphasizeTertiary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compEmphasizeTertiary_buf has to be chosen through deserialisation.")
        }
        const compEmphasizeTertiary_result : ResourceColor = (compEmphasizeTertiary_buf as Color | number | string | Resource)
        const compDivider_buf_selector : int32 = valueDeserializer.readInt8()
        let compDivider_buf : Color | number | string | Resource | undefined
        if (compDivider_buf_selector == (0).toChar()) {
            compDivider_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compDivider_buf_selector == (1).toChar()) {
            compDivider_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compDivider_buf_selector == (2).toChar()) {
            compDivider_buf = (valueDeserializer.readString() as string)
        }
        else if (compDivider_buf_selector == (3).toChar()) {
            compDivider_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compDivider_buf has to be chosen through deserialisation.")
        }
        const compDivider_result : ResourceColor = (compDivider_buf as Color | number | string | Resource)
        const compCommonContrary_buf_selector : int32 = valueDeserializer.readInt8()
        let compCommonContrary_buf : Color | number | string | Resource | undefined
        if (compCommonContrary_buf_selector == (0).toChar()) {
            compCommonContrary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compCommonContrary_buf_selector == (1).toChar()) {
            compCommonContrary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compCommonContrary_buf_selector == (2).toChar()) {
            compCommonContrary_buf = (valueDeserializer.readString() as string)
        }
        else if (compCommonContrary_buf_selector == (3).toChar()) {
            compCommonContrary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compCommonContrary_buf has to be chosen through deserialisation.")
        }
        const compCommonContrary_result : ResourceColor = (compCommonContrary_buf as Color | number | string | Resource)
        const compBackgroundFocus_buf_selector : int32 = valueDeserializer.readInt8()
        let compBackgroundFocus_buf : Color | number | string | Resource | undefined
        if (compBackgroundFocus_buf_selector == (0).toChar()) {
            compBackgroundFocus_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compBackgroundFocus_buf_selector == (1).toChar()) {
            compBackgroundFocus_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compBackgroundFocus_buf_selector == (2).toChar()) {
            compBackgroundFocus_buf = (valueDeserializer.readString() as string)
        }
        else if (compBackgroundFocus_buf_selector == (3).toChar()) {
            compBackgroundFocus_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compBackgroundFocus_buf has to be chosen through deserialisation.")
        }
        const compBackgroundFocus_result : ResourceColor = (compBackgroundFocus_buf as Color | number | string | Resource)
        const compFocusedPrimary_buf_selector : int32 = valueDeserializer.readInt8()
        let compFocusedPrimary_buf : Color | number | string | Resource | undefined
        if (compFocusedPrimary_buf_selector == (0).toChar()) {
            compFocusedPrimary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compFocusedPrimary_buf_selector == (1).toChar()) {
            compFocusedPrimary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compFocusedPrimary_buf_selector == (2).toChar()) {
            compFocusedPrimary_buf = (valueDeserializer.readString() as string)
        }
        else if (compFocusedPrimary_buf_selector == (3).toChar()) {
            compFocusedPrimary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compFocusedPrimary_buf has to be chosen through deserialisation.")
        }
        const compFocusedPrimary_result : ResourceColor = (compFocusedPrimary_buf as Color | number | string | Resource)
        const compFocusedSecondary_buf_selector : int32 = valueDeserializer.readInt8()
        let compFocusedSecondary_buf : Color | number | string | Resource | undefined
        if (compFocusedSecondary_buf_selector == (0).toChar()) {
            compFocusedSecondary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compFocusedSecondary_buf_selector == (1).toChar()) {
            compFocusedSecondary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compFocusedSecondary_buf_selector == (2).toChar()) {
            compFocusedSecondary_buf = (valueDeserializer.readString() as string)
        }
        else if (compFocusedSecondary_buf_selector == (3).toChar()) {
            compFocusedSecondary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compFocusedSecondary_buf has to be chosen through deserialisation.")
        }
        const compFocusedSecondary_result : ResourceColor = (compFocusedSecondary_buf as Color | number | string | Resource)
        const compFocusedTertiary_buf_selector : int32 = valueDeserializer.readInt8()
        let compFocusedTertiary_buf : Color | number | string | Resource | undefined
        if (compFocusedTertiary_buf_selector == (0).toChar()) {
            compFocusedTertiary_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (compFocusedTertiary_buf_selector == (1).toChar()) {
            compFocusedTertiary_buf = (valueDeserializer.readNumber() as number)
        }
        else if (compFocusedTertiary_buf_selector == (2).toChar()) {
            compFocusedTertiary_buf = (valueDeserializer.readString() as string)
        }
        else if (compFocusedTertiary_buf_selector == (3).toChar()) {
            compFocusedTertiary_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for compFocusedTertiary_buf has to be chosen through deserialisation.")
        }
        const compFocusedTertiary_result : ResourceColor = (compFocusedTertiary_buf as Color | number | string | Resource)
        const interactiveHover_buf_selector : int32 = valueDeserializer.readInt8()
        let interactiveHover_buf : Color | number | string | Resource | undefined
        if (interactiveHover_buf_selector == (0).toChar()) {
            interactiveHover_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (interactiveHover_buf_selector == (1).toChar()) {
            interactiveHover_buf = (valueDeserializer.readNumber() as number)
        }
        else if (interactiveHover_buf_selector == (2).toChar()) {
            interactiveHover_buf = (valueDeserializer.readString() as string)
        }
        else if (interactiveHover_buf_selector == (3).toChar()) {
            interactiveHover_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for interactiveHover_buf has to be chosen through deserialisation.")
        }
        const interactiveHover_result : ResourceColor = (interactiveHover_buf as Color | number | string | Resource)
        const interactivePressed_buf_selector : int32 = valueDeserializer.readInt8()
        let interactivePressed_buf : Color | number | string | Resource | undefined
        if (interactivePressed_buf_selector == (0).toChar()) {
            interactivePressed_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (interactivePressed_buf_selector == (1).toChar()) {
            interactivePressed_buf = (valueDeserializer.readNumber() as number)
        }
        else if (interactivePressed_buf_selector == (2).toChar()) {
            interactivePressed_buf = (valueDeserializer.readString() as string)
        }
        else if (interactivePressed_buf_selector == (3).toChar()) {
            interactivePressed_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for interactivePressed_buf has to be chosen through deserialisation.")
        }
        const interactivePressed_result : ResourceColor = (interactivePressed_buf as Color | number | string | Resource)
        const interactiveFocus_buf_selector : int32 = valueDeserializer.readInt8()
        let interactiveFocus_buf : Color | number | string | Resource | undefined
        if (interactiveFocus_buf_selector == (0).toChar()) {
            interactiveFocus_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (interactiveFocus_buf_selector == (1).toChar()) {
            interactiveFocus_buf = (valueDeserializer.readNumber() as number)
        }
        else if (interactiveFocus_buf_selector == (2).toChar()) {
            interactiveFocus_buf = (valueDeserializer.readString() as string)
        }
        else if (interactiveFocus_buf_selector == (3).toChar()) {
            interactiveFocus_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for interactiveFocus_buf has to be chosen through deserialisation.")
        }
        const interactiveFocus_result : ResourceColor = (interactiveFocus_buf as Color | number | string | Resource)
        const interactiveActive_buf_selector : int32 = valueDeserializer.readInt8()
        let interactiveActive_buf : Color | number | string | Resource | undefined
        if (interactiveActive_buf_selector == (0).toChar()) {
            interactiveActive_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (interactiveActive_buf_selector == (1).toChar()) {
            interactiveActive_buf = (valueDeserializer.readNumber() as number)
        }
        else if (interactiveActive_buf_selector == (2).toChar()) {
            interactiveActive_buf = (valueDeserializer.readString() as string)
        }
        else if (interactiveActive_buf_selector == (3).toChar()) {
            interactiveActive_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for interactiveActive_buf has to be chosen through deserialisation.")
        }
        const interactiveActive_result : ResourceColor = (interactiveActive_buf as Color | number | string | Resource)
        const interactiveSelect_buf_selector : int32 = valueDeserializer.readInt8()
        let interactiveSelect_buf : Color | number | string | Resource | undefined
        if (interactiveSelect_buf_selector == (0).toChar()) {
            interactiveSelect_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (interactiveSelect_buf_selector == (1).toChar()) {
            interactiveSelect_buf = (valueDeserializer.readNumber() as number)
        }
        else if (interactiveSelect_buf_selector == (2).toChar()) {
            interactiveSelect_buf = (valueDeserializer.readString() as string)
        }
        else if (interactiveSelect_buf_selector == (3).toChar()) {
            interactiveSelect_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for interactiveSelect_buf has to be chosen through deserialisation.")
        }
        const interactiveSelect_result : ResourceColor = (interactiveSelect_buf as Color | number | string | Resource)
        const interactiveClick_buf_selector : int32 = valueDeserializer.readInt8()
        let interactiveClick_buf : Color | number | string | Resource | undefined
        if (interactiveClick_buf_selector == (0).toChar()) {
            interactiveClick_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (interactiveClick_buf_selector == (1).toChar()) {
            interactiveClick_buf = (valueDeserializer.readNumber() as number)
        }
        else if (interactiveClick_buf_selector == (2).toChar()) {
            interactiveClick_buf = (valueDeserializer.readString() as string)
        }
        else if (interactiveClick_buf_selector == (3).toChar()) {
            interactiveClick_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for interactiveClick_buf has to be chosen through deserialisation.")
        }
        const interactiveClick_result : ResourceColor = (interactiveClick_buf as Color | number | string | Resource)
        let value : Colors = ({brand: brand_result, warning: warning_result, alert: alert_result, confirm: confirm_result, fontPrimary: fontPrimary_result, fontSecondary: fontSecondary_result, fontTertiary: fontTertiary_result, fontFourth: fontFourth_result, fontEmphasize: fontEmphasize_result, fontOnPrimary: fontOnPrimary_result, fontOnSecondary: fontOnSecondary_result, fontOnTertiary: fontOnTertiary_result, fontOnFourth: fontOnFourth_result, iconPrimary: iconPrimary_result, iconSecondary: iconSecondary_result, iconTertiary: iconTertiary_result, iconFourth: iconFourth_result, iconEmphasize: iconEmphasize_result, iconSubEmphasize: iconSubEmphasize_result, iconOnPrimary: iconOnPrimary_result, iconOnSecondary: iconOnSecondary_result, iconOnTertiary: iconOnTertiary_result, iconOnFourth: iconOnFourth_result, backgroundPrimary: backgroundPrimary_result, backgroundSecondary: backgroundSecondary_result, backgroundTertiary: backgroundTertiary_result, backgroundFourth: backgroundFourth_result, backgroundEmphasize: backgroundEmphasize_result, compForegroundPrimary: compForegroundPrimary_result, compBackgroundPrimary: compBackgroundPrimary_result, compBackgroundPrimaryTran: compBackgroundPrimaryTran_result, compBackgroundPrimaryContrary: compBackgroundPrimaryContrary_result, compBackgroundGray: compBackgroundGray_result, compBackgroundSecondary: compBackgroundSecondary_result, compBackgroundTertiary: compBackgroundTertiary_result, compBackgroundEmphasize: compBackgroundEmphasize_result, compBackgroundNeutral: compBackgroundNeutral_result, compEmphasizeSecondary: compEmphasizeSecondary_result, compEmphasizeTertiary: compEmphasizeTertiary_result, compDivider: compDivider_result, compCommonContrary: compCommonContrary_result, compBackgroundFocus: compBackgroundFocus_result, compFocusedPrimary: compFocusedPrimary_result, compFocusedSecondary: compFocusedSecondary_result, compFocusedTertiary: compFocusedTertiary_result, interactiveHover: interactiveHover_result, interactivePressed: interactivePressed_result, interactiveFocus: interactiveFocus_result, interactiveActive: interactiveActive_result, interactiveSelect: interactiveSelect_result, interactiveClick: interactiveClick_result} as Colors)
        return value
    }
}
export class CustomTheme_serializer {
    public static write(buffer: SerializerBase, value: CustomTheme): void {
        let valueSerializer : SerializerBase = buffer
        const value_colors  = value.colors
        let value_colors_type : int32 = RuntimeType.UNDEFINED
        value_colors_type = runtimeType(value_colors)
        valueSerializer.writeInt8((value_colors_type).toChar())
        if ((value_colors_type) != (RuntimeType.UNDEFINED)) {
            const value_colors_value  = value_colors!
            Colors_serializer.write(valueSerializer, value_colors_value)
        }
    }
    public static read(buffer: DeserializerBase): CustomTheme {
        let valueDeserializer : DeserializerBase = buffer
        const colors_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colors_buf : Colors | undefined
        if ((colors_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            colors_buf = Colors_serializer.read(valueDeserializer)
        }
        const colors_result : Colors | undefined = colors_buf
        let value : CustomTheme = ({colors: colors_result} as CustomTheme)
        return value
    }
}
