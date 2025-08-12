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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
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
        const valueHolderForBrand  = value.brand
        if (valueHolderForBrand instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForBrandForIdx0  = valueHolderForBrand as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForBrandForIdx0))
        } else if (valueHolderForBrand instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForBrandForIdx1  = valueHolderForBrand as number
            valueSerializer.writeNumber(valueHolderForBrandForIdx1)
        } else if (valueHolderForBrand instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForBrandForIdx2  = valueHolderForBrand as string
            valueSerializer.writeString(valueHolderForBrandForIdx2)
        } else if (valueHolderForBrand instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForBrandForIdx3  = valueHolderForBrand as Resource
            Resource_serializer.write(valueSerializer, valueHolderForBrandForIdx3)
        }
        const valueHolderForWarning  = value.warning
        if (valueHolderForWarning instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForWarningForIdx0  = valueHolderForWarning as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForWarningForIdx0))
        } else if (valueHolderForWarning instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForWarningForIdx1  = valueHolderForWarning as number
            valueSerializer.writeNumber(valueHolderForWarningForIdx1)
        } else if (valueHolderForWarning instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForWarningForIdx2  = valueHolderForWarning as string
            valueSerializer.writeString(valueHolderForWarningForIdx2)
        } else if (valueHolderForWarning instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForWarningForIdx3  = valueHolderForWarning as Resource
            Resource_serializer.write(valueSerializer, valueHolderForWarningForIdx3)
        }
        const valueHolderForAlert  = value.alert
        if (valueHolderForAlert instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForAlertForIdx0  = valueHolderForAlert as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForAlertForIdx0))
        } else if (valueHolderForAlert instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForAlertForIdx1  = valueHolderForAlert as number
            valueSerializer.writeNumber(valueHolderForAlertForIdx1)
        } else if (valueHolderForAlert instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForAlertForIdx2  = valueHolderForAlert as string
            valueSerializer.writeString(valueHolderForAlertForIdx2)
        } else if (valueHolderForAlert instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForAlertForIdx3  = valueHolderForAlert as Resource
            Resource_serializer.write(valueSerializer, valueHolderForAlertForIdx3)
        }
        const valueHolderForConfirm  = value.confirm
        if (valueHolderForConfirm instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForConfirmForIdx0  = valueHolderForConfirm as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForConfirmForIdx0))
        } else if (valueHolderForConfirm instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForConfirmForIdx1  = valueHolderForConfirm as number
            valueSerializer.writeNumber(valueHolderForConfirmForIdx1)
        } else if (valueHolderForConfirm instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForConfirmForIdx2  = valueHolderForConfirm as string
            valueSerializer.writeString(valueHolderForConfirmForIdx2)
        } else if (valueHolderForConfirm instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForConfirmForIdx3  = valueHolderForConfirm as Resource
            Resource_serializer.write(valueSerializer, valueHolderForConfirmForIdx3)
        }
        const valueHolderForFontPrimary  = value.fontPrimary
        if (valueHolderForFontPrimary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForFontPrimaryForIdx0  = valueHolderForFontPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForFontPrimaryForIdx0))
        } else if (valueHolderForFontPrimary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForFontPrimaryForIdx1  = valueHolderForFontPrimary as number
            valueSerializer.writeNumber(valueHolderForFontPrimaryForIdx1)
        } else if (valueHolderForFontPrimary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForFontPrimaryForIdx2  = valueHolderForFontPrimary as string
            valueSerializer.writeString(valueHolderForFontPrimaryForIdx2)
        } else if (valueHolderForFontPrimary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForFontPrimaryForIdx3  = valueHolderForFontPrimary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFontPrimaryForIdx3)
        }
        const valueHolderForFontSecondary  = value.fontSecondary
        if (valueHolderForFontSecondary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForFontSecondaryForIdx0  = valueHolderForFontSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForFontSecondaryForIdx0))
        } else if (valueHolderForFontSecondary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForFontSecondaryForIdx1  = valueHolderForFontSecondary as number
            valueSerializer.writeNumber(valueHolderForFontSecondaryForIdx1)
        } else if (valueHolderForFontSecondary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForFontSecondaryForIdx2  = valueHolderForFontSecondary as string
            valueSerializer.writeString(valueHolderForFontSecondaryForIdx2)
        } else if (valueHolderForFontSecondary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForFontSecondaryForIdx3  = valueHolderForFontSecondary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFontSecondaryForIdx3)
        }
        const valueHolderForFontTertiary  = value.fontTertiary
        if (valueHolderForFontTertiary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForFontTertiaryForIdx0  = valueHolderForFontTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForFontTertiaryForIdx0))
        } else if (valueHolderForFontTertiary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForFontTertiaryForIdx1  = valueHolderForFontTertiary as number
            valueSerializer.writeNumber(valueHolderForFontTertiaryForIdx1)
        } else if (valueHolderForFontTertiary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForFontTertiaryForIdx2  = valueHolderForFontTertiary as string
            valueSerializer.writeString(valueHolderForFontTertiaryForIdx2)
        } else if (valueHolderForFontTertiary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForFontTertiaryForIdx3  = valueHolderForFontTertiary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFontTertiaryForIdx3)
        }
        const valueHolderForFontFourth  = value.fontFourth
        if (valueHolderForFontFourth instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForFontFourthForIdx0  = valueHolderForFontFourth as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForFontFourthForIdx0))
        } else if (valueHolderForFontFourth instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForFontFourthForIdx1  = valueHolderForFontFourth as number
            valueSerializer.writeNumber(valueHolderForFontFourthForIdx1)
        } else if (valueHolderForFontFourth instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForFontFourthForIdx2  = valueHolderForFontFourth as string
            valueSerializer.writeString(valueHolderForFontFourthForIdx2)
        } else if (valueHolderForFontFourth instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForFontFourthForIdx3  = valueHolderForFontFourth as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFontFourthForIdx3)
        }
        const valueHolderForFontEmphasize  = value.fontEmphasize
        if (valueHolderForFontEmphasize instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForFontEmphasizeForIdx0  = valueHolderForFontEmphasize as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForFontEmphasizeForIdx0))
        } else if (valueHolderForFontEmphasize instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForFontEmphasizeForIdx1  = valueHolderForFontEmphasize as number
            valueSerializer.writeNumber(valueHolderForFontEmphasizeForIdx1)
        } else if (valueHolderForFontEmphasize instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForFontEmphasizeForIdx2  = valueHolderForFontEmphasize as string
            valueSerializer.writeString(valueHolderForFontEmphasizeForIdx2)
        } else if (valueHolderForFontEmphasize instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForFontEmphasizeForIdx3  = valueHolderForFontEmphasize as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFontEmphasizeForIdx3)
        }
        const valueHolderForFontOnPrimary  = value.fontOnPrimary
        if (valueHolderForFontOnPrimary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForFontOnPrimaryForIdx0  = valueHolderForFontOnPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForFontOnPrimaryForIdx0))
        } else if (valueHolderForFontOnPrimary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForFontOnPrimaryForIdx1  = valueHolderForFontOnPrimary as number
            valueSerializer.writeNumber(valueHolderForFontOnPrimaryForIdx1)
        } else if (valueHolderForFontOnPrimary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForFontOnPrimaryForIdx2  = valueHolderForFontOnPrimary as string
            valueSerializer.writeString(valueHolderForFontOnPrimaryForIdx2)
        } else if (valueHolderForFontOnPrimary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForFontOnPrimaryForIdx3  = valueHolderForFontOnPrimary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFontOnPrimaryForIdx3)
        }
        const valueHolderForFontOnSecondary  = value.fontOnSecondary
        if (valueHolderForFontOnSecondary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForFontOnSecondaryForIdx0  = valueHolderForFontOnSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForFontOnSecondaryForIdx0))
        } else if (valueHolderForFontOnSecondary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForFontOnSecondaryForIdx1  = valueHolderForFontOnSecondary as number
            valueSerializer.writeNumber(valueHolderForFontOnSecondaryForIdx1)
        } else if (valueHolderForFontOnSecondary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForFontOnSecondaryForIdx2  = valueHolderForFontOnSecondary as string
            valueSerializer.writeString(valueHolderForFontOnSecondaryForIdx2)
        } else if (valueHolderForFontOnSecondary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForFontOnSecondaryForIdx3  = valueHolderForFontOnSecondary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFontOnSecondaryForIdx3)
        }
        const valueHolderForFontOnTertiary  = value.fontOnTertiary
        if (valueHolderForFontOnTertiary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForFontOnTertiaryForIdx0  = valueHolderForFontOnTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForFontOnTertiaryForIdx0))
        } else if (valueHolderForFontOnTertiary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForFontOnTertiaryForIdx1  = valueHolderForFontOnTertiary as number
            valueSerializer.writeNumber(valueHolderForFontOnTertiaryForIdx1)
        } else if (valueHolderForFontOnTertiary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForFontOnTertiaryForIdx2  = valueHolderForFontOnTertiary as string
            valueSerializer.writeString(valueHolderForFontOnTertiaryForIdx2)
        } else if (valueHolderForFontOnTertiary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForFontOnTertiaryForIdx3  = valueHolderForFontOnTertiary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFontOnTertiaryForIdx3)
        }
        const valueHolderForFontOnFourth  = value.fontOnFourth
        if (valueHolderForFontOnFourth instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForFontOnFourthForIdx0  = valueHolderForFontOnFourth as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForFontOnFourthForIdx0))
        } else if (valueHolderForFontOnFourth instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForFontOnFourthForIdx1  = valueHolderForFontOnFourth as number
            valueSerializer.writeNumber(valueHolderForFontOnFourthForIdx1)
        } else if (valueHolderForFontOnFourth instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForFontOnFourthForIdx2  = valueHolderForFontOnFourth as string
            valueSerializer.writeString(valueHolderForFontOnFourthForIdx2)
        } else if (valueHolderForFontOnFourth instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForFontOnFourthForIdx3  = valueHolderForFontOnFourth as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFontOnFourthForIdx3)
        }
        const valueHolderForIconPrimary  = value.iconPrimary
        if (valueHolderForIconPrimary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForIconPrimaryForIdx0  = valueHolderForIconPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForIconPrimaryForIdx0))
        } else if (valueHolderForIconPrimary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForIconPrimaryForIdx1  = valueHolderForIconPrimary as number
            valueSerializer.writeNumber(valueHolderForIconPrimaryForIdx1)
        } else if (valueHolderForIconPrimary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForIconPrimaryForIdx2  = valueHolderForIconPrimary as string
            valueSerializer.writeString(valueHolderForIconPrimaryForIdx2)
        } else if (valueHolderForIconPrimary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForIconPrimaryForIdx3  = valueHolderForIconPrimary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForIconPrimaryForIdx3)
        }
        const valueHolderForIconSecondary  = value.iconSecondary
        if (valueHolderForIconSecondary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForIconSecondaryForIdx0  = valueHolderForIconSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForIconSecondaryForIdx0))
        } else if (valueHolderForIconSecondary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForIconSecondaryForIdx1  = valueHolderForIconSecondary as number
            valueSerializer.writeNumber(valueHolderForIconSecondaryForIdx1)
        } else if (valueHolderForIconSecondary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForIconSecondaryForIdx2  = valueHolderForIconSecondary as string
            valueSerializer.writeString(valueHolderForIconSecondaryForIdx2)
        } else if (valueHolderForIconSecondary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForIconSecondaryForIdx3  = valueHolderForIconSecondary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForIconSecondaryForIdx3)
        }
        const valueHolderForIconTertiary  = value.iconTertiary
        if (valueHolderForIconTertiary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForIconTertiaryForIdx0  = valueHolderForIconTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForIconTertiaryForIdx0))
        } else if (valueHolderForIconTertiary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForIconTertiaryForIdx1  = valueHolderForIconTertiary as number
            valueSerializer.writeNumber(valueHolderForIconTertiaryForIdx1)
        } else if (valueHolderForIconTertiary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForIconTertiaryForIdx2  = valueHolderForIconTertiary as string
            valueSerializer.writeString(valueHolderForIconTertiaryForIdx2)
        } else if (valueHolderForIconTertiary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForIconTertiaryForIdx3  = valueHolderForIconTertiary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForIconTertiaryForIdx3)
        }
        const valueHolderForIconFourth  = value.iconFourth
        if (valueHolderForIconFourth instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForIconFourthForIdx0  = valueHolderForIconFourth as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForIconFourthForIdx0))
        } else if (valueHolderForIconFourth instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForIconFourthForIdx1  = valueHolderForIconFourth as number
            valueSerializer.writeNumber(valueHolderForIconFourthForIdx1)
        } else if (valueHolderForIconFourth instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForIconFourthForIdx2  = valueHolderForIconFourth as string
            valueSerializer.writeString(valueHolderForIconFourthForIdx2)
        } else if (valueHolderForIconFourth instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForIconFourthForIdx3  = valueHolderForIconFourth as Resource
            Resource_serializer.write(valueSerializer, valueHolderForIconFourthForIdx3)
        }
        const valueHolderForIconEmphasize  = value.iconEmphasize
        if (valueHolderForIconEmphasize instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForIconEmphasizeForIdx0  = valueHolderForIconEmphasize as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForIconEmphasizeForIdx0))
        } else if (valueHolderForIconEmphasize instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForIconEmphasizeForIdx1  = valueHolderForIconEmphasize as number
            valueSerializer.writeNumber(valueHolderForIconEmphasizeForIdx1)
        } else if (valueHolderForIconEmphasize instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForIconEmphasizeForIdx2  = valueHolderForIconEmphasize as string
            valueSerializer.writeString(valueHolderForIconEmphasizeForIdx2)
        } else if (valueHolderForIconEmphasize instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForIconEmphasizeForIdx3  = valueHolderForIconEmphasize as Resource
            Resource_serializer.write(valueSerializer, valueHolderForIconEmphasizeForIdx3)
        }
        const valueHolderForIconSubEmphasize  = value.iconSubEmphasize
        if (valueHolderForIconSubEmphasize instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForIconSubEmphasizeForIdx0  = valueHolderForIconSubEmphasize as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForIconSubEmphasizeForIdx0))
        } else if (valueHolderForIconSubEmphasize instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForIconSubEmphasizeForIdx1  = valueHolderForIconSubEmphasize as number
            valueSerializer.writeNumber(valueHolderForIconSubEmphasizeForIdx1)
        } else if (valueHolderForIconSubEmphasize instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForIconSubEmphasizeForIdx2  = valueHolderForIconSubEmphasize as string
            valueSerializer.writeString(valueHolderForIconSubEmphasizeForIdx2)
        } else if (valueHolderForIconSubEmphasize instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForIconSubEmphasizeForIdx3  = valueHolderForIconSubEmphasize as Resource
            Resource_serializer.write(valueSerializer, valueHolderForIconSubEmphasizeForIdx3)
        }
        const valueHolderForIconOnPrimary  = value.iconOnPrimary
        if (valueHolderForIconOnPrimary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForIconOnPrimaryForIdx0  = valueHolderForIconOnPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForIconOnPrimaryForIdx0))
        } else if (valueHolderForIconOnPrimary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForIconOnPrimaryForIdx1  = valueHolderForIconOnPrimary as number
            valueSerializer.writeNumber(valueHolderForIconOnPrimaryForIdx1)
        } else if (valueHolderForIconOnPrimary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForIconOnPrimaryForIdx2  = valueHolderForIconOnPrimary as string
            valueSerializer.writeString(valueHolderForIconOnPrimaryForIdx2)
        } else if (valueHolderForIconOnPrimary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForIconOnPrimaryForIdx3  = valueHolderForIconOnPrimary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForIconOnPrimaryForIdx3)
        }
        const valueHolderForIconOnSecondary  = value.iconOnSecondary
        if (valueHolderForIconOnSecondary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForIconOnSecondaryForIdx0  = valueHolderForIconOnSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForIconOnSecondaryForIdx0))
        } else if (valueHolderForIconOnSecondary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForIconOnSecondaryForIdx1  = valueHolderForIconOnSecondary as number
            valueSerializer.writeNumber(valueHolderForIconOnSecondaryForIdx1)
        } else if (valueHolderForIconOnSecondary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForIconOnSecondaryForIdx2  = valueHolderForIconOnSecondary as string
            valueSerializer.writeString(valueHolderForIconOnSecondaryForIdx2)
        } else if (valueHolderForIconOnSecondary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForIconOnSecondaryForIdx3  = valueHolderForIconOnSecondary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForIconOnSecondaryForIdx3)
        }
        const valueHolderForIconOnTertiary  = value.iconOnTertiary
        if (valueHolderForIconOnTertiary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForIconOnTertiaryForIdx0  = valueHolderForIconOnTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForIconOnTertiaryForIdx0))
        } else if (valueHolderForIconOnTertiary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForIconOnTertiaryForIdx1  = valueHolderForIconOnTertiary as number
            valueSerializer.writeNumber(valueHolderForIconOnTertiaryForIdx1)
        } else if (valueHolderForIconOnTertiary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForIconOnTertiaryForIdx2  = valueHolderForIconOnTertiary as string
            valueSerializer.writeString(valueHolderForIconOnTertiaryForIdx2)
        } else if (valueHolderForIconOnTertiary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForIconOnTertiaryForIdx3  = valueHolderForIconOnTertiary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForIconOnTertiaryForIdx3)
        }
        const valueHolderForIconOnFourth  = value.iconOnFourth
        if (valueHolderForIconOnFourth instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForIconOnFourthForIdx0  = valueHolderForIconOnFourth as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForIconOnFourthForIdx0))
        } else if (valueHolderForIconOnFourth instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForIconOnFourthForIdx1  = valueHolderForIconOnFourth as number
            valueSerializer.writeNumber(valueHolderForIconOnFourthForIdx1)
        } else if (valueHolderForIconOnFourth instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForIconOnFourthForIdx2  = valueHolderForIconOnFourth as string
            valueSerializer.writeString(valueHolderForIconOnFourthForIdx2)
        } else if (valueHolderForIconOnFourth instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForIconOnFourthForIdx3  = valueHolderForIconOnFourth as Resource
            Resource_serializer.write(valueSerializer, valueHolderForIconOnFourthForIdx3)
        }
        const valueHolderForBackgroundPrimary  = value.backgroundPrimary
        if (valueHolderForBackgroundPrimary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForBackgroundPrimaryForIdx0  = valueHolderForBackgroundPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForBackgroundPrimaryForIdx0))
        } else if (valueHolderForBackgroundPrimary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForBackgroundPrimaryForIdx1  = valueHolderForBackgroundPrimary as number
            valueSerializer.writeNumber(valueHolderForBackgroundPrimaryForIdx1)
        } else if (valueHolderForBackgroundPrimary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForBackgroundPrimaryForIdx2  = valueHolderForBackgroundPrimary as string
            valueSerializer.writeString(valueHolderForBackgroundPrimaryForIdx2)
        } else if (valueHolderForBackgroundPrimary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForBackgroundPrimaryForIdx3  = valueHolderForBackgroundPrimary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForBackgroundPrimaryForIdx3)
        }
        const valueHolderForBackgroundSecondary  = value.backgroundSecondary
        if (valueHolderForBackgroundSecondary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForBackgroundSecondaryForIdx0  = valueHolderForBackgroundSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForBackgroundSecondaryForIdx0))
        } else if (valueHolderForBackgroundSecondary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForBackgroundSecondaryForIdx1  = valueHolderForBackgroundSecondary as number
            valueSerializer.writeNumber(valueHolderForBackgroundSecondaryForIdx1)
        } else if (valueHolderForBackgroundSecondary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForBackgroundSecondaryForIdx2  = valueHolderForBackgroundSecondary as string
            valueSerializer.writeString(valueHolderForBackgroundSecondaryForIdx2)
        } else if (valueHolderForBackgroundSecondary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForBackgroundSecondaryForIdx3  = valueHolderForBackgroundSecondary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForBackgroundSecondaryForIdx3)
        }
        const valueHolderForBackgroundTertiary  = value.backgroundTertiary
        if (valueHolderForBackgroundTertiary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForBackgroundTertiaryForIdx0  = valueHolderForBackgroundTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForBackgroundTertiaryForIdx0))
        } else if (valueHolderForBackgroundTertiary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForBackgroundTertiaryForIdx1  = valueHolderForBackgroundTertiary as number
            valueSerializer.writeNumber(valueHolderForBackgroundTertiaryForIdx1)
        } else if (valueHolderForBackgroundTertiary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForBackgroundTertiaryForIdx2  = valueHolderForBackgroundTertiary as string
            valueSerializer.writeString(valueHolderForBackgroundTertiaryForIdx2)
        } else if (valueHolderForBackgroundTertiary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForBackgroundTertiaryForIdx3  = valueHolderForBackgroundTertiary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForBackgroundTertiaryForIdx3)
        }
        const valueHolderForBackgroundFourth  = value.backgroundFourth
        if (valueHolderForBackgroundFourth instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForBackgroundFourthForIdx0  = valueHolderForBackgroundFourth as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForBackgroundFourthForIdx0))
        } else if (valueHolderForBackgroundFourth instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForBackgroundFourthForIdx1  = valueHolderForBackgroundFourth as number
            valueSerializer.writeNumber(valueHolderForBackgroundFourthForIdx1)
        } else if (valueHolderForBackgroundFourth instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForBackgroundFourthForIdx2  = valueHolderForBackgroundFourth as string
            valueSerializer.writeString(valueHolderForBackgroundFourthForIdx2)
        } else if (valueHolderForBackgroundFourth instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForBackgroundFourthForIdx3  = valueHolderForBackgroundFourth as Resource
            Resource_serializer.write(valueSerializer, valueHolderForBackgroundFourthForIdx3)
        }
        const valueHolderForBackgroundEmphasize  = value.backgroundEmphasize
        if (valueHolderForBackgroundEmphasize instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForBackgroundEmphasizeForIdx0  = valueHolderForBackgroundEmphasize as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForBackgroundEmphasizeForIdx0))
        } else if (valueHolderForBackgroundEmphasize instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForBackgroundEmphasizeForIdx1  = valueHolderForBackgroundEmphasize as number
            valueSerializer.writeNumber(valueHolderForBackgroundEmphasizeForIdx1)
        } else if (valueHolderForBackgroundEmphasize instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForBackgroundEmphasizeForIdx2  = valueHolderForBackgroundEmphasize as string
            valueSerializer.writeString(valueHolderForBackgroundEmphasizeForIdx2)
        } else if (valueHolderForBackgroundEmphasize instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForBackgroundEmphasizeForIdx3  = valueHolderForBackgroundEmphasize as Resource
            Resource_serializer.write(valueSerializer, valueHolderForBackgroundEmphasizeForIdx3)
        }
        const valueHolderForCompForegroundPrimary  = value.compForegroundPrimary
        if (valueHolderForCompForegroundPrimary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompForegroundPrimaryForIdx0  = valueHolderForCompForegroundPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompForegroundPrimaryForIdx0))
        } else if (valueHolderForCompForegroundPrimary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompForegroundPrimaryForIdx1  = valueHolderForCompForegroundPrimary as number
            valueSerializer.writeNumber(valueHolderForCompForegroundPrimaryForIdx1)
        } else if (valueHolderForCompForegroundPrimary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompForegroundPrimaryForIdx2  = valueHolderForCompForegroundPrimary as string
            valueSerializer.writeString(valueHolderForCompForegroundPrimaryForIdx2)
        } else if (valueHolderForCompForegroundPrimary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompForegroundPrimaryForIdx3  = valueHolderForCompForegroundPrimary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompForegroundPrimaryForIdx3)
        }
        const valueHolderForCompBackgroundPrimary  = value.compBackgroundPrimary
        if (valueHolderForCompBackgroundPrimary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompBackgroundPrimaryForIdx0  = valueHolderForCompBackgroundPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompBackgroundPrimaryForIdx0))
        } else if (valueHolderForCompBackgroundPrimary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompBackgroundPrimaryForIdx1  = valueHolderForCompBackgroundPrimary as number
            valueSerializer.writeNumber(valueHolderForCompBackgroundPrimaryForIdx1)
        } else if (valueHolderForCompBackgroundPrimary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompBackgroundPrimaryForIdx2  = valueHolderForCompBackgroundPrimary as string
            valueSerializer.writeString(valueHolderForCompBackgroundPrimaryForIdx2)
        } else if (valueHolderForCompBackgroundPrimary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompBackgroundPrimaryForIdx3  = valueHolderForCompBackgroundPrimary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompBackgroundPrimaryForIdx3)
        }
        const valueHolderForCompBackgroundPrimaryTran  = value.compBackgroundPrimaryTran
        if (valueHolderForCompBackgroundPrimaryTran instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompBackgroundPrimaryTranForIdx0  = valueHolderForCompBackgroundPrimaryTran as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompBackgroundPrimaryTranForIdx0))
        } else if (valueHolderForCompBackgroundPrimaryTran instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompBackgroundPrimaryTranForIdx1  = valueHolderForCompBackgroundPrimaryTran as number
            valueSerializer.writeNumber(valueHolderForCompBackgroundPrimaryTranForIdx1)
        } else if (valueHolderForCompBackgroundPrimaryTran instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompBackgroundPrimaryTranForIdx2  = valueHolderForCompBackgroundPrimaryTran as string
            valueSerializer.writeString(valueHolderForCompBackgroundPrimaryTranForIdx2)
        } else if (valueHolderForCompBackgroundPrimaryTran instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompBackgroundPrimaryTranForIdx3  = valueHolderForCompBackgroundPrimaryTran as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompBackgroundPrimaryTranForIdx3)
        }
        const valueHolderForCompBackgroundPrimaryContrary  = value.compBackgroundPrimaryContrary
        if (valueHolderForCompBackgroundPrimaryContrary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompBackgroundPrimaryContraryForIdx0  = valueHolderForCompBackgroundPrimaryContrary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompBackgroundPrimaryContraryForIdx0))
        } else if (valueHolderForCompBackgroundPrimaryContrary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompBackgroundPrimaryContraryForIdx1  = valueHolderForCompBackgroundPrimaryContrary as number
            valueSerializer.writeNumber(valueHolderForCompBackgroundPrimaryContraryForIdx1)
        } else if (valueHolderForCompBackgroundPrimaryContrary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompBackgroundPrimaryContraryForIdx2  = valueHolderForCompBackgroundPrimaryContrary as string
            valueSerializer.writeString(valueHolderForCompBackgroundPrimaryContraryForIdx2)
        } else if (valueHolderForCompBackgroundPrimaryContrary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompBackgroundPrimaryContraryForIdx3  = valueHolderForCompBackgroundPrimaryContrary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompBackgroundPrimaryContraryForIdx3)
        }
        const valueHolderForCompBackgroundGray  = value.compBackgroundGray
        if (valueHolderForCompBackgroundGray instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompBackgroundGrayForIdx0  = valueHolderForCompBackgroundGray as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompBackgroundGrayForIdx0))
        } else if (valueHolderForCompBackgroundGray instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompBackgroundGrayForIdx1  = valueHolderForCompBackgroundGray as number
            valueSerializer.writeNumber(valueHolderForCompBackgroundGrayForIdx1)
        } else if (valueHolderForCompBackgroundGray instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompBackgroundGrayForIdx2  = valueHolderForCompBackgroundGray as string
            valueSerializer.writeString(valueHolderForCompBackgroundGrayForIdx2)
        } else if (valueHolderForCompBackgroundGray instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompBackgroundGrayForIdx3  = valueHolderForCompBackgroundGray as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompBackgroundGrayForIdx3)
        }
        const valueHolderForCompBackgroundSecondary  = value.compBackgroundSecondary
        if (valueHolderForCompBackgroundSecondary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompBackgroundSecondaryForIdx0  = valueHolderForCompBackgroundSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompBackgroundSecondaryForIdx0))
        } else if (valueHolderForCompBackgroundSecondary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompBackgroundSecondaryForIdx1  = valueHolderForCompBackgroundSecondary as number
            valueSerializer.writeNumber(valueHolderForCompBackgroundSecondaryForIdx1)
        } else if (valueHolderForCompBackgroundSecondary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompBackgroundSecondaryForIdx2  = valueHolderForCompBackgroundSecondary as string
            valueSerializer.writeString(valueHolderForCompBackgroundSecondaryForIdx2)
        } else if (valueHolderForCompBackgroundSecondary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompBackgroundSecondaryForIdx3  = valueHolderForCompBackgroundSecondary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompBackgroundSecondaryForIdx3)
        }
        const valueHolderForCompBackgroundTertiary  = value.compBackgroundTertiary
        if (valueHolderForCompBackgroundTertiary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompBackgroundTertiaryForIdx0  = valueHolderForCompBackgroundTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompBackgroundTertiaryForIdx0))
        } else if (valueHolderForCompBackgroundTertiary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompBackgroundTertiaryForIdx1  = valueHolderForCompBackgroundTertiary as number
            valueSerializer.writeNumber(valueHolderForCompBackgroundTertiaryForIdx1)
        } else if (valueHolderForCompBackgroundTertiary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompBackgroundTertiaryForIdx2  = valueHolderForCompBackgroundTertiary as string
            valueSerializer.writeString(valueHolderForCompBackgroundTertiaryForIdx2)
        } else if (valueHolderForCompBackgroundTertiary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompBackgroundTertiaryForIdx3  = valueHolderForCompBackgroundTertiary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompBackgroundTertiaryForIdx3)
        }
        const valueHolderForCompBackgroundEmphasize  = value.compBackgroundEmphasize
        if (valueHolderForCompBackgroundEmphasize instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompBackgroundEmphasizeForIdx0  = valueHolderForCompBackgroundEmphasize as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompBackgroundEmphasizeForIdx0))
        } else if (valueHolderForCompBackgroundEmphasize instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompBackgroundEmphasizeForIdx1  = valueHolderForCompBackgroundEmphasize as number
            valueSerializer.writeNumber(valueHolderForCompBackgroundEmphasizeForIdx1)
        } else if (valueHolderForCompBackgroundEmphasize instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompBackgroundEmphasizeForIdx2  = valueHolderForCompBackgroundEmphasize as string
            valueSerializer.writeString(valueHolderForCompBackgroundEmphasizeForIdx2)
        } else if (valueHolderForCompBackgroundEmphasize instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompBackgroundEmphasizeForIdx3  = valueHolderForCompBackgroundEmphasize as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompBackgroundEmphasizeForIdx3)
        }
        const valueHolderForCompBackgroundNeutral  = value.compBackgroundNeutral
        if (valueHolderForCompBackgroundNeutral instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompBackgroundNeutralForIdx0  = valueHolderForCompBackgroundNeutral as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompBackgroundNeutralForIdx0))
        } else if (valueHolderForCompBackgroundNeutral instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompBackgroundNeutralForIdx1  = valueHolderForCompBackgroundNeutral as number
            valueSerializer.writeNumber(valueHolderForCompBackgroundNeutralForIdx1)
        } else if (valueHolderForCompBackgroundNeutral instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompBackgroundNeutralForIdx2  = valueHolderForCompBackgroundNeutral as string
            valueSerializer.writeString(valueHolderForCompBackgroundNeutralForIdx2)
        } else if (valueHolderForCompBackgroundNeutral instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompBackgroundNeutralForIdx3  = valueHolderForCompBackgroundNeutral as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompBackgroundNeutralForIdx3)
        }
        const valueHolderForCompEmphasizeSecondary  = value.compEmphasizeSecondary
        if (valueHolderForCompEmphasizeSecondary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompEmphasizeSecondaryForIdx0  = valueHolderForCompEmphasizeSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompEmphasizeSecondaryForIdx0))
        } else if (valueHolderForCompEmphasizeSecondary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompEmphasizeSecondaryForIdx1  = valueHolderForCompEmphasizeSecondary as number
            valueSerializer.writeNumber(valueHolderForCompEmphasizeSecondaryForIdx1)
        } else if (valueHolderForCompEmphasizeSecondary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompEmphasizeSecondaryForIdx2  = valueHolderForCompEmphasizeSecondary as string
            valueSerializer.writeString(valueHolderForCompEmphasizeSecondaryForIdx2)
        } else if (valueHolderForCompEmphasizeSecondary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompEmphasizeSecondaryForIdx3  = valueHolderForCompEmphasizeSecondary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompEmphasizeSecondaryForIdx3)
        }
        const valueHolderForCompEmphasizeTertiary  = value.compEmphasizeTertiary
        if (valueHolderForCompEmphasizeTertiary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompEmphasizeTertiaryForIdx0  = valueHolderForCompEmphasizeTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompEmphasizeTertiaryForIdx0))
        } else if (valueHolderForCompEmphasizeTertiary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompEmphasizeTertiaryForIdx1  = valueHolderForCompEmphasizeTertiary as number
            valueSerializer.writeNumber(valueHolderForCompEmphasizeTertiaryForIdx1)
        } else if (valueHolderForCompEmphasizeTertiary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompEmphasizeTertiaryForIdx2  = valueHolderForCompEmphasizeTertiary as string
            valueSerializer.writeString(valueHolderForCompEmphasizeTertiaryForIdx2)
        } else if (valueHolderForCompEmphasizeTertiary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompEmphasizeTertiaryForIdx3  = valueHolderForCompEmphasizeTertiary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompEmphasizeTertiaryForIdx3)
        }
        const valueHolderForCompDivider  = value.compDivider
        if (valueHolderForCompDivider instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompDividerForIdx0  = valueHolderForCompDivider as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompDividerForIdx0))
        } else if (valueHolderForCompDivider instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompDividerForIdx1  = valueHolderForCompDivider as number
            valueSerializer.writeNumber(valueHolderForCompDividerForIdx1)
        } else if (valueHolderForCompDivider instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompDividerForIdx2  = valueHolderForCompDivider as string
            valueSerializer.writeString(valueHolderForCompDividerForIdx2)
        } else if (valueHolderForCompDivider instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompDividerForIdx3  = valueHolderForCompDivider as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompDividerForIdx3)
        }
        const valueHolderForCompCommonContrary  = value.compCommonContrary
        if (valueHolderForCompCommonContrary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompCommonContraryForIdx0  = valueHolderForCompCommonContrary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompCommonContraryForIdx0))
        } else if (valueHolderForCompCommonContrary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompCommonContraryForIdx1  = valueHolderForCompCommonContrary as number
            valueSerializer.writeNumber(valueHolderForCompCommonContraryForIdx1)
        } else if (valueHolderForCompCommonContrary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompCommonContraryForIdx2  = valueHolderForCompCommonContrary as string
            valueSerializer.writeString(valueHolderForCompCommonContraryForIdx2)
        } else if (valueHolderForCompCommonContrary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompCommonContraryForIdx3  = valueHolderForCompCommonContrary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompCommonContraryForIdx3)
        }
        const valueHolderForCompBackgroundFocus  = value.compBackgroundFocus
        if (valueHolderForCompBackgroundFocus instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompBackgroundFocusForIdx0  = valueHolderForCompBackgroundFocus as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompBackgroundFocusForIdx0))
        } else if (valueHolderForCompBackgroundFocus instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompBackgroundFocusForIdx1  = valueHolderForCompBackgroundFocus as number
            valueSerializer.writeNumber(valueHolderForCompBackgroundFocusForIdx1)
        } else if (valueHolderForCompBackgroundFocus instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompBackgroundFocusForIdx2  = valueHolderForCompBackgroundFocus as string
            valueSerializer.writeString(valueHolderForCompBackgroundFocusForIdx2)
        } else if (valueHolderForCompBackgroundFocus instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompBackgroundFocusForIdx3  = valueHolderForCompBackgroundFocus as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompBackgroundFocusForIdx3)
        }
        const valueHolderForCompFocusedPrimary  = value.compFocusedPrimary
        if (valueHolderForCompFocusedPrimary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompFocusedPrimaryForIdx0  = valueHolderForCompFocusedPrimary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompFocusedPrimaryForIdx0))
        } else if (valueHolderForCompFocusedPrimary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompFocusedPrimaryForIdx1  = valueHolderForCompFocusedPrimary as number
            valueSerializer.writeNumber(valueHolderForCompFocusedPrimaryForIdx1)
        } else if (valueHolderForCompFocusedPrimary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompFocusedPrimaryForIdx2  = valueHolderForCompFocusedPrimary as string
            valueSerializer.writeString(valueHolderForCompFocusedPrimaryForIdx2)
        } else if (valueHolderForCompFocusedPrimary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompFocusedPrimaryForIdx3  = valueHolderForCompFocusedPrimary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompFocusedPrimaryForIdx3)
        }
        const valueHolderForCompFocusedSecondary  = value.compFocusedSecondary
        if (valueHolderForCompFocusedSecondary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompFocusedSecondaryForIdx0  = valueHolderForCompFocusedSecondary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompFocusedSecondaryForIdx0))
        } else if (valueHolderForCompFocusedSecondary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompFocusedSecondaryForIdx1  = valueHolderForCompFocusedSecondary as number
            valueSerializer.writeNumber(valueHolderForCompFocusedSecondaryForIdx1)
        } else if (valueHolderForCompFocusedSecondary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompFocusedSecondaryForIdx2  = valueHolderForCompFocusedSecondary as string
            valueSerializer.writeString(valueHolderForCompFocusedSecondaryForIdx2)
        } else if (valueHolderForCompFocusedSecondary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompFocusedSecondaryForIdx3  = valueHolderForCompFocusedSecondary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompFocusedSecondaryForIdx3)
        }
        const valueHolderForCompFocusedTertiary  = value.compFocusedTertiary
        if (valueHolderForCompFocusedTertiary instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCompFocusedTertiaryForIdx0  = valueHolderForCompFocusedTertiary as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCompFocusedTertiaryForIdx0))
        } else if (valueHolderForCompFocusedTertiary instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCompFocusedTertiaryForIdx1  = valueHolderForCompFocusedTertiary as number
            valueSerializer.writeNumber(valueHolderForCompFocusedTertiaryForIdx1)
        } else if (valueHolderForCompFocusedTertiary instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForCompFocusedTertiaryForIdx2  = valueHolderForCompFocusedTertiary as string
            valueSerializer.writeString(valueHolderForCompFocusedTertiaryForIdx2)
        } else if (valueHolderForCompFocusedTertiary instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForCompFocusedTertiaryForIdx3  = valueHolderForCompFocusedTertiary as Resource
            Resource_serializer.write(valueSerializer, valueHolderForCompFocusedTertiaryForIdx3)
        }
        const valueHolderForInteractiveHover  = value.interactiveHover
        if (valueHolderForInteractiveHover instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForInteractiveHoverForIdx0  = valueHolderForInteractiveHover as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForInteractiveHoverForIdx0))
        } else if (valueHolderForInteractiveHover instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForInteractiveHoverForIdx1  = valueHolderForInteractiveHover as number
            valueSerializer.writeNumber(valueHolderForInteractiveHoverForIdx1)
        } else if (valueHolderForInteractiveHover instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForInteractiveHoverForIdx2  = valueHolderForInteractiveHover as string
            valueSerializer.writeString(valueHolderForInteractiveHoverForIdx2)
        } else if (valueHolderForInteractiveHover instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForInteractiveHoverForIdx3  = valueHolderForInteractiveHover as Resource
            Resource_serializer.write(valueSerializer, valueHolderForInteractiveHoverForIdx3)
        }
        const valueHolderForInteractivePressed  = value.interactivePressed
        if (valueHolderForInteractivePressed instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForInteractivePressedForIdx0  = valueHolderForInteractivePressed as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForInteractivePressedForIdx0))
        } else if (valueHolderForInteractivePressed instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForInteractivePressedForIdx1  = valueHolderForInteractivePressed as number
            valueSerializer.writeNumber(valueHolderForInteractivePressedForIdx1)
        } else if (valueHolderForInteractivePressed instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForInteractivePressedForIdx2  = valueHolderForInteractivePressed as string
            valueSerializer.writeString(valueHolderForInteractivePressedForIdx2)
        } else if (valueHolderForInteractivePressed instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForInteractivePressedForIdx3  = valueHolderForInteractivePressed as Resource
            Resource_serializer.write(valueSerializer, valueHolderForInteractivePressedForIdx3)
        }
        const valueHolderForInteractiveFocus  = value.interactiveFocus
        if (valueHolderForInteractiveFocus instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForInteractiveFocusForIdx0  = valueHolderForInteractiveFocus as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForInteractiveFocusForIdx0))
        } else if (valueHolderForInteractiveFocus instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForInteractiveFocusForIdx1  = valueHolderForInteractiveFocus as number
            valueSerializer.writeNumber(valueHolderForInteractiveFocusForIdx1)
        } else if (valueHolderForInteractiveFocus instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForInteractiveFocusForIdx2  = valueHolderForInteractiveFocus as string
            valueSerializer.writeString(valueHolderForInteractiveFocusForIdx2)
        } else if (valueHolderForInteractiveFocus instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForInteractiveFocusForIdx3  = valueHolderForInteractiveFocus as Resource
            Resource_serializer.write(valueSerializer, valueHolderForInteractiveFocusForIdx3)
        }
        const valueHolderForInteractiveActive  = value.interactiveActive
        if (valueHolderForInteractiveActive instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForInteractiveActiveForIdx0  = valueHolderForInteractiveActive as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForInteractiveActiveForIdx0))
        } else if (valueHolderForInteractiveActive instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForInteractiveActiveForIdx1  = valueHolderForInteractiveActive as number
            valueSerializer.writeNumber(valueHolderForInteractiveActiveForIdx1)
        } else if (valueHolderForInteractiveActive instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForInteractiveActiveForIdx2  = valueHolderForInteractiveActive as string
            valueSerializer.writeString(valueHolderForInteractiveActiveForIdx2)
        } else if (valueHolderForInteractiveActive instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForInteractiveActiveForIdx3  = valueHolderForInteractiveActive as Resource
            Resource_serializer.write(valueSerializer, valueHolderForInteractiveActiveForIdx3)
        }
        const valueHolderForInteractiveSelect  = value.interactiveSelect
        if (valueHolderForInteractiveSelect instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForInteractiveSelectForIdx0  = valueHolderForInteractiveSelect as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForInteractiveSelectForIdx0))
        } else if (valueHolderForInteractiveSelect instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForInteractiveSelectForIdx1  = valueHolderForInteractiveSelect as number
            valueSerializer.writeNumber(valueHolderForInteractiveSelectForIdx1)
        } else if (valueHolderForInteractiveSelect instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForInteractiveSelectForIdx2  = valueHolderForInteractiveSelect as string
            valueSerializer.writeString(valueHolderForInteractiveSelectForIdx2)
        } else if (valueHolderForInteractiveSelect instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForInteractiveSelectForIdx3  = valueHolderForInteractiveSelect as Resource
            Resource_serializer.write(valueSerializer, valueHolderForInteractiveSelectForIdx3)
        }
        const valueHolderForInteractiveClick  = value.interactiveClick
        if (valueHolderForInteractiveClick instanceof Color) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForInteractiveClickForIdx0  = valueHolderForInteractiveClick as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForInteractiveClickForIdx0))
        } else if (valueHolderForInteractiveClick instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForInteractiveClickForIdx1  = valueHolderForInteractiveClick as number
            valueSerializer.writeNumber(valueHolderForInteractiveClickForIdx1)
        } else if (valueHolderForInteractiveClick instanceof string) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForInteractiveClickForIdx2  = valueHolderForInteractiveClick as string
            valueSerializer.writeString(valueHolderForInteractiveClickForIdx2)
        } else if (valueHolderForInteractiveClick instanceof Resource) {
            valueSerializer.writeInt8((3).toChar())
            const valueHolderForInteractiveClickForIdx3  = valueHolderForInteractiveClick as Resource
            Resource_serializer.write(valueSerializer, valueHolderForInteractiveClickForIdx3)
        }
    }
    public static read(buffer: DeserializerBase): Colors {
        let valueDeserializer : DeserializerBase = buffer
        const brandTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let brandTmpBuf : Color | number | string | Resource | undefined
        if (brandTmpBufUnionSelector == (0).toChar()) {
            brandTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (brandTmpBufUnionSelector == (1).toChar()) {
            brandTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (brandTmpBufUnionSelector == (2).toChar()) {
            brandTmpBuf = (valueDeserializer.readString() as string)
        } else if (brandTmpBufUnionSelector == (3).toChar()) {
            brandTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for brandTmpBuf has to be chosen through deserialisation.")
        }
        const brandTmpResult : ResourceColor = (brandTmpBuf as Color | number | string | Resource)
        const warningTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let warningTmpBuf : Color | number | string | Resource | undefined
        if (warningTmpBufUnionSelector == (0).toChar()) {
            warningTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (warningTmpBufUnionSelector == (1).toChar()) {
            warningTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (warningTmpBufUnionSelector == (2).toChar()) {
            warningTmpBuf = (valueDeserializer.readString() as string)
        } else if (warningTmpBufUnionSelector == (3).toChar()) {
            warningTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for warningTmpBuf has to be chosen through deserialisation.")
        }
        const warningTmpResult : ResourceColor = (warningTmpBuf as Color | number | string | Resource)
        const alertTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let alertTmpBuf : Color | number | string | Resource | undefined
        if (alertTmpBufUnionSelector == (0).toChar()) {
            alertTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (alertTmpBufUnionSelector == (1).toChar()) {
            alertTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (alertTmpBufUnionSelector == (2).toChar()) {
            alertTmpBuf = (valueDeserializer.readString() as string)
        } else if (alertTmpBufUnionSelector == (3).toChar()) {
            alertTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for alertTmpBuf has to be chosen through deserialisation.")
        }
        const alertTmpResult : ResourceColor = (alertTmpBuf as Color | number | string | Resource)
        const confirmTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let confirmTmpBuf : Color | number | string | Resource | undefined
        if (confirmTmpBufUnionSelector == (0).toChar()) {
            confirmTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (confirmTmpBufUnionSelector == (1).toChar()) {
            confirmTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (confirmTmpBufUnionSelector == (2).toChar()) {
            confirmTmpBuf = (valueDeserializer.readString() as string)
        } else if (confirmTmpBufUnionSelector == (3).toChar()) {
            confirmTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for confirmTmpBuf has to be chosen through deserialisation.")
        }
        const confirmTmpResult : ResourceColor = (confirmTmpBuf as Color | number | string | Resource)
        const fontPrimaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let fontPrimaryTmpBuf : Color | number | string | Resource | undefined
        if (fontPrimaryTmpBufUnionSelector == (0).toChar()) {
            fontPrimaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (fontPrimaryTmpBufUnionSelector == (1).toChar()) {
            fontPrimaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (fontPrimaryTmpBufUnionSelector == (2).toChar()) {
            fontPrimaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (fontPrimaryTmpBufUnionSelector == (3).toChar()) {
            fontPrimaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for fontPrimaryTmpBuf has to be chosen through deserialisation.")
        }
        const fontPrimaryTmpResult : ResourceColor = (fontPrimaryTmpBuf as Color | number | string | Resource)
        const fontSecondaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let fontSecondaryTmpBuf : Color | number | string | Resource | undefined
        if (fontSecondaryTmpBufUnionSelector == (0).toChar()) {
            fontSecondaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (fontSecondaryTmpBufUnionSelector == (1).toChar()) {
            fontSecondaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (fontSecondaryTmpBufUnionSelector == (2).toChar()) {
            fontSecondaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (fontSecondaryTmpBufUnionSelector == (3).toChar()) {
            fontSecondaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for fontSecondaryTmpBuf has to be chosen through deserialisation.")
        }
        const fontSecondaryTmpResult : ResourceColor = (fontSecondaryTmpBuf as Color | number | string | Resource)
        const fontTertiaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let fontTertiaryTmpBuf : Color | number | string | Resource | undefined
        if (fontTertiaryTmpBufUnionSelector == (0).toChar()) {
            fontTertiaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (fontTertiaryTmpBufUnionSelector == (1).toChar()) {
            fontTertiaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (fontTertiaryTmpBufUnionSelector == (2).toChar()) {
            fontTertiaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (fontTertiaryTmpBufUnionSelector == (3).toChar()) {
            fontTertiaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for fontTertiaryTmpBuf has to be chosen through deserialisation.")
        }
        const fontTertiaryTmpResult : ResourceColor = (fontTertiaryTmpBuf as Color | number | string | Resource)
        const fontFourthTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let fontFourthTmpBuf : Color | number | string | Resource | undefined
        if (fontFourthTmpBufUnionSelector == (0).toChar()) {
            fontFourthTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (fontFourthTmpBufUnionSelector == (1).toChar()) {
            fontFourthTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (fontFourthTmpBufUnionSelector == (2).toChar()) {
            fontFourthTmpBuf = (valueDeserializer.readString() as string)
        } else if (fontFourthTmpBufUnionSelector == (3).toChar()) {
            fontFourthTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for fontFourthTmpBuf has to be chosen through deserialisation.")
        }
        const fontFourthTmpResult : ResourceColor = (fontFourthTmpBuf as Color | number | string | Resource)
        const fontEmphasizeTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let fontEmphasizeTmpBuf : Color | number | string | Resource | undefined
        if (fontEmphasizeTmpBufUnionSelector == (0).toChar()) {
            fontEmphasizeTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (fontEmphasizeTmpBufUnionSelector == (1).toChar()) {
            fontEmphasizeTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (fontEmphasizeTmpBufUnionSelector == (2).toChar()) {
            fontEmphasizeTmpBuf = (valueDeserializer.readString() as string)
        } else if (fontEmphasizeTmpBufUnionSelector == (3).toChar()) {
            fontEmphasizeTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for fontEmphasizeTmpBuf has to be chosen through deserialisation.")
        }
        const fontEmphasizeTmpResult : ResourceColor = (fontEmphasizeTmpBuf as Color | number | string | Resource)
        const fontOnPrimaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let fontOnPrimaryTmpBuf : Color | number | string | Resource | undefined
        if (fontOnPrimaryTmpBufUnionSelector == (0).toChar()) {
            fontOnPrimaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (fontOnPrimaryTmpBufUnionSelector == (1).toChar()) {
            fontOnPrimaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (fontOnPrimaryTmpBufUnionSelector == (2).toChar()) {
            fontOnPrimaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (fontOnPrimaryTmpBufUnionSelector == (3).toChar()) {
            fontOnPrimaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for fontOnPrimaryTmpBuf has to be chosen through deserialisation.")
        }
        const fontOnPrimaryTmpResult : ResourceColor = (fontOnPrimaryTmpBuf as Color | number | string | Resource)
        const fontOnSecondaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let fontOnSecondaryTmpBuf : Color | number | string | Resource | undefined
        if (fontOnSecondaryTmpBufUnionSelector == (0).toChar()) {
            fontOnSecondaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (fontOnSecondaryTmpBufUnionSelector == (1).toChar()) {
            fontOnSecondaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (fontOnSecondaryTmpBufUnionSelector == (2).toChar()) {
            fontOnSecondaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (fontOnSecondaryTmpBufUnionSelector == (3).toChar()) {
            fontOnSecondaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for fontOnSecondaryTmpBuf has to be chosen through deserialisation.")
        }
        const fontOnSecondaryTmpResult : ResourceColor = (fontOnSecondaryTmpBuf as Color | number | string | Resource)
        const fontOnTertiaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let fontOnTertiaryTmpBuf : Color | number | string | Resource | undefined
        if (fontOnTertiaryTmpBufUnionSelector == (0).toChar()) {
            fontOnTertiaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (fontOnTertiaryTmpBufUnionSelector == (1).toChar()) {
            fontOnTertiaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (fontOnTertiaryTmpBufUnionSelector == (2).toChar()) {
            fontOnTertiaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (fontOnTertiaryTmpBufUnionSelector == (3).toChar()) {
            fontOnTertiaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for fontOnTertiaryTmpBuf has to be chosen through deserialisation.")
        }
        const fontOnTertiaryTmpResult : ResourceColor = (fontOnTertiaryTmpBuf as Color | number | string | Resource)
        const fontOnFourthTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let fontOnFourthTmpBuf : Color | number | string | Resource | undefined
        if (fontOnFourthTmpBufUnionSelector == (0).toChar()) {
            fontOnFourthTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (fontOnFourthTmpBufUnionSelector == (1).toChar()) {
            fontOnFourthTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (fontOnFourthTmpBufUnionSelector == (2).toChar()) {
            fontOnFourthTmpBuf = (valueDeserializer.readString() as string)
        } else if (fontOnFourthTmpBufUnionSelector == (3).toChar()) {
            fontOnFourthTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for fontOnFourthTmpBuf has to be chosen through deserialisation.")
        }
        const fontOnFourthTmpResult : ResourceColor = (fontOnFourthTmpBuf as Color | number | string | Resource)
        const iconPrimaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let iconPrimaryTmpBuf : Color | number | string | Resource | undefined
        if (iconPrimaryTmpBufUnionSelector == (0).toChar()) {
            iconPrimaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (iconPrimaryTmpBufUnionSelector == (1).toChar()) {
            iconPrimaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (iconPrimaryTmpBufUnionSelector == (2).toChar()) {
            iconPrimaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (iconPrimaryTmpBufUnionSelector == (3).toChar()) {
            iconPrimaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for iconPrimaryTmpBuf has to be chosen through deserialisation.")
        }
        const iconPrimaryTmpResult : ResourceColor = (iconPrimaryTmpBuf as Color | number | string | Resource)
        const iconSecondaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let iconSecondaryTmpBuf : Color | number | string | Resource | undefined
        if (iconSecondaryTmpBufUnionSelector == (0).toChar()) {
            iconSecondaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (iconSecondaryTmpBufUnionSelector == (1).toChar()) {
            iconSecondaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (iconSecondaryTmpBufUnionSelector == (2).toChar()) {
            iconSecondaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (iconSecondaryTmpBufUnionSelector == (3).toChar()) {
            iconSecondaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for iconSecondaryTmpBuf has to be chosen through deserialisation.")
        }
        const iconSecondaryTmpResult : ResourceColor = (iconSecondaryTmpBuf as Color | number | string | Resource)
        const iconTertiaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let iconTertiaryTmpBuf : Color | number | string | Resource | undefined
        if (iconTertiaryTmpBufUnionSelector == (0).toChar()) {
            iconTertiaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (iconTertiaryTmpBufUnionSelector == (1).toChar()) {
            iconTertiaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (iconTertiaryTmpBufUnionSelector == (2).toChar()) {
            iconTertiaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (iconTertiaryTmpBufUnionSelector == (3).toChar()) {
            iconTertiaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for iconTertiaryTmpBuf has to be chosen through deserialisation.")
        }
        const iconTertiaryTmpResult : ResourceColor = (iconTertiaryTmpBuf as Color | number | string | Resource)
        const iconFourthTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let iconFourthTmpBuf : Color | number | string | Resource | undefined
        if (iconFourthTmpBufUnionSelector == (0).toChar()) {
            iconFourthTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (iconFourthTmpBufUnionSelector == (1).toChar()) {
            iconFourthTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (iconFourthTmpBufUnionSelector == (2).toChar()) {
            iconFourthTmpBuf = (valueDeserializer.readString() as string)
        } else if (iconFourthTmpBufUnionSelector == (3).toChar()) {
            iconFourthTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for iconFourthTmpBuf has to be chosen through deserialisation.")
        }
        const iconFourthTmpResult : ResourceColor = (iconFourthTmpBuf as Color | number | string | Resource)
        const iconEmphasizeTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let iconEmphasizeTmpBuf : Color | number | string | Resource | undefined
        if (iconEmphasizeTmpBufUnionSelector == (0).toChar()) {
            iconEmphasizeTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (iconEmphasizeTmpBufUnionSelector == (1).toChar()) {
            iconEmphasizeTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (iconEmphasizeTmpBufUnionSelector == (2).toChar()) {
            iconEmphasizeTmpBuf = (valueDeserializer.readString() as string)
        } else if (iconEmphasizeTmpBufUnionSelector == (3).toChar()) {
            iconEmphasizeTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for iconEmphasizeTmpBuf has to be chosen through deserialisation.")
        }
        const iconEmphasizeTmpResult : ResourceColor = (iconEmphasizeTmpBuf as Color | number | string | Resource)
        const iconSubEmphasizeTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let iconSubEmphasizeTmpBuf : Color | number | string | Resource | undefined
        if (iconSubEmphasizeTmpBufUnionSelector == (0).toChar()) {
            iconSubEmphasizeTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (iconSubEmphasizeTmpBufUnionSelector == (1).toChar()) {
            iconSubEmphasizeTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (iconSubEmphasizeTmpBufUnionSelector == (2).toChar()) {
            iconSubEmphasizeTmpBuf = (valueDeserializer.readString() as string)
        } else if (iconSubEmphasizeTmpBufUnionSelector == (3).toChar()) {
            iconSubEmphasizeTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for iconSubEmphasizeTmpBuf has to be chosen through deserialisation.")
        }
        const iconSubEmphasizeTmpResult : ResourceColor = (iconSubEmphasizeTmpBuf as Color | number | string | Resource)
        const iconOnPrimaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let iconOnPrimaryTmpBuf : Color | number | string | Resource | undefined
        if (iconOnPrimaryTmpBufUnionSelector == (0).toChar()) {
            iconOnPrimaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (iconOnPrimaryTmpBufUnionSelector == (1).toChar()) {
            iconOnPrimaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (iconOnPrimaryTmpBufUnionSelector == (2).toChar()) {
            iconOnPrimaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (iconOnPrimaryTmpBufUnionSelector == (3).toChar()) {
            iconOnPrimaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for iconOnPrimaryTmpBuf has to be chosen through deserialisation.")
        }
        const iconOnPrimaryTmpResult : ResourceColor = (iconOnPrimaryTmpBuf as Color | number | string | Resource)
        const iconOnSecondaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let iconOnSecondaryTmpBuf : Color | number | string | Resource | undefined
        if (iconOnSecondaryTmpBufUnionSelector == (0).toChar()) {
            iconOnSecondaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (iconOnSecondaryTmpBufUnionSelector == (1).toChar()) {
            iconOnSecondaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (iconOnSecondaryTmpBufUnionSelector == (2).toChar()) {
            iconOnSecondaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (iconOnSecondaryTmpBufUnionSelector == (3).toChar()) {
            iconOnSecondaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for iconOnSecondaryTmpBuf has to be chosen through deserialisation.")
        }
        const iconOnSecondaryTmpResult : ResourceColor = (iconOnSecondaryTmpBuf as Color | number | string | Resource)
        const iconOnTertiaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let iconOnTertiaryTmpBuf : Color | number | string | Resource | undefined
        if (iconOnTertiaryTmpBufUnionSelector == (0).toChar()) {
            iconOnTertiaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (iconOnTertiaryTmpBufUnionSelector == (1).toChar()) {
            iconOnTertiaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (iconOnTertiaryTmpBufUnionSelector == (2).toChar()) {
            iconOnTertiaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (iconOnTertiaryTmpBufUnionSelector == (3).toChar()) {
            iconOnTertiaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for iconOnTertiaryTmpBuf has to be chosen through deserialisation.")
        }
        const iconOnTertiaryTmpResult : ResourceColor = (iconOnTertiaryTmpBuf as Color | number | string | Resource)
        const iconOnFourthTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let iconOnFourthTmpBuf : Color | number | string | Resource | undefined
        if (iconOnFourthTmpBufUnionSelector == (0).toChar()) {
            iconOnFourthTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (iconOnFourthTmpBufUnionSelector == (1).toChar()) {
            iconOnFourthTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (iconOnFourthTmpBufUnionSelector == (2).toChar()) {
            iconOnFourthTmpBuf = (valueDeserializer.readString() as string)
        } else if (iconOnFourthTmpBufUnionSelector == (3).toChar()) {
            iconOnFourthTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for iconOnFourthTmpBuf has to be chosen through deserialisation.")
        }
        const iconOnFourthTmpResult : ResourceColor = (iconOnFourthTmpBuf as Color | number | string | Resource)
        const backgroundPrimaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let backgroundPrimaryTmpBuf : Color | number | string | Resource | undefined
        if (backgroundPrimaryTmpBufUnionSelector == (0).toChar()) {
            backgroundPrimaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (backgroundPrimaryTmpBufUnionSelector == (1).toChar()) {
            backgroundPrimaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (backgroundPrimaryTmpBufUnionSelector == (2).toChar()) {
            backgroundPrimaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (backgroundPrimaryTmpBufUnionSelector == (3).toChar()) {
            backgroundPrimaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for backgroundPrimaryTmpBuf has to be chosen through deserialisation.")
        }
        const backgroundPrimaryTmpResult : ResourceColor = (backgroundPrimaryTmpBuf as Color | number | string | Resource)
        const backgroundSecondaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let backgroundSecondaryTmpBuf : Color | number | string | Resource | undefined
        if (backgroundSecondaryTmpBufUnionSelector == (0).toChar()) {
            backgroundSecondaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (backgroundSecondaryTmpBufUnionSelector == (1).toChar()) {
            backgroundSecondaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (backgroundSecondaryTmpBufUnionSelector == (2).toChar()) {
            backgroundSecondaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (backgroundSecondaryTmpBufUnionSelector == (3).toChar()) {
            backgroundSecondaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for backgroundSecondaryTmpBuf has to be chosen through deserialisation.")
        }
        const backgroundSecondaryTmpResult : ResourceColor = (backgroundSecondaryTmpBuf as Color | number | string | Resource)
        const backgroundTertiaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let backgroundTertiaryTmpBuf : Color | number | string | Resource | undefined
        if (backgroundTertiaryTmpBufUnionSelector == (0).toChar()) {
            backgroundTertiaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (backgroundTertiaryTmpBufUnionSelector == (1).toChar()) {
            backgroundTertiaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (backgroundTertiaryTmpBufUnionSelector == (2).toChar()) {
            backgroundTertiaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (backgroundTertiaryTmpBufUnionSelector == (3).toChar()) {
            backgroundTertiaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for backgroundTertiaryTmpBuf has to be chosen through deserialisation.")
        }
        const backgroundTertiaryTmpResult : ResourceColor = (backgroundTertiaryTmpBuf as Color | number | string | Resource)
        const backgroundFourthTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let backgroundFourthTmpBuf : Color | number | string | Resource | undefined
        if (backgroundFourthTmpBufUnionSelector == (0).toChar()) {
            backgroundFourthTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (backgroundFourthTmpBufUnionSelector == (1).toChar()) {
            backgroundFourthTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (backgroundFourthTmpBufUnionSelector == (2).toChar()) {
            backgroundFourthTmpBuf = (valueDeserializer.readString() as string)
        } else if (backgroundFourthTmpBufUnionSelector == (3).toChar()) {
            backgroundFourthTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for backgroundFourthTmpBuf has to be chosen through deserialisation.")
        }
        const backgroundFourthTmpResult : ResourceColor = (backgroundFourthTmpBuf as Color | number | string | Resource)
        const backgroundEmphasizeTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let backgroundEmphasizeTmpBuf : Color | number | string | Resource | undefined
        if (backgroundEmphasizeTmpBufUnionSelector == (0).toChar()) {
            backgroundEmphasizeTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (backgroundEmphasizeTmpBufUnionSelector == (1).toChar()) {
            backgroundEmphasizeTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (backgroundEmphasizeTmpBufUnionSelector == (2).toChar()) {
            backgroundEmphasizeTmpBuf = (valueDeserializer.readString() as string)
        } else if (backgroundEmphasizeTmpBufUnionSelector == (3).toChar()) {
            backgroundEmphasizeTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for backgroundEmphasizeTmpBuf has to be chosen through deserialisation.")
        }
        const backgroundEmphasizeTmpResult : ResourceColor = (backgroundEmphasizeTmpBuf as Color | number | string | Resource)
        const compForegroundPrimaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compForegroundPrimaryTmpBuf : Color | number | string | Resource | undefined
        if (compForegroundPrimaryTmpBufUnionSelector == (0).toChar()) {
            compForegroundPrimaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compForegroundPrimaryTmpBufUnionSelector == (1).toChar()) {
            compForegroundPrimaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compForegroundPrimaryTmpBufUnionSelector == (2).toChar()) {
            compForegroundPrimaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (compForegroundPrimaryTmpBufUnionSelector == (3).toChar()) {
            compForegroundPrimaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compForegroundPrimaryTmpBuf has to be chosen through deserialisation.")
        }
        const compForegroundPrimaryTmpResult : ResourceColor = (compForegroundPrimaryTmpBuf as Color | number | string | Resource)
        const compBackgroundPrimaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compBackgroundPrimaryTmpBuf : Color | number | string | Resource | undefined
        if (compBackgroundPrimaryTmpBufUnionSelector == (0).toChar()) {
            compBackgroundPrimaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compBackgroundPrimaryTmpBufUnionSelector == (1).toChar()) {
            compBackgroundPrimaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compBackgroundPrimaryTmpBufUnionSelector == (2).toChar()) {
            compBackgroundPrimaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (compBackgroundPrimaryTmpBufUnionSelector == (3).toChar()) {
            compBackgroundPrimaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compBackgroundPrimaryTmpBuf has to be chosen through deserialisation.")
        }
        const compBackgroundPrimaryTmpResult : ResourceColor = (compBackgroundPrimaryTmpBuf as Color | number | string | Resource)
        const compBackgroundPrimaryTranTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compBackgroundPrimaryTranTmpBuf : Color | number | string | Resource | undefined
        if (compBackgroundPrimaryTranTmpBufUnionSelector == (0).toChar()) {
            compBackgroundPrimaryTranTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compBackgroundPrimaryTranTmpBufUnionSelector == (1).toChar()) {
            compBackgroundPrimaryTranTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compBackgroundPrimaryTranTmpBufUnionSelector == (2).toChar()) {
            compBackgroundPrimaryTranTmpBuf = (valueDeserializer.readString() as string)
        } else if (compBackgroundPrimaryTranTmpBufUnionSelector == (3).toChar()) {
            compBackgroundPrimaryTranTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compBackgroundPrimaryTranTmpBuf has to be chosen through deserialisation.")
        }
        const compBackgroundPrimaryTranTmpResult : ResourceColor = (compBackgroundPrimaryTranTmpBuf as Color | number | string | Resource)
        const compBackgroundPrimaryContraryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compBackgroundPrimaryContraryTmpBuf : Color | number | string | Resource | undefined
        if (compBackgroundPrimaryContraryTmpBufUnionSelector == (0).toChar()) {
            compBackgroundPrimaryContraryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compBackgroundPrimaryContraryTmpBufUnionSelector == (1).toChar()) {
            compBackgroundPrimaryContraryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compBackgroundPrimaryContraryTmpBufUnionSelector == (2).toChar()) {
            compBackgroundPrimaryContraryTmpBuf = (valueDeserializer.readString() as string)
        } else if (compBackgroundPrimaryContraryTmpBufUnionSelector == (3).toChar()) {
            compBackgroundPrimaryContraryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compBackgroundPrimaryContraryTmpBuf has to be chosen through deserialisation.")
        }
        const compBackgroundPrimaryContraryTmpResult : ResourceColor = (compBackgroundPrimaryContraryTmpBuf as Color | number | string | Resource)
        const compBackgroundGrayTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compBackgroundGrayTmpBuf : Color | number | string | Resource | undefined
        if (compBackgroundGrayTmpBufUnionSelector == (0).toChar()) {
            compBackgroundGrayTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compBackgroundGrayTmpBufUnionSelector == (1).toChar()) {
            compBackgroundGrayTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compBackgroundGrayTmpBufUnionSelector == (2).toChar()) {
            compBackgroundGrayTmpBuf = (valueDeserializer.readString() as string)
        } else if (compBackgroundGrayTmpBufUnionSelector == (3).toChar()) {
            compBackgroundGrayTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compBackgroundGrayTmpBuf has to be chosen through deserialisation.")
        }
        const compBackgroundGrayTmpResult : ResourceColor = (compBackgroundGrayTmpBuf as Color | number | string | Resource)
        const compBackgroundSecondaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compBackgroundSecondaryTmpBuf : Color | number | string | Resource | undefined
        if (compBackgroundSecondaryTmpBufUnionSelector == (0).toChar()) {
            compBackgroundSecondaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compBackgroundSecondaryTmpBufUnionSelector == (1).toChar()) {
            compBackgroundSecondaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compBackgroundSecondaryTmpBufUnionSelector == (2).toChar()) {
            compBackgroundSecondaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (compBackgroundSecondaryTmpBufUnionSelector == (3).toChar()) {
            compBackgroundSecondaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compBackgroundSecondaryTmpBuf has to be chosen through deserialisation.")
        }
        const compBackgroundSecondaryTmpResult : ResourceColor = (compBackgroundSecondaryTmpBuf as Color | number | string | Resource)
        const compBackgroundTertiaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compBackgroundTertiaryTmpBuf : Color | number | string | Resource | undefined
        if (compBackgroundTertiaryTmpBufUnionSelector == (0).toChar()) {
            compBackgroundTertiaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compBackgroundTertiaryTmpBufUnionSelector == (1).toChar()) {
            compBackgroundTertiaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compBackgroundTertiaryTmpBufUnionSelector == (2).toChar()) {
            compBackgroundTertiaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (compBackgroundTertiaryTmpBufUnionSelector == (3).toChar()) {
            compBackgroundTertiaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compBackgroundTertiaryTmpBuf has to be chosen through deserialisation.")
        }
        const compBackgroundTertiaryTmpResult : ResourceColor = (compBackgroundTertiaryTmpBuf as Color | number | string | Resource)
        const compBackgroundEmphasizeTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compBackgroundEmphasizeTmpBuf : Color | number | string | Resource | undefined
        if (compBackgroundEmphasizeTmpBufUnionSelector == (0).toChar()) {
            compBackgroundEmphasizeTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compBackgroundEmphasizeTmpBufUnionSelector == (1).toChar()) {
            compBackgroundEmphasizeTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compBackgroundEmphasizeTmpBufUnionSelector == (2).toChar()) {
            compBackgroundEmphasizeTmpBuf = (valueDeserializer.readString() as string)
        } else if (compBackgroundEmphasizeTmpBufUnionSelector == (3).toChar()) {
            compBackgroundEmphasizeTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compBackgroundEmphasizeTmpBuf has to be chosen through deserialisation.")
        }
        const compBackgroundEmphasizeTmpResult : ResourceColor = (compBackgroundEmphasizeTmpBuf as Color | number | string | Resource)
        const compBackgroundNeutralTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compBackgroundNeutralTmpBuf : Color | number | string | Resource | undefined
        if (compBackgroundNeutralTmpBufUnionSelector == (0).toChar()) {
            compBackgroundNeutralTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compBackgroundNeutralTmpBufUnionSelector == (1).toChar()) {
            compBackgroundNeutralTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compBackgroundNeutralTmpBufUnionSelector == (2).toChar()) {
            compBackgroundNeutralTmpBuf = (valueDeserializer.readString() as string)
        } else if (compBackgroundNeutralTmpBufUnionSelector == (3).toChar()) {
            compBackgroundNeutralTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compBackgroundNeutralTmpBuf has to be chosen through deserialisation.")
        }
        const compBackgroundNeutralTmpResult : ResourceColor = (compBackgroundNeutralTmpBuf as Color | number | string | Resource)
        const compEmphasizeSecondaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compEmphasizeSecondaryTmpBuf : Color | number | string | Resource | undefined
        if (compEmphasizeSecondaryTmpBufUnionSelector == (0).toChar()) {
            compEmphasizeSecondaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compEmphasizeSecondaryTmpBufUnionSelector == (1).toChar()) {
            compEmphasizeSecondaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compEmphasizeSecondaryTmpBufUnionSelector == (2).toChar()) {
            compEmphasizeSecondaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (compEmphasizeSecondaryTmpBufUnionSelector == (3).toChar()) {
            compEmphasizeSecondaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compEmphasizeSecondaryTmpBuf has to be chosen through deserialisation.")
        }
        const compEmphasizeSecondaryTmpResult : ResourceColor = (compEmphasizeSecondaryTmpBuf as Color | number | string | Resource)
        const compEmphasizeTertiaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compEmphasizeTertiaryTmpBuf : Color | number | string | Resource | undefined
        if (compEmphasizeTertiaryTmpBufUnionSelector == (0).toChar()) {
            compEmphasizeTertiaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compEmphasizeTertiaryTmpBufUnionSelector == (1).toChar()) {
            compEmphasizeTertiaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compEmphasizeTertiaryTmpBufUnionSelector == (2).toChar()) {
            compEmphasizeTertiaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (compEmphasizeTertiaryTmpBufUnionSelector == (3).toChar()) {
            compEmphasizeTertiaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compEmphasizeTertiaryTmpBuf has to be chosen through deserialisation.")
        }
        const compEmphasizeTertiaryTmpResult : ResourceColor = (compEmphasizeTertiaryTmpBuf as Color | number | string | Resource)
        const compDividerTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compDividerTmpBuf : Color | number | string | Resource | undefined
        if (compDividerTmpBufUnionSelector == (0).toChar()) {
            compDividerTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compDividerTmpBufUnionSelector == (1).toChar()) {
            compDividerTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compDividerTmpBufUnionSelector == (2).toChar()) {
            compDividerTmpBuf = (valueDeserializer.readString() as string)
        } else if (compDividerTmpBufUnionSelector == (3).toChar()) {
            compDividerTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compDividerTmpBuf has to be chosen through deserialisation.")
        }
        const compDividerTmpResult : ResourceColor = (compDividerTmpBuf as Color | number | string | Resource)
        const compCommonContraryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compCommonContraryTmpBuf : Color | number | string | Resource | undefined
        if (compCommonContraryTmpBufUnionSelector == (0).toChar()) {
            compCommonContraryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compCommonContraryTmpBufUnionSelector == (1).toChar()) {
            compCommonContraryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compCommonContraryTmpBufUnionSelector == (2).toChar()) {
            compCommonContraryTmpBuf = (valueDeserializer.readString() as string)
        } else if (compCommonContraryTmpBufUnionSelector == (3).toChar()) {
            compCommonContraryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compCommonContraryTmpBuf has to be chosen through deserialisation.")
        }
        const compCommonContraryTmpResult : ResourceColor = (compCommonContraryTmpBuf as Color | number | string | Resource)
        const compBackgroundFocusTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compBackgroundFocusTmpBuf : Color | number | string | Resource | undefined
        if (compBackgroundFocusTmpBufUnionSelector == (0).toChar()) {
            compBackgroundFocusTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compBackgroundFocusTmpBufUnionSelector == (1).toChar()) {
            compBackgroundFocusTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compBackgroundFocusTmpBufUnionSelector == (2).toChar()) {
            compBackgroundFocusTmpBuf = (valueDeserializer.readString() as string)
        } else if (compBackgroundFocusTmpBufUnionSelector == (3).toChar()) {
            compBackgroundFocusTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compBackgroundFocusTmpBuf has to be chosen through deserialisation.")
        }
        const compBackgroundFocusTmpResult : ResourceColor = (compBackgroundFocusTmpBuf as Color | number | string | Resource)
        const compFocusedPrimaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compFocusedPrimaryTmpBuf : Color | number | string | Resource | undefined
        if (compFocusedPrimaryTmpBufUnionSelector == (0).toChar()) {
            compFocusedPrimaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compFocusedPrimaryTmpBufUnionSelector == (1).toChar()) {
            compFocusedPrimaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compFocusedPrimaryTmpBufUnionSelector == (2).toChar()) {
            compFocusedPrimaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (compFocusedPrimaryTmpBufUnionSelector == (3).toChar()) {
            compFocusedPrimaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compFocusedPrimaryTmpBuf has to be chosen through deserialisation.")
        }
        const compFocusedPrimaryTmpResult : ResourceColor = (compFocusedPrimaryTmpBuf as Color | number | string | Resource)
        const compFocusedSecondaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compFocusedSecondaryTmpBuf : Color | number | string | Resource | undefined
        if (compFocusedSecondaryTmpBufUnionSelector == (0).toChar()) {
            compFocusedSecondaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compFocusedSecondaryTmpBufUnionSelector == (1).toChar()) {
            compFocusedSecondaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compFocusedSecondaryTmpBufUnionSelector == (2).toChar()) {
            compFocusedSecondaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (compFocusedSecondaryTmpBufUnionSelector == (3).toChar()) {
            compFocusedSecondaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compFocusedSecondaryTmpBuf has to be chosen through deserialisation.")
        }
        const compFocusedSecondaryTmpResult : ResourceColor = (compFocusedSecondaryTmpBuf as Color | number | string | Resource)
        const compFocusedTertiaryTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let compFocusedTertiaryTmpBuf : Color | number | string | Resource | undefined
        if (compFocusedTertiaryTmpBufUnionSelector == (0).toChar()) {
            compFocusedTertiaryTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (compFocusedTertiaryTmpBufUnionSelector == (1).toChar()) {
            compFocusedTertiaryTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (compFocusedTertiaryTmpBufUnionSelector == (2).toChar()) {
            compFocusedTertiaryTmpBuf = (valueDeserializer.readString() as string)
        } else if (compFocusedTertiaryTmpBufUnionSelector == (3).toChar()) {
            compFocusedTertiaryTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for compFocusedTertiaryTmpBuf has to be chosen through deserialisation.")
        }
        const compFocusedTertiaryTmpResult : ResourceColor = (compFocusedTertiaryTmpBuf as Color | number | string | Resource)
        const interactiveHoverTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let interactiveHoverTmpBuf : Color | number | string | Resource | undefined
        if (interactiveHoverTmpBufUnionSelector == (0).toChar()) {
            interactiveHoverTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (interactiveHoverTmpBufUnionSelector == (1).toChar()) {
            interactiveHoverTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (interactiveHoverTmpBufUnionSelector == (2).toChar()) {
            interactiveHoverTmpBuf = (valueDeserializer.readString() as string)
        } else if (interactiveHoverTmpBufUnionSelector == (3).toChar()) {
            interactiveHoverTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for interactiveHoverTmpBuf has to be chosen through deserialisation.")
        }
        const interactiveHoverTmpResult : ResourceColor = (interactiveHoverTmpBuf as Color | number | string | Resource)
        const interactivePressedTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let interactivePressedTmpBuf : Color | number | string | Resource | undefined
        if (interactivePressedTmpBufUnionSelector == (0).toChar()) {
            interactivePressedTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (interactivePressedTmpBufUnionSelector == (1).toChar()) {
            interactivePressedTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (interactivePressedTmpBufUnionSelector == (2).toChar()) {
            interactivePressedTmpBuf = (valueDeserializer.readString() as string)
        } else if (interactivePressedTmpBufUnionSelector == (3).toChar()) {
            interactivePressedTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for interactivePressedTmpBuf has to be chosen through deserialisation.")
        }
        const interactivePressedTmpResult : ResourceColor = (interactivePressedTmpBuf as Color | number | string | Resource)
        const interactiveFocusTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let interactiveFocusTmpBuf : Color | number | string | Resource | undefined
        if (interactiveFocusTmpBufUnionSelector == (0).toChar()) {
            interactiveFocusTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (interactiveFocusTmpBufUnionSelector == (1).toChar()) {
            interactiveFocusTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (interactiveFocusTmpBufUnionSelector == (2).toChar()) {
            interactiveFocusTmpBuf = (valueDeserializer.readString() as string)
        } else if (interactiveFocusTmpBufUnionSelector == (3).toChar()) {
            interactiveFocusTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for interactiveFocusTmpBuf has to be chosen through deserialisation.")
        }
        const interactiveFocusTmpResult : ResourceColor = (interactiveFocusTmpBuf as Color | number | string | Resource)
        const interactiveActiveTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let interactiveActiveTmpBuf : Color | number | string | Resource | undefined
        if (interactiveActiveTmpBufUnionSelector == (0).toChar()) {
            interactiveActiveTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (interactiveActiveTmpBufUnionSelector == (1).toChar()) {
            interactiveActiveTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (interactiveActiveTmpBufUnionSelector == (2).toChar()) {
            interactiveActiveTmpBuf = (valueDeserializer.readString() as string)
        } else if (interactiveActiveTmpBufUnionSelector == (3).toChar()) {
            interactiveActiveTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for interactiveActiveTmpBuf has to be chosen through deserialisation.")
        }
        const interactiveActiveTmpResult : ResourceColor = (interactiveActiveTmpBuf as Color | number | string | Resource)
        const interactiveSelectTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let interactiveSelectTmpBuf : Color | number | string | Resource | undefined
        if (interactiveSelectTmpBufUnionSelector == (0).toChar()) {
            interactiveSelectTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (interactiveSelectTmpBufUnionSelector == (1).toChar()) {
            interactiveSelectTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (interactiveSelectTmpBufUnionSelector == (2).toChar()) {
            interactiveSelectTmpBuf = (valueDeserializer.readString() as string)
        } else if (interactiveSelectTmpBufUnionSelector == (3).toChar()) {
            interactiveSelectTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for interactiveSelectTmpBuf has to be chosen through deserialisation.")
        }
        const interactiveSelectTmpResult : ResourceColor = (interactiveSelectTmpBuf as Color | number | string | Resource)
        const interactiveClickTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let interactiveClickTmpBuf : Color | number | string | Resource | undefined
        if (interactiveClickTmpBufUnionSelector == (0).toChar()) {
            interactiveClickTmpBuf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        } else if (interactiveClickTmpBufUnionSelector == (1).toChar()) {
            interactiveClickTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (interactiveClickTmpBufUnionSelector == (2).toChar()) {
            interactiveClickTmpBuf = (valueDeserializer.readString() as string)
        } else if (interactiveClickTmpBufUnionSelector == (3).toChar()) {
            interactiveClickTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for interactiveClickTmpBuf has to be chosen through deserialisation.")
        }
        const interactiveClickTmpResult : ResourceColor = (interactiveClickTmpBuf as Color | number | string | Resource)
        let value : Colors = ({brand: brandTmpResult, warning: warningTmpResult, alert: alertTmpResult, confirm: confirmTmpResult, fontPrimary: fontPrimaryTmpResult, fontSecondary: fontSecondaryTmpResult, fontTertiary: fontTertiaryTmpResult, fontFourth: fontFourthTmpResult, fontEmphasize: fontEmphasizeTmpResult, fontOnPrimary: fontOnPrimaryTmpResult, fontOnSecondary: fontOnSecondaryTmpResult, fontOnTertiary: fontOnTertiaryTmpResult, fontOnFourth: fontOnFourthTmpResult, iconPrimary: iconPrimaryTmpResult, iconSecondary: iconSecondaryTmpResult, iconTertiary: iconTertiaryTmpResult, iconFourth: iconFourthTmpResult, iconEmphasize: iconEmphasizeTmpResult, iconSubEmphasize: iconSubEmphasizeTmpResult, iconOnPrimary: iconOnPrimaryTmpResult, iconOnSecondary: iconOnSecondaryTmpResult, iconOnTertiary: iconOnTertiaryTmpResult, iconOnFourth: iconOnFourthTmpResult, backgroundPrimary: backgroundPrimaryTmpResult, backgroundSecondary: backgroundSecondaryTmpResult, backgroundTertiary: backgroundTertiaryTmpResult, backgroundFourth: backgroundFourthTmpResult, backgroundEmphasize: backgroundEmphasizeTmpResult, compForegroundPrimary: compForegroundPrimaryTmpResult, compBackgroundPrimary: compBackgroundPrimaryTmpResult, compBackgroundPrimaryTran: compBackgroundPrimaryTranTmpResult, compBackgroundPrimaryContrary: compBackgroundPrimaryContraryTmpResult, compBackgroundGray: compBackgroundGrayTmpResult, compBackgroundSecondary: compBackgroundSecondaryTmpResult, compBackgroundTertiary: compBackgroundTertiaryTmpResult, compBackgroundEmphasize: compBackgroundEmphasizeTmpResult, compBackgroundNeutral: compBackgroundNeutralTmpResult, compEmphasizeSecondary: compEmphasizeSecondaryTmpResult, compEmphasizeTertiary: compEmphasizeTertiaryTmpResult, compDivider: compDividerTmpResult, compCommonContrary: compCommonContraryTmpResult, compBackgroundFocus: compBackgroundFocusTmpResult, compFocusedPrimary: compFocusedPrimaryTmpResult, compFocusedSecondary: compFocusedSecondaryTmpResult, compFocusedTertiary: compFocusedTertiaryTmpResult, interactiveHover: interactiveHoverTmpResult, interactivePressed: interactivePressedTmpResult, interactiveFocus: interactiveFocusTmpResult, interactiveActive: interactiveActiveTmpResult, interactiveSelect: interactiveSelectTmpResult, interactiveClick: interactiveClickTmpResult} as Colors)
        return value
    }
}
export class CustomTheme_serializer {
    public static write(buffer: SerializerBase, value: CustomTheme): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForColors  = value.colors
        if (valueHolderForColors !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorsTmpValue  = valueHolderForColors!
            Colors_serializer.write(valueSerializer, valueHolderForColorsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CustomTheme {
        let valueDeserializer : DeserializerBase = buffer
        const colorsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorsTmpBuf : Colors | undefined
        if ((colorsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            colorsTmpBuf = Colors_serializer.read(valueDeserializer)
        }
        const colorsTmpResult : Colors | undefined = colorsTmpBuf
        let value : CustomTheme = ({colors: colorsTmpResult} as CustomTheme)
        return value
    }
}
