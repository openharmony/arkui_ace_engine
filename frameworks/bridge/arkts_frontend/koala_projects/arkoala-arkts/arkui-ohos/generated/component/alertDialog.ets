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
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { DialogButtonStyle, Color, WordBreak, BorderStyle } from "./enums"
import { ResourceStr, ResourceColor, VoidCallback, Offset, Dimension, BorderRadiuses, LocalizedBorderRadiuses, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, EdgeStyles, Offset_serializer, BorderRadiuses_serializer, LocalizedBorderRadiuses_serializer, EdgeWidths_serializer, LocalizedEdgeWidths_serializer, EdgeColors_serializer, LocalizedEdgeColors_serializer, EdgeStyles_serializer } from "./units"
import { Resource } from "global.resource"
import { DismissDialogAction, DismissDialogAction_serializer } from "./actionSheet"
import { Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, TransitionEffect, ShadowOptions, ShadowStyle, HoverModeAreaType, Rectangle_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, TransitionEffect_serializer, ShadowOptions_serializer } from "./common"
import { LevelMode, ImmersiveMode, LevelOrder } from "@ohos.promptAction"
import { extractors } from "#handwritten"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer } from "./../framework/resource"
import { LevelOrder_serializer } from "./../framework/ohos.promptAction"
export enum DialogAlignment {
    TOP = 0,
    Top = 0,
    CENTER = 1,
    Center = 1,
    BOTTOM = 2,
    Bottom = 2,
    DEFAULT = 3,
    Default = 3,
    TOP_START = 4,
    TopStart = 4,
    TOP_END = 5,
    TopEnd = 5,
    CENTER_START = 6,
    CenterStart = 6,
    CENTER_END = 7,
    CenterEnd = 7,
    BOTTOM_START = 8,
    BottomStart = 8,
    BOTTOM_END = 9,
    BottomEnd = 9
}
export enum DialogButtonDirection {
    AUTO = 0,
    HORIZONTAL = 1,
    VERTICAL = 2
}
export interface AlertDialogButtonBaseOptions {
    enabled?: boolean;
    defaultFocus?: boolean;
    style?: DialogButtonStyle;
    value: ResourceStr;
    fontColor?: ResourceColor;
    backgroundColor?: ResourceColor;
    action: VoidCallback;
}
export interface AlertDialogButtonOptions extends AlertDialogButtonBaseOptions {
    primary?: boolean;
}
export interface AlertDialogTextStyleOptions {
    wordBreak?: WordBreak;
}
export interface AlertDialogParam {
    title?: ResourceStr;
    subtitle?: ResourceStr;
    message: ResourceStr;
    autoCancel?: boolean;
    cancel?: VoidCallback;
    alignment?: DialogAlignment;
    offset?: Offset;
    gridCount?: int32;
    maskRect?: Rectangle;
    showInSubWindow?: boolean;
    isModal?: boolean;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onWillDismiss?: ((value0: DismissDialogAction) => void);
    transition?: TransitionEffect;
    cornerRadius?: Dimension | BorderRadiuses | LocalizedBorderRadiuses;
    width?: Dimension;
    height?: Dimension;
    borderWidth?: Dimension | EdgeWidths | LocalizedEdgeWidths;
    borderColor?: ResourceColor | EdgeColors | LocalizedEdgeColors;
    borderStyle?: BorderStyle | EdgeStyles;
    shadow?: ShadowOptions | ShadowStyle;
    textStyle?: AlertDialogTextStyleOptions;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    levelMode?: LevelMode;
    levelUniqueId?: int32;
    immersiveMode?: ImmersiveMode;
    levelOrder?: LevelOrder;
}
export interface AlertDialogParamWithConfirm extends AlertDialogParam {
    confirm?: AlertDialogButtonBaseOptions;
}
export interface AlertDialogParamWithButtons extends AlertDialogParam {
    primaryButton: AlertDialogButtonBaseOptions;
    secondaryButton: AlertDialogButtonBaseOptions;
}
export interface AlertDialogParamWithOptions extends AlertDialogParam {
    buttons: Array<AlertDialogButtonOptions>;
    buttonDirection?: DialogButtonDirection;
}
export class AlertDialogTextStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: AlertDialogTextStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWordBreak  = value.wordBreak
        if (valueHolderForWordBreak !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWordBreakTmpValue  = (valueHolderForWordBreak as WordBreak)
            valueSerializer.writeInt32(valueHolderForWordBreakTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): AlertDialogTextStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const wordBreakTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let wordBreakTmpBuf : WordBreak | undefined = undefined
        if ((wordBreakTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wordBreakTmpBuf = WordBreak.fromValue(valueDeserializer.readInt32())
        }
        const wordBreakTmpResult : WordBreak | undefined = wordBreakTmpBuf
        let value : AlertDialogTextStyleOptions = ({wordBreak: wordBreakTmpResult} as AlertDialogTextStyleOptions)
        return value
    }
}
export class AlertDialogButtonBaseOptions_serializer {
    public static write(buffer: SerializerBase, value: AlertDialogButtonBaseOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        if (valueHolderForEnabled !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnabledTmpValue  = valueHolderForEnabled!
            valueSerializer.writeBoolean(valueHolderForEnabledTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDefaultFocus  = value.defaultFocus
        if (valueHolderForDefaultFocus !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDefaultFocusTmpValue  = valueHolderForDefaultFocus!
            valueSerializer.writeBoolean(valueHolderForDefaultFocusTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as DialogButtonStyle)
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForValue  = value.value
        if (valueHolderForValue instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForValueForIdx0  = valueHolderForValue as string
            valueSerializer.writeString(valueHolderForValueForIdx0)
        } else if (valueHolderForValue instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForValueForIdx1  = valueHolderForValue as Resource
            Resource_serializer.write(valueSerializer, valueHolderForValueForIdx1)
        }
        const valueHolderForFontColor  = value.fontColor
        if (valueHolderForFontColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontColorTmpValue  = valueHolderForFontColor!
            if (valueHolderForFontColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontColorTmpValueForIdx0  = valueHolderForFontColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForFontColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForFontColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontColorTmpValueForIdx1  = valueHolderForFontColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForFontColorTmpValueForIdx1)
            } else if (valueHolderForFontColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontColorTmpValueForIdx2  = valueHolderForFontColorTmpValue as string
                valueSerializer.writeString(valueHolderForFontColorTmpValueForIdx2)
            } else if (valueHolderForFontColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForFontColorTmpValueForIdx3  = valueHolderForFontColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForFontColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAction  = value.action
        valueSerializer.holdAndWriteCallback(valueHolderForAction)
    }
    public static read(buffer: DeserializerBase): AlertDialogButtonBaseOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enabledTmpBuf : boolean | undefined = undefined
        if ((enabledTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enabledTmpBuf = valueDeserializer.readBoolean()
        }
        const enabledTmpResult : boolean | undefined = enabledTmpBuf
        const defaultFocusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let defaultFocusTmpBuf : boolean | undefined = undefined
        if ((defaultFocusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            defaultFocusTmpBuf = valueDeserializer.readBoolean()
        }
        const defaultFocusTmpResult : boolean | undefined = defaultFocusTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : DialogButtonStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = DialogButtonStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : DialogButtonStyle | undefined = styleTmpBuf
        const valueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let valueTmpBuf : string | Resource | undefined
        if (valueTmpBufUnionSelector == (0).toChar()) {
            valueTmpBuf = (valueDeserializer.readString() as string)
        } else if (valueTmpBufUnionSelector == (1).toChar()) {
            valueTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for valueTmpBuf has to be chosen through deserialisation.")
        }
        const valueTmpResult : ResourceStr = (valueTmpBuf as string | Resource)
        const fontColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontColorTmpBuf : ResourceColor | undefined = undefined
        if ((fontColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontColorTmpBuf_ : Color | number | string | Resource | undefined
            if (fontColorTmpBuf_UnionSelector == (0).toChar()) {
                fontColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (fontColorTmpBuf_UnionSelector == (1).toChar()) {
                fontColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (fontColorTmpBuf_UnionSelector == (2).toChar()) {
                fontColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (fontColorTmpBuf_UnionSelector == (3).toChar()) {
                fontColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for fontColorTmpBuf_ has to be chosen through deserialisation.")
            }
            fontColorTmpBuf = (fontColorTmpBuf_ as Color | number | string | Resource)
        }
        const fontColorTmpResult : ResourceColor | undefined = fontColorTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const actionTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const actionTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const actionTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const actionTmpResult : VoidCallback = ():void => {
            const actionTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            actionTmpBufBufArgsSerializer.writeInt32(actionTmpBufBufResource.resourceId);
            actionTmpBufBufArgsSerializer.writePointer(actionTmpBufBufCall);
            actionTmpBufBufArgsSerializer.writePointer(actionTmpBufBufCallSync);
            InteropNativeModule._CallCallbackSync(10, -2038961969, actionTmpBufBufArgsSerializer.asBuffer(), actionTmpBufBufArgsSerializer.length());
            actionTmpBufBufArgsSerializer.release();
            return;
        }
        let value : AlertDialogButtonBaseOptions = ({enabled: enabledTmpResult, defaultFocus: defaultFocusTmpResult, style: styleTmpResult, value: valueTmpResult, fontColor: fontColorTmpResult, backgroundColor: backgroundColorTmpResult, action: actionTmpResult} as AlertDialogButtonBaseOptions)
        return value
    }
}
export class AlertDialogButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: AlertDialogButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        if (valueHolderForEnabled !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnabledTmpValue  = valueHolderForEnabled!
            valueSerializer.writeBoolean(valueHolderForEnabledTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDefaultFocus  = value.defaultFocus
        if (valueHolderForDefaultFocus !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDefaultFocusTmpValue  = valueHolderForDefaultFocus!
            valueSerializer.writeBoolean(valueHolderForDefaultFocusTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as DialogButtonStyle)
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForValue  = value.value
        if (valueHolderForValue instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForValueForIdx0  = valueHolderForValue as string
            valueSerializer.writeString(valueHolderForValueForIdx0)
        } else if (valueHolderForValue instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForValueForIdx1  = valueHolderForValue as Resource
            Resource_serializer.write(valueSerializer, valueHolderForValueForIdx1)
        }
        const valueHolderForFontColor  = value.fontColor
        if (valueHolderForFontColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontColorTmpValue  = valueHolderForFontColor!
            if (valueHolderForFontColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontColorTmpValueForIdx0  = valueHolderForFontColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForFontColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForFontColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontColorTmpValueForIdx1  = valueHolderForFontColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForFontColorTmpValueForIdx1)
            } else if (valueHolderForFontColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontColorTmpValueForIdx2  = valueHolderForFontColorTmpValue as string
                valueSerializer.writeString(valueHolderForFontColorTmpValueForIdx2)
            } else if (valueHolderForFontColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForFontColorTmpValueForIdx3  = valueHolderForFontColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForFontColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAction  = value.action
        valueSerializer.holdAndWriteCallback(valueHolderForAction)
        const valueHolderForPrimary  = value.primary
        if (valueHolderForPrimary !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPrimaryTmpValue  = valueHolderForPrimary!
            valueSerializer.writeBoolean(valueHolderForPrimaryTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): AlertDialogButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enabledTmpBuf : boolean | undefined = undefined
        if ((enabledTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enabledTmpBuf = valueDeserializer.readBoolean()
        }
        const enabledTmpResult : boolean | undefined = enabledTmpBuf
        const defaultFocusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let defaultFocusTmpBuf : boolean | undefined = undefined
        if ((defaultFocusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            defaultFocusTmpBuf = valueDeserializer.readBoolean()
        }
        const defaultFocusTmpResult : boolean | undefined = defaultFocusTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : DialogButtonStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = DialogButtonStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : DialogButtonStyle | undefined = styleTmpBuf
        const valueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let valueTmpBuf : string | Resource | undefined
        if (valueTmpBufUnionSelector == (0).toChar()) {
            valueTmpBuf = (valueDeserializer.readString() as string)
        } else if (valueTmpBufUnionSelector == (1).toChar()) {
            valueTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for valueTmpBuf has to be chosen through deserialisation.")
        }
        const valueTmpResult : ResourceStr = (valueTmpBuf as string | Resource)
        const fontColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontColorTmpBuf : ResourceColor | undefined = undefined
        if ((fontColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontColorTmpBuf_ : Color | number | string | Resource | undefined
            if (fontColorTmpBuf_UnionSelector == (0).toChar()) {
                fontColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (fontColorTmpBuf_UnionSelector == (1).toChar()) {
                fontColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (fontColorTmpBuf_UnionSelector == (2).toChar()) {
                fontColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (fontColorTmpBuf_UnionSelector == (3).toChar()) {
                fontColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for fontColorTmpBuf_ has to be chosen through deserialisation.")
            }
            fontColorTmpBuf = (fontColorTmpBuf_ as Color | number | string | Resource)
        }
        const fontColorTmpResult : ResourceColor | undefined = fontColorTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const actionTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const actionTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const actionTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const actionTmpResult : VoidCallback = ():void => {
            const actionTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            actionTmpBufBufArgsSerializer.writeInt32(actionTmpBufBufResource.resourceId);
            actionTmpBufBufArgsSerializer.writePointer(actionTmpBufBufCall);
            actionTmpBufBufArgsSerializer.writePointer(actionTmpBufBufCallSync);
            InteropNativeModule._CallCallbackSync(10, -2038961969, actionTmpBufBufArgsSerializer.asBuffer(), actionTmpBufBufArgsSerializer.length());
            actionTmpBufBufArgsSerializer.release();
            return;
        }
        const primaryTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let primaryTmpBuf : boolean | undefined = undefined
        if ((primaryTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            primaryTmpBuf = valueDeserializer.readBoolean()
        }
        const primaryTmpResult : boolean | undefined = primaryTmpBuf
        let value : AlertDialogButtonOptions = ({enabled: enabledTmpResult, defaultFocus: defaultFocusTmpResult, style: styleTmpResult, value: valueTmpResult, fontColor: fontColorTmpResult, backgroundColor: backgroundColorTmpResult, action: actionTmpResult, primary: primaryTmpResult} as AlertDialogButtonOptions)
        return value
    }
}
export class AlertDialogParamWithButtons_serializer {
    public static write(buffer: SerializerBase, value: AlertDialogParamWithButtons): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTitle  = value.title
        if (valueHolderForTitle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTitleTmpValue  = valueHolderForTitle!
            if (valueHolderForTitleTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTitleTmpValueForIdx0  = valueHolderForTitleTmpValue as string
                valueSerializer.writeString(valueHolderForTitleTmpValueForIdx0)
            } else if (valueHolderForTitleTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTitleTmpValueForIdx1  = valueHolderForTitleTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTitleTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSubtitle  = value.subtitle
        if (valueHolderForSubtitle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSubtitleTmpValue  = valueHolderForSubtitle!
            if (valueHolderForSubtitleTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSubtitleTmpValueForIdx0  = valueHolderForSubtitleTmpValue as string
                valueSerializer.writeString(valueHolderForSubtitleTmpValueForIdx0)
            } else if (valueHolderForSubtitleTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSubtitleTmpValueForIdx1  = valueHolderForSubtitleTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSubtitleTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMessage  = value.message
        if (valueHolderForMessage instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForMessageForIdx0  = valueHolderForMessage as string
            valueSerializer.writeString(valueHolderForMessageForIdx0)
        } else if (valueHolderForMessage instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForMessageForIdx1  = valueHolderForMessage as Resource
            Resource_serializer.write(valueSerializer, valueHolderForMessageForIdx1)
        }
        const valueHolderForAutoCancel  = value.autoCancel
        if (valueHolderForAutoCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAutoCancelTmpValue  = valueHolderForAutoCancel!
            valueSerializer.writeBoolean(valueHolderForAutoCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCancel  = value.cancel
        if (valueHolderForCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCancelTmpValue  = valueHolderForCancel!
            valueSerializer.holdAndWriteCallback(valueHolderForCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlignment  = value.alignment
        if (valueHolderForAlignment !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignmentTmpValue  = (valueHolderForAlignment as DialogAlignment)
            valueSerializer.writeInt32(valueHolderForAlignmentTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            Offset_serializer.write(valueSerializer, valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForGridCount  = value.gridCount
        if (valueHolderForGridCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGridCountTmpValue  = valueHolderForGridCount!
            valueSerializer.writeInt32(valueHolderForGridCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaskRect  = value.maskRect
        if (valueHolderForMaskRect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaskRectTmpValue  = valueHolderForMaskRect!
            Rectangle_serializer.write(valueSerializer, valueHolderForMaskRectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShowInSubWindow  = value.showInSubWindow
        if (valueHolderForShowInSubWindow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowInSubWindowTmpValue  = valueHolderForShowInSubWindow!
            valueSerializer.writeBoolean(valueHolderForShowInSubWindowTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIsModal  = value.isModal
        if (valueHolderForIsModal !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsModalTmpValue  = valueHolderForIsModal!
            valueSerializer.writeBoolean(valueHolderForIsModalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyle  = value.backgroundBlurStyle
        if (valueHolderForBackgroundBlurStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleTmpValue  = (valueHolderForBackgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(valueHolderForBackgroundBlurStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        if (valueHolderForBackgroundBlurStyleOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleOptionsTmpValue  = valueHolderForBackgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, valueHolderForBackgroundBlurStyleOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundEffect  = value.backgroundEffect
        if (valueHolderForBackgroundEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundEffectTmpValue  = valueHolderForBackgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, valueHolderForBackgroundEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDismiss  = value.onWillDismiss
        if (valueHolderForOnWillDismiss !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDismissTmpValue  = valueHolderForOnWillDismiss!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDismissTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTransition  = value.transition
        if (valueHolderForTransition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTransitionTmpValue  = valueHolderForTransition!
            TransitionEffect_serializer.write(valueSerializer, valueHolderForTransitionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCornerRadius  = value.cornerRadius
        if (valueHolderForCornerRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCornerRadiusTmpValue  = valueHolderForCornerRadius!
            if (valueHolderForCornerRadiusTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx0  = valueHolderForCornerRadiusTmpValue as Dimension
                if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx0  = valueHolderForCornerRadiusTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForCornerRadiusTmpValueForIdx0ForIdx0)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx1  = valueHolderForCornerRadiusTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForCornerRadiusTmpValueForIdx0ForIdx1)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx2  = valueHolderForCornerRadiusTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForCornerRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx1  = valueHolderForCornerRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx1)
            } else if (valueHolderForCornerRadiusTmpValue instanceof LocalizedBorderRadiuses) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx2  = valueHolderForCornerRadiusTmpValue as LocalizedBorderRadiuses
                LocalizedBorderRadiuses_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForHeightTmpValueForIdx2  = valueHolderForHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderWidth  = value.borderWidth
        if (valueHolderForBorderWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderWidthTmpValue  = valueHolderForBorderWidth!
            if (valueHolderForBorderWidthTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderWidthTmpValueForIdx0  = valueHolderForBorderWidthTmpValue as Dimension
                if (valueHolderForBorderWidthTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx0  = valueHolderForBorderWidthTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderWidthTmpValueForIdx0ForIdx0)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx1  = valueHolderForBorderWidthTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderWidthTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx2  = valueHolderForBorderWidthTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForBorderWidthTmpValue instanceof EdgeWidths) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderWidthTmpValueForIdx1  = valueHolderForBorderWidthTmpValue as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx1)
            } else if (valueHolderForBorderWidthTmpValue instanceof LocalizedEdgeWidths) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderWidthTmpValueForIdx2  = valueHolderForBorderWidthTmpValue as LocalizedEdgeWidths
                LocalizedEdgeWidths_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderColor  = value.borderColor
        if (valueHolderForBorderColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderColorTmpValue  = valueHolderForBorderColor!
            if (valueHolderForBorderColorTmpValue instanceof ResourceColor) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderColorTmpValueForIdx0  = valueHolderForBorderColorTmpValue as ResourceColor
                if (valueHolderForBorderColorTmpValueForIdx0 instanceof Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx0  = valueHolderForBorderColorTmpValueForIdx0 as Color
                    valueSerializer.writeInt32(valueHolderForBorderColorTmpValueForIdx0ForIdx0.getOrdinal())
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx1  = valueHolderForBorderColorTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderColorTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx2  = valueHolderForBorderColorTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderColorTmpValueForIdx0ForIdx2)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx3  = valueHolderForBorderColorTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx0ForIdx3)
                }
            } else if (valueHolderForBorderColorTmpValue instanceof EdgeColors) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderColorTmpValueForIdx1  = valueHolderForBorderColorTmpValue as EdgeColors
                EdgeColors_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx1)
            } else if (valueHolderForBorderColorTmpValue instanceof LocalizedEdgeColors) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderColorTmpValueForIdx2  = valueHolderForBorderColorTmpValue as LocalizedEdgeColors
                LocalizedEdgeColors_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderStyle  = value.borderStyle
        if (valueHolderForBorderStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderStyleTmpValue  = valueHolderForBorderStyle!
            if (valueHolderForBorderStyleTmpValue instanceof BorderStyle) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderStyleTmpValueForIdx0  = valueHolderForBorderStyleTmpValue as BorderStyle
                valueSerializer.writeInt32(valueHolderForBorderStyleTmpValueForIdx0.valueOf())
            } else if (valueHolderForBorderStyleTmpValue instanceof EdgeStyles) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderStyleTmpValueForIdx1  = valueHolderForBorderStyleTmpValue as EdgeStyles
                EdgeStyles_serializer.write(valueSerializer, valueHolderForBorderStyleTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShadow  = value.shadow
        if (valueHolderForShadow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShadowTmpValue  = valueHolderForShadow!
            if (valueHolderForShadowTmpValue instanceof ShadowOptions) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForShadowTmpValueForIdx0  = valueHolderForShadowTmpValue as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, valueHolderForShadowTmpValueForIdx0)
            } else if (valueHolderForShadowTmpValue instanceof ShadowStyle) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForShadowTmpValueForIdx1  = valueHolderForShadowTmpValue as ShadowStyle
                valueSerializer.writeInt32(valueHolderForShadowTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextStyle  = value.textStyle
        if (valueHolderForTextStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextStyleTmpValue  = valueHolderForTextStyle!
            AlertDialogTextStyleOptions_serializer.write(valueSerializer, valueHolderForTextStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableHoverMode  = value.enableHoverMode
        if (valueHolderForEnableHoverMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableHoverModeTmpValue  = valueHolderForEnableHoverMode!
            valueSerializer.writeBoolean(valueHolderForEnableHoverModeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHoverModeArea  = value.hoverModeArea
        if (valueHolderForHoverModeArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHoverModeAreaTmpValue  = (valueHolderForHoverModeArea as HoverModeAreaType)
            valueSerializer.writeInt32(valueHolderForHoverModeAreaTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidAppear  = value.onDidAppear
        if (valueHolderForOnDidAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidAppearTmpValue  = valueHolderForOnDidAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidDisappear  = value.onDidDisappear
        if (valueHolderForOnDidDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidDisappearTmpValue  = valueHolderForOnDidDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillAppear  = value.onWillAppear
        if (valueHolderForOnWillAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillAppearTmpValue  = valueHolderForOnWillAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDisappear  = value.onWillDisappear
        if (valueHolderForOnWillDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDisappearTmpValue  = valueHolderForOnWillDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelMode  = value.levelMode
        if (valueHolderForLevelMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelModeTmpValue  = (valueHolderForLevelMode as LevelMode)
            valueSerializer.writeInt32(valueHolderForLevelModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelUniqueId  = value.levelUniqueId
        if (valueHolderForLevelUniqueId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelUniqueIdTmpValue  = valueHolderForLevelUniqueId!
            valueSerializer.writeInt32(valueHolderForLevelUniqueIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImmersiveMode  = value.immersiveMode
        if (valueHolderForImmersiveMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImmersiveModeTmpValue  = (valueHolderForImmersiveMode as ImmersiveMode)
            valueSerializer.writeInt32(valueHolderForImmersiveModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelOrder  = value.levelOrder
        if (valueHolderForLevelOrder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelOrderTmpValue  = valueHolderForLevelOrder!
            LevelOrder_serializer.write(valueSerializer, valueHolderForLevelOrderTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPrimaryButton  = value.primaryButton
        AlertDialogButtonBaseOptions_serializer.write(valueSerializer, valueHolderForPrimaryButton)
        const valueHolderForSecondaryButton  = value.secondaryButton
        AlertDialogButtonBaseOptions_serializer.write(valueSerializer, valueHolderForSecondaryButton)
    }
    public static read(buffer: DeserializerBase): AlertDialogParamWithButtons {
        let valueDeserializer : DeserializerBase = buffer
        const titleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let titleTmpBuf : ResourceStr | undefined = undefined
        if ((titleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const titleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let titleTmpBuf_ : string | Resource | undefined
            if (titleTmpBuf_UnionSelector == (0).toChar()) {
                titleTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (titleTmpBuf_UnionSelector == (1).toChar()) {
                titleTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for titleTmpBuf_ has to be chosen through deserialisation.")
            }
            titleTmpBuf = (titleTmpBuf_ as string | Resource)
        }
        const titleTmpResult : ResourceStr | undefined = titleTmpBuf
        const subtitleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let subtitleTmpBuf : ResourceStr | undefined = undefined
        if ((subtitleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const subtitleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let subtitleTmpBuf_ : string | Resource | undefined
            if (subtitleTmpBuf_UnionSelector == (0).toChar()) {
                subtitleTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (subtitleTmpBuf_UnionSelector == (1).toChar()) {
                subtitleTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for subtitleTmpBuf_ has to be chosen through deserialisation.")
            }
            subtitleTmpBuf = (subtitleTmpBuf_ as string | Resource)
        }
        const subtitleTmpResult : ResourceStr | undefined = subtitleTmpBuf
        const messageTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let messageTmpBuf : string | Resource | undefined
        if (messageTmpBufUnionSelector == (0).toChar()) {
            messageTmpBuf = (valueDeserializer.readString() as string)
        } else if (messageTmpBufUnionSelector == (1).toChar()) {
            messageTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for messageTmpBuf has to be chosen through deserialisation.")
        }
        const messageTmpResult : ResourceStr = (messageTmpBuf as string | Resource)
        const autoCancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let autoCancelTmpBuf : boolean | undefined = undefined
        if ((autoCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            autoCancelTmpBuf = valueDeserializer.readBoolean()
        }
        const autoCancelTmpResult : boolean | undefined = autoCancelTmpBuf
        const cancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cancelTmpBuf : VoidCallback | undefined = undefined
        if ((cancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cancelTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const cancelTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const cancelTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            cancelTmpBuf = ():void => {
                const cancelTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                cancelTmpBuf_BufArgsSerializer.writeInt32(cancelTmpBuf_BufResource.resourceId);
                cancelTmpBuf_BufArgsSerializer.writePointer(cancelTmpBuf_BufCall);
                cancelTmpBuf_BufArgsSerializer.writePointer(cancelTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, cancelTmpBuf_BufArgsSerializer.asBuffer(), cancelTmpBuf_BufArgsSerializer.length());
                cancelTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const cancelTmpResult : VoidCallback | undefined = cancelTmpBuf
        const alignmentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignmentTmpBuf : DialogAlignment | undefined = undefined
        if ((alignmentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignmentTmpBuf = DialogAlignment.fromValue(valueDeserializer.readInt32())
        }
        const alignmentTmpResult : DialogAlignment | undefined = alignmentTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetTmpBuf : Offset | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = Offset_serializer.read(valueDeserializer)
        }
        const offsetTmpResult : Offset | undefined = offsetTmpBuf
        const gridCountTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let gridCountTmpBuf : int32 | undefined = undefined
        if ((gridCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            gridCountTmpBuf = valueDeserializer.readInt32()
        }
        const gridCountTmpResult : int32 | undefined = gridCountTmpBuf
        const maskRectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maskRectTmpBuf : Rectangle | undefined = undefined
        if ((maskRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maskRectTmpBuf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRectTmpResult : Rectangle | undefined = maskRectTmpBuf
        const showInSubWindowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showInSubWindowTmpBuf : boolean | undefined = undefined
        if ((showInSubWindowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showInSubWindowTmpBuf = valueDeserializer.readBoolean()
        }
        const showInSubWindowTmpResult : boolean | undefined = showInSubWindowTmpBuf
        const isModalTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isModalTmpBuf : boolean | undefined = undefined
        if ((isModalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isModalTmpBuf = valueDeserializer.readBoolean()
        }
        const isModalTmpResult : boolean | undefined = isModalTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const onWillDismissTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDismissTmpBuf : ((value0: DismissDialogAction) => void) | undefined = undefined
        if ((onWillDismissTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDismissTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDismissTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDismissTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDismissTmpBuf = (value0: DismissDialogAction):void => {
                const onWillDismissTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDismissTmpBuf_BufArgsSerializer.writeInt32(onWillDismissTmpBuf_BufResource.resourceId);
                onWillDismissTmpBuf_BufArgsSerializer.writePointer(onWillDismissTmpBuf_BufCall);
                onWillDismissTmpBuf_BufArgsSerializer.writePointer(onWillDismissTmpBuf_BufCallSync);
                DismissDialogAction_serializer.write(onWillDismissTmpBuf_BufArgsSerializer, value0);
                InteropNativeModule._CallCallbackSync(10, -2095828093, onWillDismissTmpBuf_BufArgsSerializer.asBuffer(), onWillDismissTmpBuf_BufArgsSerializer.length());
                onWillDismissTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDismissTmpResult : ((value0: DismissDialogAction) => void) | undefined = onWillDismissTmpBuf
        const transitionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let transitionTmpBuf : TransitionEffect | undefined = undefined
        if ((transitionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            transitionTmpBuf = (TransitionEffect_serializer.read(valueDeserializer) as TransitionEffect)
        }
        const transitionTmpResult : TransitionEffect | undefined = transitionTmpBuf
        const cornerRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cornerRadiusTmpBuf : Dimension | BorderRadiuses | LocalizedBorderRadiuses | undefined = undefined
        if ((cornerRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cornerRadiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let cornerRadiusTmpBuf_ : Dimension | BorderRadiuses | LocalizedBorderRadiuses | undefined
            if (cornerRadiusTmpBuf_UnionSelector == (0).toChar()) {
                const cornerRadiusTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let cornerRadiusTmpBuf_BufU : string | number | Resource | undefined
                if (cornerRadiusTmpBuf_BufUUnionSelector == (0).toChar()) {
                    cornerRadiusTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (cornerRadiusTmpBuf_BufUUnionSelector == (1).toChar()) {
                    cornerRadiusTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (cornerRadiusTmpBuf_BufUUnionSelector == (2).toChar()) {
                    cornerRadiusTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for cornerRadiusTmpBuf_BufU has to be chosen through deserialisation.")
                }
                cornerRadiusTmpBuf_ = (cornerRadiusTmpBuf_BufU as string | number | Resource)
            } else if (cornerRadiusTmpBuf_UnionSelector == (1).toChar()) {
                cornerRadiusTmpBuf_ = BorderRadiuses_serializer.read(valueDeserializer)
            } else if (cornerRadiusTmpBuf_UnionSelector == (2).toChar()) {
                cornerRadiusTmpBuf_ = LocalizedBorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for cornerRadiusTmpBuf_ has to be chosen through deserialisation.")
            }
            cornerRadiusTmpBuf = (cornerRadiusTmpBuf_ as Dimension | BorderRadiuses | LocalizedBorderRadiuses)
        }
        const cornerRadiusTmpResult : Dimension | BorderRadiuses | LocalizedBorderRadiuses | undefined = cornerRadiusTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : Dimension | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : string | number | Resource | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBuf_UnionSelector == (2).toChar()) {
                widthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as string | number | Resource)
        }
        const widthTmpResult : Dimension | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : Dimension | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : string | number | Resource | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBuf_UnionSelector == (2).toChar()) {
                heightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as string | number | Resource)
        }
        const heightTmpResult : Dimension | undefined = heightTmpBuf
        const borderWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderWidthTmpBuf : Dimension | EdgeWidths | LocalizedEdgeWidths | undefined = undefined
        if ((borderWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderWidthTmpBuf_ : Dimension | EdgeWidths | LocalizedEdgeWidths | undefined
            if (borderWidthTmpBuf_UnionSelector == (0).toChar()) {
                const borderWidthTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderWidthTmpBuf_BufU : string | number | Resource | undefined
                if (borderWidthTmpBuf_BufUUnionSelector == (0).toChar()) {
                    borderWidthTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (borderWidthTmpBuf_BufUUnionSelector == (1).toChar()) {
                    borderWidthTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (borderWidthTmpBuf_BufUUnionSelector == (2).toChar()) {
                    borderWidthTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for borderWidthTmpBuf_BufU has to be chosen through deserialisation.")
                }
                borderWidthTmpBuf_ = (borderWidthTmpBuf_BufU as string | number | Resource)
            } else if (borderWidthTmpBuf_UnionSelector == (1).toChar()) {
                borderWidthTmpBuf_ = EdgeWidths_serializer.read(valueDeserializer)
            } else if (borderWidthTmpBuf_UnionSelector == (2).toChar()) {
                borderWidthTmpBuf_ = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            borderWidthTmpBuf = (borderWidthTmpBuf_ as Dimension | EdgeWidths | LocalizedEdgeWidths)
        }
        const borderWidthTmpResult : Dimension | EdgeWidths | LocalizedEdgeWidths | undefined = borderWidthTmpBuf
        const borderColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderColorTmpBuf : ResourceColor | EdgeColors | LocalizedEdgeColors | undefined = undefined
        if ((borderColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderColorTmpBuf_ : ResourceColor | EdgeColors | LocalizedEdgeColors | undefined
            if (borderColorTmpBuf_UnionSelector == (0).toChar()) {
                const borderColorTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderColorTmpBuf_BufU : Color | number | string | Resource | undefined
                if (borderColorTmpBuf_BufUUnionSelector == (0).toChar()) {
                    borderColorTmpBuf_BufU = Color.values()[valueDeserializer.readInt32()]
                } else if (borderColorTmpBuf_BufUUnionSelector == (1).toChar()) {
                    borderColorTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (borderColorTmpBuf_BufUUnionSelector == (2).toChar()) {
                    borderColorTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (borderColorTmpBuf_BufUUnionSelector == (3).toChar()) {
                    borderColorTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for borderColorTmpBuf_BufU has to be chosen through deserialisation.")
                }
                borderColorTmpBuf_ = (borderColorTmpBuf_BufU as Color | number | string | Resource)
            } else if (borderColorTmpBuf_UnionSelector == (1).toChar()) {
                borderColorTmpBuf_ = EdgeColors_serializer.read(valueDeserializer)
            } else if (borderColorTmpBuf_UnionSelector == (2).toChar()) {
                borderColorTmpBuf_ = LocalizedEdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderColorTmpBuf_ has to be chosen through deserialisation.")
            }
            borderColorTmpBuf = (borderColorTmpBuf_ as ResourceColor | EdgeColors | LocalizedEdgeColors)
        }
        const borderColorTmpResult : ResourceColor | EdgeColors | LocalizedEdgeColors | undefined = borderColorTmpBuf
        const borderStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderStyleTmpBuf : BorderStyle | EdgeStyles | undefined = undefined
        if ((borderStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderStyleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderStyleTmpBuf_ : BorderStyle | EdgeStyles | undefined
            if (borderStyleTmpBuf_UnionSelector == (0).toChar()) {
                borderStyleTmpBuf_ = BorderStyle.fromValue(valueDeserializer.readInt32())
            } else if (borderStyleTmpBuf_UnionSelector == (1).toChar()) {
                borderStyleTmpBuf_ = EdgeStyles_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderStyleTmpBuf_ has to be chosen through deserialisation.")
            }
            borderStyleTmpBuf = (borderStyleTmpBuf_ as BorderStyle | EdgeStyles)
        }
        const borderStyleTmpResult : BorderStyle | EdgeStyles | undefined = borderStyleTmpBuf
        const shadowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shadowTmpBuf : ShadowOptions | ShadowStyle | undefined = undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shadowTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let shadowTmpBuf_ : ShadowOptions | ShadowStyle | undefined
            if (shadowTmpBuf_UnionSelector == (0).toChar()) {
                shadowTmpBuf_ = ShadowOptions_serializer.read(valueDeserializer)
            } else if (shadowTmpBuf_UnionSelector == (1).toChar()) {
                shadowTmpBuf_ = ShadowStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for shadowTmpBuf_ has to be chosen through deserialisation.")
            }
            shadowTmpBuf = (shadowTmpBuf_ as ShadowOptions | ShadowStyle)
        }
        const shadowTmpResult : ShadowOptions | ShadowStyle | undefined = shadowTmpBuf
        const textStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textStyleTmpBuf : AlertDialogTextStyleOptions | undefined = undefined
        if ((textStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textStyleTmpBuf = AlertDialogTextStyleOptions_serializer.read(valueDeserializer)
        }
        const textStyleTmpResult : AlertDialogTextStyleOptions | undefined = textStyleTmpBuf
        const enableHoverModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHoverModeTmpBuf : boolean | undefined = undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult : boolean | undefined = enableHoverModeTmpBuf
        const hoverModeAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hoverModeAreaTmpBuf : HoverModeAreaType | undefined = undefined
        if ((hoverModeAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hoverModeAreaTmpBuf = HoverModeAreaType.fromValue(valueDeserializer.readInt32())
        }
        const hoverModeAreaTmpResult : HoverModeAreaType | undefined = hoverModeAreaTmpBuf
        const onDidAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidAppearTmpBuf : (() => void) | undefined = undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidAppearTmpBuf = ():void => {
                const onDidAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidAppearTmpBuf_BufArgsSerializer.writeInt32(onDidAppearTmpBuf_BufResource.resourceId);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCall);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onDidAppearTmpBuf_BufArgsSerializer.asBuffer(), onDidAppearTmpBuf_BufArgsSerializer.length());
                onDidAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidAppearTmpResult : (() => void) | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidDisappearTmpBuf = ():void => {
                const onDidDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBuf_BufArgsSerializer.writeInt32(onDidDisappearTmpBuf_BufResource.resourceId);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCall);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onDidDisappearTmpBuf_BufArgsSerializer.asBuffer(), onDidDisappearTmpBuf_BufArgsSerializer.length());
                onDidDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidDisappearTmpResult : (() => void) | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillAppearTmpBuf : (() => void) | undefined = undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillAppearTmpBuf = ():void => {
                const onWillAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillAppearTmpBuf_BufArgsSerializer.writeInt32(onWillAppearTmpBuf_BufResource.resourceId);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCall);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onWillAppearTmpBuf_BufArgsSerializer.asBuffer(), onWillAppearTmpBuf_BufArgsSerializer.length());
                onWillAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillAppearTmpResult : (() => void) | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDisappearTmpBuf = ():void => {
                const onWillDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBuf_BufArgsSerializer.writeInt32(onWillDisappearTmpBuf_BufResource.resourceId);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCall);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onWillDisappearTmpBuf_BufArgsSerializer.asBuffer(), onWillDisappearTmpBuf_BufArgsSerializer.length());
                onWillDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDisappearTmpResult : (() => void) | undefined = onWillDisappearTmpBuf
        const levelModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelModeTmpBuf : LevelMode | undefined = undefined
        if ((levelModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelModeTmpBuf = LevelMode.fromValue(valueDeserializer.readInt32())
        }
        const levelModeTmpResult : LevelMode | undefined = levelModeTmpBuf
        const levelUniqueIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelUniqueIdTmpBuf : int32 | undefined = undefined
        if ((levelUniqueIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelUniqueIdTmpBuf = valueDeserializer.readInt32()
        }
        const levelUniqueIdTmpResult : int32 | undefined = levelUniqueIdTmpBuf
        const immersiveModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let immersiveModeTmpBuf : ImmersiveMode | undefined = undefined
        if ((immersiveModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            immersiveModeTmpBuf = ImmersiveMode.fromValue(valueDeserializer.readInt32())
        }
        const immersiveModeTmpResult : ImmersiveMode | undefined = immersiveModeTmpBuf
        const levelOrderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelOrderTmpBuf : LevelOrder | undefined = undefined
        if ((levelOrderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelOrderTmpBuf = (LevelOrder_serializer.read(valueDeserializer) as LevelOrder)
        }
        const levelOrderTmpResult : LevelOrder | undefined = levelOrderTmpBuf
        const primaryButtonTmpResult : AlertDialogButtonBaseOptions = AlertDialogButtonBaseOptions_serializer.read(valueDeserializer)
        const secondaryButtonTmpResult : AlertDialogButtonBaseOptions = AlertDialogButtonBaseOptions_serializer.read(valueDeserializer)
        let value : AlertDialogParamWithButtons = ({title: titleTmpResult, subtitle: subtitleTmpResult, message: messageTmpResult, autoCancel: autoCancelTmpResult, cancel: cancelTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, gridCount: gridCountTmpResult, maskRect: maskRectTmpResult, showInSubWindow: showInSubWindowTmpResult, isModal: isModalTmpResult, backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, onWillDismiss: onWillDismissTmpResult, transition: transitionTmpResult, cornerRadius: cornerRadiusTmpResult, width: widthTmpResult, height: heightTmpResult, borderWidth: borderWidthTmpResult, borderColor: borderColorTmpResult, borderStyle: borderStyleTmpResult, shadow: shadowTmpResult, textStyle: textStyleTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, levelMode: levelModeTmpResult, levelUniqueId: levelUniqueIdTmpResult, immersiveMode: immersiveModeTmpResult, levelOrder: levelOrderTmpResult, primaryButton: primaryButtonTmpResult, secondaryButton: secondaryButtonTmpResult} as AlertDialogParamWithButtons)
        return value
    }
}
export class AlertDialogParamWithConfirm_serializer {
    public static write(buffer: SerializerBase, value: AlertDialogParamWithConfirm): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTitle  = value.title
        if (valueHolderForTitle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTitleTmpValue  = valueHolderForTitle!
            if (valueHolderForTitleTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTitleTmpValueForIdx0  = valueHolderForTitleTmpValue as string
                valueSerializer.writeString(valueHolderForTitleTmpValueForIdx0)
            } else if (valueHolderForTitleTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTitleTmpValueForIdx1  = valueHolderForTitleTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTitleTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSubtitle  = value.subtitle
        if (valueHolderForSubtitle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSubtitleTmpValue  = valueHolderForSubtitle!
            if (valueHolderForSubtitleTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSubtitleTmpValueForIdx0  = valueHolderForSubtitleTmpValue as string
                valueSerializer.writeString(valueHolderForSubtitleTmpValueForIdx0)
            } else if (valueHolderForSubtitleTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSubtitleTmpValueForIdx1  = valueHolderForSubtitleTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSubtitleTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMessage  = value.message
        if (valueHolderForMessage instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForMessageForIdx0  = valueHolderForMessage as string
            valueSerializer.writeString(valueHolderForMessageForIdx0)
        } else if (valueHolderForMessage instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForMessageForIdx1  = valueHolderForMessage as Resource
            Resource_serializer.write(valueSerializer, valueHolderForMessageForIdx1)
        }
        const valueHolderForAutoCancel  = value.autoCancel
        if (valueHolderForAutoCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAutoCancelTmpValue  = valueHolderForAutoCancel!
            valueSerializer.writeBoolean(valueHolderForAutoCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCancel  = value.cancel
        if (valueHolderForCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCancelTmpValue  = valueHolderForCancel!
            valueSerializer.holdAndWriteCallback(valueHolderForCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlignment  = value.alignment
        if (valueHolderForAlignment !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignmentTmpValue  = (valueHolderForAlignment as DialogAlignment)
            valueSerializer.writeInt32(valueHolderForAlignmentTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            Offset_serializer.write(valueSerializer, valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForGridCount  = value.gridCount
        if (valueHolderForGridCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGridCountTmpValue  = valueHolderForGridCount!
            valueSerializer.writeInt32(valueHolderForGridCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaskRect  = value.maskRect
        if (valueHolderForMaskRect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaskRectTmpValue  = valueHolderForMaskRect!
            Rectangle_serializer.write(valueSerializer, valueHolderForMaskRectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShowInSubWindow  = value.showInSubWindow
        if (valueHolderForShowInSubWindow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowInSubWindowTmpValue  = valueHolderForShowInSubWindow!
            valueSerializer.writeBoolean(valueHolderForShowInSubWindowTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIsModal  = value.isModal
        if (valueHolderForIsModal !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsModalTmpValue  = valueHolderForIsModal!
            valueSerializer.writeBoolean(valueHolderForIsModalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyle  = value.backgroundBlurStyle
        if (valueHolderForBackgroundBlurStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleTmpValue  = (valueHolderForBackgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(valueHolderForBackgroundBlurStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        if (valueHolderForBackgroundBlurStyleOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleOptionsTmpValue  = valueHolderForBackgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, valueHolderForBackgroundBlurStyleOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundEffect  = value.backgroundEffect
        if (valueHolderForBackgroundEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundEffectTmpValue  = valueHolderForBackgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, valueHolderForBackgroundEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDismiss  = value.onWillDismiss
        if (valueHolderForOnWillDismiss !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDismissTmpValue  = valueHolderForOnWillDismiss!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDismissTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTransition  = value.transition
        if (valueHolderForTransition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTransitionTmpValue  = valueHolderForTransition!
            TransitionEffect_serializer.write(valueSerializer, valueHolderForTransitionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCornerRadius  = value.cornerRadius
        if (valueHolderForCornerRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCornerRadiusTmpValue  = valueHolderForCornerRadius!
            if (valueHolderForCornerRadiusTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx0  = valueHolderForCornerRadiusTmpValue as Dimension
                if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx0  = valueHolderForCornerRadiusTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForCornerRadiusTmpValueForIdx0ForIdx0)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx1  = valueHolderForCornerRadiusTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForCornerRadiusTmpValueForIdx0ForIdx1)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx2  = valueHolderForCornerRadiusTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForCornerRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx1  = valueHolderForCornerRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx1)
            } else if (valueHolderForCornerRadiusTmpValue instanceof LocalizedBorderRadiuses) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx2  = valueHolderForCornerRadiusTmpValue as LocalizedBorderRadiuses
                LocalizedBorderRadiuses_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForHeightTmpValueForIdx2  = valueHolderForHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderWidth  = value.borderWidth
        if (valueHolderForBorderWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderWidthTmpValue  = valueHolderForBorderWidth!
            if (valueHolderForBorderWidthTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderWidthTmpValueForIdx0  = valueHolderForBorderWidthTmpValue as Dimension
                if (valueHolderForBorderWidthTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx0  = valueHolderForBorderWidthTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderWidthTmpValueForIdx0ForIdx0)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx1  = valueHolderForBorderWidthTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderWidthTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx2  = valueHolderForBorderWidthTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForBorderWidthTmpValue instanceof EdgeWidths) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderWidthTmpValueForIdx1  = valueHolderForBorderWidthTmpValue as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx1)
            } else if (valueHolderForBorderWidthTmpValue instanceof LocalizedEdgeWidths) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderWidthTmpValueForIdx2  = valueHolderForBorderWidthTmpValue as LocalizedEdgeWidths
                LocalizedEdgeWidths_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderColor  = value.borderColor
        if (valueHolderForBorderColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderColorTmpValue  = valueHolderForBorderColor!
            if (valueHolderForBorderColorTmpValue instanceof ResourceColor) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderColorTmpValueForIdx0  = valueHolderForBorderColorTmpValue as ResourceColor
                if (valueHolderForBorderColorTmpValueForIdx0 instanceof Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx0  = valueHolderForBorderColorTmpValueForIdx0 as Color
                    valueSerializer.writeInt32(valueHolderForBorderColorTmpValueForIdx0ForIdx0.getOrdinal())
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx1  = valueHolderForBorderColorTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderColorTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx2  = valueHolderForBorderColorTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderColorTmpValueForIdx0ForIdx2)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx3  = valueHolderForBorderColorTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx0ForIdx3)
                }
            } else if (valueHolderForBorderColorTmpValue instanceof EdgeColors) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderColorTmpValueForIdx1  = valueHolderForBorderColorTmpValue as EdgeColors
                EdgeColors_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx1)
            } else if (valueHolderForBorderColorTmpValue instanceof LocalizedEdgeColors) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderColorTmpValueForIdx2  = valueHolderForBorderColorTmpValue as LocalizedEdgeColors
                LocalizedEdgeColors_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderStyle  = value.borderStyle
        if (valueHolderForBorderStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderStyleTmpValue  = valueHolderForBorderStyle!
            if (valueHolderForBorderStyleTmpValue instanceof BorderStyle) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderStyleTmpValueForIdx0  = valueHolderForBorderStyleTmpValue as BorderStyle
                valueSerializer.writeInt32(valueHolderForBorderStyleTmpValueForIdx0.valueOf())
            } else if (valueHolderForBorderStyleTmpValue instanceof EdgeStyles) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderStyleTmpValueForIdx1  = valueHolderForBorderStyleTmpValue as EdgeStyles
                EdgeStyles_serializer.write(valueSerializer, valueHolderForBorderStyleTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShadow  = value.shadow
        if (valueHolderForShadow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShadowTmpValue  = valueHolderForShadow!
            if (valueHolderForShadowTmpValue instanceof ShadowOptions) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForShadowTmpValueForIdx0  = valueHolderForShadowTmpValue as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, valueHolderForShadowTmpValueForIdx0)
            } else if (valueHolderForShadowTmpValue instanceof ShadowStyle) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForShadowTmpValueForIdx1  = valueHolderForShadowTmpValue as ShadowStyle
                valueSerializer.writeInt32(valueHolderForShadowTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextStyle  = value.textStyle
        if (valueHolderForTextStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextStyleTmpValue  = valueHolderForTextStyle!
            AlertDialogTextStyleOptions_serializer.write(valueSerializer, valueHolderForTextStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableHoverMode  = value.enableHoverMode
        if (valueHolderForEnableHoverMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableHoverModeTmpValue  = valueHolderForEnableHoverMode!
            valueSerializer.writeBoolean(valueHolderForEnableHoverModeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHoverModeArea  = value.hoverModeArea
        if (valueHolderForHoverModeArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHoverModeAreaTmpValue  = (valueHolderForHoverModeArea as HoverModeAreaType)
            valueSerializer.writeInt32(valueHolderForHoverModeAreaTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidAppear  = value.onDidAppear
        if (valueHolderForOnDidAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidAppearTmpValue  = valueHolderForOnDidAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidDisappear  = value.onDidDisappear
        if (valueHolderForOnDidDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidDisappearTmpValue  = valueHolderForOnDidDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillAppear  = value.onWillAppear
        if (valueHolderForOnWillAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillAppearTmpValue  = valueHolderForOnWillAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDisappear  = value.onWillDisappear
        if (valueHolderForOnWillDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDisappearTmpValue  = valueHolderForOnWillDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelMode  = value.levelMode
        if (valueHolderForLevelMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelModeTmpValue  = (valueHolderForLevelMode as LevelMode)
            valueSerializer.writeInt32(valueHolderForLevelModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelUniqueId  = value.levelUniqueId
        if (valueHolderForLevelUniqueId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelUniqueIdTmpValue  = valueHolderForLevelUniqueId!
            valueSerializer.writeInt32(valueHolderForLevelUniqueIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImmersiveMode  = value.immersiveMode
        if (valueHolderForImmersiveMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImmersiveModeTmpValue  = (valueHolderForImmersiveMode as ImmersiveMode)
            valueSerializer.writeInt32(valueHolderForImmersiveModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelOrder  = value.levelOrder
        if (valueHolderForLevelOrder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelOrderTmpValue  = valueHolderForLevelOrder!
            LevelOrder_serializer.write(valueSerializer, valueHolderForLevelOrderTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForConfirm  = value.confirm
        if (valueHolderForConfirm !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForConfirmTmpValue  = valueHolderForConfirm!
            AlertDialogButtonBaseOptions_serializer.write(valueSerializer, valueHolderForConfirmTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): AlertDialogParamWithConfirm {
        let valueDeserializer : DeserializerBase = buffer
        const titleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let titleTmpBuf : ResourceStr | undefined = undefined
        if ((titleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const titleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let titleTmpBuf_ : string | Resource | undefined
            if (titleTmpBuf_UnionSelector == (0).toChar()) {
                titleTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (titleTmpBuf_UnionSelector == (1).toChar()) {
                titleTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for titleTmpBuf_ has to be chosen through deserialisation.")
            }
            titleTmpBuf = (titleTmpBuf_ as string | Resource)
        }
        const titleTmpResult : ResourceStr | undefined = titleTmpBuf
        const subtitleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let subtitleTmpBuf : ResourceStr | undefined = undefined
        if ((subtitleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const subtitleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let subtitleTmpBuf_ : string | Resource | undefined
            if (subtitleTmpBuf_UnionSelector == (0).toChar()) {
                subtitleTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (subtitleTmpBuf_UnionSelector == (1).toChar()) {
                subtitleTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for subtitleTmpBuf_ has to be chosen through deserialisation.")
            }
            subtitleTmpBuf = (subtitleTmpBuf_ as string | Resource)
        }
        const subtitleTmpResult : ResourceStr | undefined = subtitleTmpBuf
        const messageTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let messageTmpBuf : string | Resource | undefined
        if (messageTmpBufUnionSelector == (0).toChar()) {
            messageTmpBuf = (valueDeserializer.readString() as string)
        } else if (messageTmpBufUnionSelector == (1).toChar()) {
            messageTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for messageTmpBuf has to be chosen through deserialisation.")
        }
        const messageTmpResult : ResourceStr = (messageTmpBuf as string | Resource)
        const autoCancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let autoCancelTmpBuf : boolean | undefined = undefined
        if ((autoCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            autoCancelTmpBuf = valueDeserializer.readBoolean()
        }
        const autoCancelTmpResult : boolean | undefined = autoCancelTmpBuf
        const cancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cancelTmpBuf : VoidCallback | undefined = undefined
        if ((cancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cancelTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const cancelTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const cancelTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            cancelTmpBuf = ():void => {
                const cancelTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                cancelTmpBuf_BufArgsSerializer.writeInt32(cancelTmpBuf_BufResource.resourceId);
                cancelTmpBuf_BufArgsSerializer.writePointer(cancelTmpBuf_BufCall);
                cancelTmpBuf_BufArgsSerializer.writePointer(cancelTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, cancelTmpBuf_BufArgsSerializer.asBuffer(), cancelTmpBuf_BufArgsSerializer.length());
                cancelTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const cancelTmpResult : VoidCallback | undefined = cancelTmpBuf
        const alignmentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignmentTmpBuf : DialogAlignment | undefined = undefined
        if ((alignmentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignmentTmpBuf = DialogAlignment.fromValue(valueDeserializer.readInt32())
        }
        const alignmentTmpResult : DialogAlignment | undefined = alignmentTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetTmpBuf : Offset | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = Offset_serializer.read(valueDeserializer)
        }
        const offsetTmpResult : Offset | undefined = offsetTmpBuf
        const gridCountTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let gridCountTmpBuf : int32 | undefined = undefined
        if ((gridCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            gridCountTmpBuf = valueDeserializer.readInt32()
        }
        const gridCountTmpResult : int32 | undefined = gridCountTmpBuf
        const maskRectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maskRectTmpBuf : Rectangle | undefined = undefined
        if ((maskRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maskRectTmpBuf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRectTmpResult : Rectangle | undefined = maskRectTmpBuf
        const showInSubWindowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showInSubWindowTmpBuf : boolean | undefined = undefined
        if ((showInSubWindowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showInSubWindowTmpBuf = valueDeserializer.readBoolean()
        }
        const showInSubWindowTmpResult : boolean | undefined = showInSubWindowTmpBuf
        const isModalTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isModalTmpBuf : boolean | undefined = undefined
        if ((isModalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isModalTmpBuf = valueDeserializer.readBoolean()
        }
        const isModalTmpResult : boolean | undefined = isModalTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const onWillDismissTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDismissTmpBuf : ((value0: DismissDialogAction) => void) | undefined = undefined
        if ((onWillDismissTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDismissTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDismissTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDismissTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDismissTmpBuf = (value0: DismissDialogAction):void => {
                const onWillDismissTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDismissTmpBuf_BufArgsSerializer.writeInt32(onWillDismissTmpBuf_BufResource.resourceId);
                onWillDismissTmpBuf_BufArgsSerializer.writePointer(onWillDismissTmpBuf_BufCall);
                onWillDismissTmpBuf_BufArgsSerializer.writePointer(onWillDismissTmpBuf_BufCallSync);
                DismissDialogAction_serializer.write(onWillDismissTmpBuf_BufArgsSerializer, value0);
                InteropNativeModule._CallCallbackSync(10, -2095828093, onWillDismissTmpBuf_BufArgsSerializer.asBuffer(), onWillDismissTmpBuf_BufArgsSerializer.length());
                onWillDismissTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDismissTmpResult : ((value0: DismissDialogAction) => void) | undefined = onWillDismissTmpBuf
        const transitionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let transitionTmpBuf : TransitionEffect | undefined = undefined
        if ((transitionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            transitionTmpBuf = (TransitionEffect_serializer.read(valueDeserializer) as TransitionEffect)
        }
        const transitionTmpResult : TransitionEffect | undefined = transitionTmpBuf
        const cornerRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cornerRadiusTmpBuf : Dimension | BorderRadiuses | LocalizedBorderRadiuses | undefined = undefined
        if ((cornerRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cornerRadiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let cornerRadiusTmpBuf_ : Dimension | BorderRadiuses | LocalizedBorderRadiuses | undefined
            if (cornerRadiusTmpBuf_UnionSelector == (0).toChar()) {
                const cornerRadiusTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let cornerRadiusTmpBuf_BufU : string | number | Resource | undefined
                if (cornerRadiusTmpBuf_BufUUnionSelector == (0).toChar()) {
                    cornerRadiusTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (cornerRadiusTmpBuf_BufUUnionSelector == (1).toChar()) {
                    cornerRadiusTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (cornerRadiusTmpBuf_BufUUnionSelector == (2).toChar()) {
                    cornerRadiusTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for cornerRadiusTmpBuf_BufU has to be chosen through deserialisation.")
                }
                cornerRadiusTmpBuf_ = (cornerRadiusTmpBuf_BufU as string | number | Resource)
            } else if (cornerRadiusTmpBuf_UnionSelector == (1).toChar()) {
                cornerRadiusTmpBuf_ = BorderRadiuses_serializer.read(valueDeserializer)
            } else if (cornerRadiusTmpBuf_UnionSelector == (2).toChar()) {
                cornerRadiusTmpBuf_ = LocalizedBorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for cornerRadiusTmpBuf_ has to be chosen through deserialisation.")
            }
            cornerRadiusTmpBuf = (cornerRadiusTmpBuf_ as Dimension | BorderRadiuses | LocalizedBorderRadiuses)
        }
        const cornerRadiusTmpResult : Dimension | BorderRadiuses | LocalizedBorderRadiuses | undefined = cornerRadiusTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : Dimension | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : string | number | Resource | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBuf_UnionSelector == (2).toChar()) {
                widthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as string | number | Resource)
        }
        const widthTmpResult : Dimension | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : Dimension | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : string | number | Resource | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBuf_UnionSelector == (2).toChar()) {
                heightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as string | number | Resource)
        }
        const heightTmpResult : Dimension | undefined = heightTmpBuf
        const borderWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderWidthTmpBuf : Dimension | EdgeWidths | LocalizedEdgeWidths | undefined = undefined
        if ((borderWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderWidthTmpBuf_ : Dimension | EdgeWidths | LocalizedEdgeWidths | undefined
            if (borderWidthTmpBuf_UnionSelector == (0).toChar()) {
                const borderWidthTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderWidthTmpBuf_BufU : string | number | Resource | undefined
                if (borderWidthTmpBuf_BufUUnionSelector == (0).toChar()) {
                    borderWidthTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (borderWidthTmpBuf_BufUUnionSelector == (1).toChar()) {
                    borderWidthTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (borderWidthTmpBuf_BufUUnionSelector == (2).toChar()) {
                    borderWidthTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for borderWidthTmpBuf_BufU has to be chosen through deserialisation.")
                }
                borderWidthTmpBuf_ = (borderWidthTmpBuf_BufU as string | number | Resource)
            } else if (borderWidthTmpBuf_UnionSelector == (1).toChar()) {
                borderWidthTmpBuf_ = EdgeWidths_serializer.read(valueDeserializer)
            } else if (borderWidthTmpBuf_UnionSelector == (2).toChar()) {
                borderWidthTmpBuf_ = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            borderWidthTmpBuf = (borderWidthTmpBuf_ as Dimension | EdgeWidths | LocalizedEdgeWidths)
        }
        const borderWidthTmpResult : Dimension | EdgeWidths | LocalizedEdgeWidths | undefined = borderWidthTmpBuf
        const borderColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderColorTmpBuf : ResourceColor | EdgeColors | LocalizedEdgeColors | undefined = undefined
        if ((borderColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderColorTmpBuf_ : ResourceColor | EdgeColors | LocalizedEdgeColors | undefined
            if (borderColorTmpBuf_UnionSelector == (0).toChar()) {
                const borderColorTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderColorTmpBuf_BufU : Color | number | string | Resource | undefined
                if (borderColorTmpBuf_BufUUnionSelector == (0).toChar()) {
                    borderColorTmpBuf_BufU = Color.values()[valueDeserializer.readInt32()]
                } else if (borderColorTmpBuf_BufUUnionSelector == (1).toChar()) {
                    borderColorTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (borderColorTmpBuf_BufUUnionSelector == (2).toChar()) {
                    borderColorTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (borderColorTmpBuf_BufUUnionSelector == (3).toChar()) {
                    borderColorTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for borderColorTmpBuf_BufU has to be chosen through deserialisation.")
                }
                borderColorTmpBuf_ = (borderColorTmpBuf_BufU as Color | number | string | Resource)
            } else if (borderColorTmpBuf_UnionSelector == (1).toChar()) {
                borderColorTmpBuf_ = EdgeColors_serializer.read(valueDeserializer)
            } else if (borderColorTmpBuf_UnionSelector == (2).toChar()) {
                borderColorTmpBuf_ = LocalizedEdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderColorTmpBuf_ has to be chosen through deserialisation.")
            }
            borderColorTmpBuf = (borderColorTmpBuf_ as ResourceColor | EdgeColors | LocalizedEdgeColors)
        }
        const borderColorTmpResult : ResourceColor | EdgeColors | LocalizedEdgeColors | undefined = borderColorTmpBuf
        const borderStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderStyleTmpBuf : BorderStyle | EdgeStyles | undefined = undefined
        if ((borderStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderStyleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderStyleTmpBuf_ : BorderStyle | EdgeStyles | undefined
            if (borderStyleTmpBuf_UnionSelector == (0).toChar()) {
                borderStyleTmpBuf_ = BorderStyle.fromValue(valueDeserializer.readInt32())
            } else if (borderStyleTmpBuf_UnionSelector == (1).toChar()) {
                borderStyleTmpBuf_ = EdgeStyles_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderStyleTmpBuf_ has to be chosen through deserialisation.")
            }
            borderStyleTmpBuf = (borderStyleTmpBuf_ as BorderStyle | EdgeStyles)
        }
        const borderStyleTmpResult : BorderStyle | EdgeStyles | undefined = borderStyleTmpBuf
        const shadowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shadowTmpBuf : ShadowOptions | ShadowStyle | undefined = undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shadowTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let shadowTmpBuf_ : ShadowOptions | ShadowStyle | undefined
            if (shadowTmpBuf_UnionSelector == (0).toChar()) {
                shadowTmpBuf_ = ShadowOptions_serializer.read(valueDeserializer)
            } else if (shadowTmpBuf_UnionSelector == (1).toChar()) {
                shadowTmpBuf_ = ShadowStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for shadowTmpBuf_ has to be chosen through deserialisation.")
            }
            shadowTmpBuf = (shadowTmpBuf_ as ShadowOptions | ShadowStyle)
        }
        const shadowTmpResult : ShadowOptions | ShadowStyle | undefined = shadowTmpBuf
        const textStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textStyleTmpBuf : AlertDialogTextStyleOptions | undefined = undefined
        if ((textStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textStyleTmpBuf = AlertDialogTextStyleOptions_serializer.read(valueDeserializer)
        }
        const textStyleTmpResult : AlertDialogTextStyleOptions | undefined = textStyleTmpBuf
        const enableHoverModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHoverModeTmpBuf : boolean | undefined = undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult : boolean | undefined = enableHoverModeTmpBuf
        const hoverModeAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hoverModeAreaTmpBuf : HoverModeAreaType | undefined = undefined
        if ((hoverModeAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hoverModeAreaTmpBuf = HoverModeAreaType.fromValue(valueDeserializer.readInt32())
        }
        const hoverModeAreaTmpResult : HoverModeAreaType | undefined = hoverModeAreaTmpBuf
        const onDidAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidAppearTmpBuf : (() => void) | undefined = undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidAppearTmpBuf = ():void => {
                const onDidAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidAppearTmpBuf_BufArgsSerializer.writeInt32(onDidAppearTmpBuf_BufResource.resourceId);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCall);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onDidAppearTmpBuf_BufArgsSerializer.asBuffer(), onDidAppearTmpBuf_BufArgsSerializer.length());
                onDidAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidAppearTmpResult : (() => void) | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidDisappearTmpBuf = ():void => {
                const onDidDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBuf_BufArgsSerializer.writeInt32(onDidDisappearTmpBuf_BufResource.resourceId);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCall);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onDidDisappearTmpBuf_BufArgsSerializer.asBuffer(), onDidDisappearTmpBuf_BufArgsSerializer.length());
                onDidDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidDisappearTmpResult : (() => void) | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillAppearTmpBuf : (() => void) | undefined = undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillAppearTmpBuf = ():void => {
                const onWillAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillAppearTmpBuf_BufArgsSerializer.writeInt32(onWillAppearTmpBuf_BufResource.resourceId);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCall);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onWillAppearTmpBuf_BufArgsSerializer.asBuffer(), onWillAppearTmpBuf_BufArgsSerializer.length());
                onWillAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillAppearTmpResult : (() => void) | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDisappearTmpBuf = ():void => {
                const onWillDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBuf_BufArgsSerializer.writeInt32(onWillDisappearTmpBuf_BufResource.resourceId);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCall);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onWillDisappearTmpBuf_BufArgsSerializer.asBuffer(), onWillDisappearTmpBuf_BufArgsSerializer.length());
                onWillDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDisappearTmpResult : (() => void) | undefined = onWillDisappearTmpBuf
        const levelModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelModeTmpBuf : LevelMode | undefined = undefined
        if ((levelModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelModeTmpBuf = LevelMode.fromValue(valueDeserializer.readInt32())
        }
        const levelModeTmpResult : LevelMode | undefined = levelModeTmpBuf
        const levelUniqueIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelUniqueIdTmpBuf : int32 | undefined = undefined
        if ((levelUniqueIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelUniqueIdTmpBuf = valueDeserializer.readInt32()
        }
        const levelUniqueIdTmpResult : int32 | undefined = levelUniqueIdTmpBuf
        const immersiveModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let immersiveModeTmpBuf : ImmersiveMode | undefined = undefined
        if ((immersiveModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            immersiveModeTmpBuf = ImmersiveMode.fromValue(valueDeserializer.readInt32())
        }
        const immersiveModeTmpResult : ImmersiveMode | undefined = immersiveModeTmpBuf
        const levelOrderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelOrderTmpBuf : LevelOrder | undefined = undefined
        if ((levelOrderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelOrderTmpBuf = (LevelOrder_serializer.read(valueDeserializer) as LevelOrder)
        }
        const levelOrderTmpResult : LevelOrder | undefined = levelOrderTmpBuf
        const confirmTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let confirmTmpBuf : AlertDialogButtonBaseOptions | undefined = undefined
        if ((confirmTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            confirmTmpBuf = AlertDialogButtonBaseOptions_serializer.read(valueDeserializer)
        }
        const confirmTmpResult : AlertDialogButtonBaseOptions | undefined = confirmTmpBuf
        let value : AlertDialogParamWithConfirm = ({title: titleTmpResult, subtitle: subtitleTmpResult, message: messageTmpResult, autoCancel: autoCancelTmpResult, cancel: cancelTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, gridCount: gridCountTmpResult, maskRect: maskRectTmpResult, showInSubWindow: showInSubWindowTmpResult, isModal: isModalTmpResult, backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, onWillDismiss: onWillDismissTmpResult, transition: transitionTmpResult, cornerRadius: cornerRadiusTmpResult, width: widthTmpResult, height: heightTmpResult, borderWidth: borderWidthTmpResult, borderColor: borderColorTmpResult, borderStyle: borderStyleTmpResult, shadow: shadowTmpResult, textStyle: textStyleTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, levelMode: levelModeTmpResult, levelUniqueId: levelUniqueIdTmpResult, immersiveMode: immersiveModeTmpResult, levelOrder: levelOrderTmpResult, confirm: confirmTmpResult} as AlertDialogParamWithConfirm)
        return value
    }
}
export class AlertDialogParamWithOptions_serializer {
    public static write(buffer: SerializerBase, value: AlertDialogParamWithOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTitle  = value.title
        if (valueHolderForTitle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTitleTmpValue  = valueHolderForTitle!
            if (valueHolderForTitleTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTitleTmpValueForIdx0  = valueHolderForTitleTmpValue as string
                valueSerializer.writeString(valueHolderForTitleTmpValueForIdx0)
            } else if (valueHolderForTitleTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTitleTmpValueForIdx1  = valueHolderForTitleTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTitleTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSubtitle  = value.subtitle
        if (valueHolderForSubtitle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSubtitleTmpValue  = valueHolderForSubtitle!
            if (valueHolderForSubtitleTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSubtitleTmpValueForIdx0  = valueHolderForSubtitleTmpValue as string
                valueSerializer.writeString(valueHolderForSubtitleTmpValueForIdx0)
            } else if (valueHolderForSubtitleTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSubtitleTmpValueForIdx1  = valueHolderForSubtitleTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSubtitleTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMessage  = value.message
        if (valueHolderForMessage instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForMessageForIdx0  = valueHolderForMessage as string
            valueSerializer.writeString(valueHolderForMessageForIdx0)
        } else if (valueHolderForMessage instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForMessageForIdx1  = valueHolderForMessage as Resource
            Resource_serializer.write(valueSerializer, valueHolderForMessageForIdx1)
        }
        const valueHolderForAutoCancel  = value.autoCancel
        if (valueHolderForAutoCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAutoCancelTmpValue  = valueHolderForAutoCancel!
            valueSerializer.writeBoolean(valueHolderForAutoCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCancel  = value.cancel
        if (valueHolderForCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCancelTmpValue  = valueHolderForCancel!
            valueSerializer.holdAndWriteCallback(valueHolderForCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlignment  = value.alignment
        if (valueHolderForAlignment !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignmentTmpValue  = (valueHolderForAlignment as DialogAlignment)
            valueSerializer.writeInt32(valueHolderForAlignmentTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            Offset_serializer.write(valueSerializer, valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForGridCount  = value.gridCount
        if (valueHolderForGridCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGridCountTmpValue  = valueHolderForGridCount!
            valueSerializer.writeInt32(valueHolderForGridCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaskRect  = value.maskRect
        if (valueHolderForMaskRect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaskRectTmpValue  = valueHolderForMaskRect!
            Rectangle_serializer.write(valueSerializer, valueHolderForMaskRectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShowInSubWindow  = value.showInSubWindow
        if (valueHolderForShowInSubWindow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowInSubWindowTmpValue  = valueHolderForShowInSubWindow!
            valueSerializer.writeBoolean(valueHolderForShowInSubWindowTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIsModal  = value.isModal
        if (valueHolderForIsModal !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsModalTmpValue  = valueHolderForIsModal!
            valueSerializer.writeBoolean(valueHolderForIsModalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyle  = value.backgroundBlurStyle
        if (valueHolderForBackgroundBlurStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleTmpValue  = (valueHolderForBackgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(valueHolderForBackgroundBlurStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        if (valueHolderForBackgroundBlurStyleOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleOptionsTmpValue  = valueHolderForBackgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, valueHolderForBackgroundBlurStyleOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundEffect  = value.backgroundEffect
        if (valueHolderForBackgroundEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundEffectTmpValue  = valueHolderForBackgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, valueHolderForBackgroundEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDismiss  = value.onWillDismiss
        if (valueHolderForOnWillDismiss !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDismissTmpValue  = valueHolderForOnWillDismiss!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDismissTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTransition  = value.transition
        if (valueHolderForTransition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTransitionTmpValue  = valueHolderForTransition!
            TransitionEffect_serializer.write(valueSerializer, valueHolderForTransitionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCornerRadius  = value.cornerRadius
        if (valueHolderForCornerRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCornerRadiusTmpValue  = valueHolderForCornerRadius!
            if (valueHolderForCornerRadiusTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx0  = valueHolderForCornerRadiusTmpValue as Dimension
                if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx0  = valueHolderForCornerRadiusTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForCornerRadiusTmpValueForIdx0ForIdx0)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx1  = valueHolderForCornerRadiusTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForCornerRadiusTmpValueForIdx0ForIdx1)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx2  = valueHolderForCornerRadiusTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForCornerRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx1  = valueHolderForCornerRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx1)
            } else if (valueHolderForCornerRadiusTmpValue instanceof LocalizedBorderRadiuses) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx2  = valueHolderForCornerRadiusTmpValue as LocalizedBorderRadiuses
                LocalizedBorderRadiuses_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForHeightTmpValueForIdx2  = valueHolderForHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderWidth  = value.borderWidth
        if (valueHolderForBorderWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderWidthTmpValue  = valueHolderForBorderWidth!
            if (valueHolderForBorderWidthTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderWidthTmpValueForIdx0  = valueHolderForBorderWidthTmpValue as Dimension
                if (valueHolderForBorderWidthTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx0  = valueHolderForBorderWidthTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderWidthTmpValueForIdx0ForIdx0)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx1  = valueHolderForBorderWidthTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderWidthTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx2  = valueHolderForBorderWidthTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForBorderWidthTmpValue instanceof EdgeWidths) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderWidthTmpValueForIdx1  = valueHolderForBorderWidthTmpValue as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx1)
            } else if (valueHolderForBorderWidthTmpValue instanceof LocalizedEdgeWidths) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderWidthTmpValueForIdx2  = valueHolderForBorderWidthTmpValue as LocalizedEdgeWidths
                LocalizedEdgeWidths_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderColor  = value.borderColor
        if (valueHolderForBorderColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderColorTmpValue  = valueHolderForBorderColor!
            if (valueHolderForBorderColorTmpValue instanceof ResourceColor) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderColorTmpValueForIdx0  = valueHolderForBorderColorTmpValue as ResourceColor
                if (valueHolderForBorderColorTmpValueForIdx0 instanceof Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx0  = valueHolderForBorderColorTmpValueForIdx0 as Color
                    valueSerializer.writeInt32(valueHolderForBorderColorTmpValueForIdx0ForIdx0.getOrdinal())
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx1  = valueHolderForBorderColorTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderColorTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx2  = valueHolderForBorderColorTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderColorTmpValueForIdx0ForIdx2)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx3  = valueHolderForBorderColorTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx0ForIdx3)
                }
            } else if (valueHolderForBorderColorTmpValue instanceof EdgeColors) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderColorTmpValueForIdx1  = valueHolderForBorderColorTmpValue as EdgeColors
                EdgeColors_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx1)
            } else if (valueHolderForBorderColorTmpValue instanceof LocalizedEdgeColors) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderColorTmpValueForIdx2  = valueHolderForBorderColorTmpValue as LocalizedEdgeColors
                LocalizedEdgeColors_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderStyle  = value.borderStyle
        if (valueHolderForBorderStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderStyleTmpValue  = valueHolderForBorderStyle!
            if (valueHolderForBorderStyleTmpValue instanceof BorderStyle) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderStyleTmpValueForIdx0  = valueHolderForBorderStyleTmpValue as BorderStyle
                valueSerializer.writeInt32(valueHolderForBorderStyleTmpValueForIdx0.valueOf())
            } else if (valueHolderForBorderStyleTmpValue instanceof EdgeStyles) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderStyleTmpValueForIdx1  = valueHolderForBorderStyleTmpValue as EdgeStyles
                EdgeStyles_serializer.write(valueSerializer, valueHolderForBorderStyleTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShadow  = value.shadow
        if (valueHolderForShadow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShadowTmpValue  = valueHolderForShadow!
            if (valueHolderForShadowTmpValue instanceof ShadowOptions) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForShadowTmpValueForIdx0  = valueHolderForShadowTmpValue as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, valueHolderForShadowTmpValueForIdx0)
            } else if (valueHolderForShadowTmpValue instanceof ShadowStyle) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForShadowTmpValueForIdx1  = valueHolderForShadowTmpValue as ShadowStyle
                valueSerializer.writeInt32(valueHolderForShadowTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextStyle  = value.textStyle
        if (valueHolderForTextStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextStyleTmpValue  = valueHolderForTextStyle!
            AlertDialogTextStyleOptions_serializer.write(valueSerializer, valueHolderForTextStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableHoverMode  = value.enableHoverMode
        if (valueHolderForEnableHoverMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableHoverModeTmpValue  = valueHolderForEnableHoverMode!
            valueSerializer.writeBoolean(valueHolderForEnableHoverModeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHoverModeArea  = value.hoverModeArea
        if (valueHolderForHoverModeArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHoverModeAreaTmpValue  = (valueHolderForHoverModeArea as HoverModeAreaType)
            valueSerializer.writeInt32(valueHolderForHoverModeAreaTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidAppear  = value.onDidAppear
        if (valueHolderForOnDidAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidAppearTmpValue  = valueHolderForOnDidAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidDisappear  = value.onDidDisappear
        if (valueHolderForOnDidDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidDisappearTmpValue  = valueHolderForOnDidDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillAppear  = value.onWillAppear
        if (valueHolderForOnWillAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillAppearTmpValue  = valueHolderForOnWillAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDisappear  = value.onWillDisappear
        if (valueHolderForOnWillDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDisappearTmpValue  = valueHolderForOnWillDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelMode  = value.levelMode
        if (valueHolderForLevelMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelModeTmpValue  = (valueHolderForLevelMode as LevelMode)
            valueSerializer.writeInt32(valueHolderForLevelModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelUniqueId  = value.levelUniqueId
        if (valueHolderForLevelUniqueId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelUniqueIdTmpValue  = valueHolderForLevelUniqueId!
            valueSerializer.writeInt32(valueHolderForLevelUniqueIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImmersiveMode  = value.immersiveMode
        if (valueHolderForImmersiveMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImmersiveModeTmpValue  = (valueHolderForImmersiveMode as ImmersiveMode)
            valueSerializer.writeInt32(valueHolderForImmersiveModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelOrder  = value.levelOrder
        if (valueHolderForLevelOrder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelOrderTmpValue  = valueHolderForLevelOrder!
            LevelOrder_serializer.write(valueSerializer, valueHolderForLevelOrderTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForButtons  = value.buttons
        valueSerializer.writeInt32((valueHolderForButtons.length).toInt())
        for (let valueHolderForButtonsCounterI = 0; valueHolderForButtonsCounterI < valueHolderForButtons.length; valueHolderForButtonsCounterI++) {
            const valueHolderForButtonsTmpElement : AlertDialogButtonOptions = valueHolderForButtons[valueHolderForButtonsCounterI]
            AlertDialogButtonOptions_serializer.write(valueSerializer, valueHolderForButtonsTmpElement)
        }
        const valueHolderForButtonDirection  = value.buttonDirection
        if (valueHolderForButtonDirection !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForButtonDirectionTmpValue  = (valueHolderForButtonDirection as DialogButtonDirection)
            valueSerializer.writeInt32(valueHolderForButtonDirectionTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): AlertDialogParamWithOptions {
        let valueDeserializer : DeserializerBase = buffer
        const titleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let titleTmpBuf : ResourceStr | undefined = undefined
        if ((titleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const titleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let titleTmpBuf_ : string | Resource | undefined
            if (titleTmpBuf_UnionSelector == (0).toChar()) {
                titleTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (titleTmpBuf_UnionSelector == (1).toChar()) {
                titleTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for titleTmpBuf_ has to be chosen through deserialisation.")
            }
            titleTmpBuf = (titleTmpBuf_ as string | Resource)
        }
        const titleTmpResult : ResourceStr | undefined = titleTmpBuf
        const subtitleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let subtitleTmpBuf : ResourceStr | undefined = undefined
        if ((subtitleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const subtitleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let subtitleTmpBuf_ : string | Resource | undefined
            if (subtitleTmpBuf_UnionSelector == (0).toChar()) {
                subtitleTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (subtitleTmpBuf_UnionSelector == (1).toChar()) {
                subtitleTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for subtitleTmpBuf_ has to be chosen through deserialisation.")
            }
            subtitleTmpBuf = (subtitleTmpBuf_ as string | Resource)
        }
        const subtitleTmpResult : ResourceStr | undefined = subtitleTmpBuf
        const messageTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let messageTmpBuf : string | Resource | undefined
        if (messageTmpBufUnionSelector == (0).toChar()) {
            messageTmpBuf = (valueDeserializer.readString() as string)
        } else if (messageTmpBufUnionSelector == (1).toChar()) {
            messageTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for messageTmpBuf has to be chosen through deserialisation.")
        }
        const messageTmpResult : ResourceStr = (messageTmpBuf as string | Resource)
        const autoCancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let autoCancelTmpBuf : boolean | undefined = undefined
        if ((autoCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            autoCancelTmpBuf = valueDeserializer.readBoolean()
        }
        const autoCancelTmpResult : boolean | undefined = autoCancelTmpBuf
        const cancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cancelTmpBuf : VoidCallback | undefined = undefined
        if ((cancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cancelTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const cancelTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const cancelTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            cancelTmpBuf = ():void => {
                const cancelTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                cancelTmpBuf_BufArgsSerializer.writeInt32(cancelTmpBuf_BufResource.resourceId);
                cancelTmpBuf_BufArgsSerializer.writePointer(cancelTmpBuf_BufCall);
                cancelTmpBuf_BufArgsSerializer.writePointer(cancelTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, cancelTmpBuf_BufArgsSerializer.asBuffer(), cancelTmpBuf_BufArgsSerializer.length());
                cancelTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const cancelTmpResult : VoidCallback | undefined = cancelTmpBuf
        const alignmentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignmentTmpBuf : DialogAlignment | undefined = undefined
        if ((alignmentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignmentTmpBuf = DialogAlignment.fromValue(valueDeserializer.readInt32())
        }
        const alignmentTmpResult : DialogAlignment | undefined = alignmentTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetTmpBuf : Offset | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = Offset_serializer.read(valueDeserializer)
        }
        const offsetTmpResult : Offset | undefined = offsetTmpBuf
        const gridCountTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let gridCountTmpBuf : int32 | undefined = undefined
        if ((gridCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            gridCountTmpBuf = valueDeserializer.readInt32()
        }
        const gridCountTmpResult : int32 | undefined = gridCountTmpBuf
        const maskRectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maskRectTmpBuf : Rectangle | undefined = undefined
        if ((maskRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maskRectTmpBuf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRectTmpResult : Rectangle | undefined = maskRectTmpBuf
        const showInSubWindowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showInSubWindowTmpBuf : boolean | undefined = undefined
        if ((showInSubWindowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showInSubWindowTmpBuf = valueDeserializer.readBoolean()
        }
        const showInSubWindowTmpResult : boolean | undefined = showInSubWindowTmpBuf
        const isModalTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isModalTmpBuf : boolean | undefined = undefined
        if ((isModalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isModalTmpBuf = valueDeserializer.readBoolean()
        }
        const isModalTmpResult : boolean | undefined = isModalTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const onWillDismissTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDismissTmpBuf : ((value0: DismissDialogAction) => void) | undefined = undefined
        if ((onWillDismissTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDismissTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDismissTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDismissTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDismissTmpBuf = (value0: DismissDialogAction):void => {
                const onWillDismissTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDismissTmpBuf_BufArgsSerializer.writeInt32(onWillDismissTmpBuf_BufResource.resourceId);
                onWillDismissTmpBuf_BufArgsSerializer.writePointer(onWillDismissTmpBuf_BufCall);
                onWillDismissTmpBuf_BufArgsSerializer.writePointer(onWillDismissTmpBuf_BufCallSync);
                DismissDialogAction_serializer.write(onWillDismissTmpBuf_BufArgsSerializer, value0);
                InteropNativeModule._CallCallbackSync(10, -2095828093, onWillDismissTmpBuf_BufArgsSerializer.asBuffer(), onWillDismissTmpBuf_BufArgsSerializer.length());
                onWillDismissTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDismissTmpResult : ((value0: DismissDialogAction) => void) | undefined = onWillDismissTmpBuf
        const transitionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let transitionTmpBuf : TransitionEffect | undefined = undefined
        if ((transitionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            transitionTmpBuf = (TransitionEffect_serializer.read(valueDeserializer) as TransitionEffect)
        }
        const transitionTmpResult : TransitionEffect | undefined = transitionTmpBuf
        const cornerRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cornerRadiusTmpBuf : Dimension | BorderRadiuses | LocalizedBorderRadiuses | undefined = undefined
        if ((cornerRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cornerRadiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let cornerRadiusTmpBuf_ : Dimension | BorderRadiuses | LocalizedBorderRadiuses | undefined
            if (cornerRadiusTmpBuf_UnionSelector == (0).toChar()) {
                const cornerRadiusTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let cornerRadiusTmpBuf_BufU : string | number | Resource | undefined
                if (cornerRadiusTmpBuf_BufUUnionSelector == (0).toChar()) {
                    cornerRadiusTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (cornerRadiusTmpBuf_BufUUnionSelector == (1).toChar()) {
                    cornerRadiusTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (cornerRadiusTmpBuf_BufUUnionSelector == (2).toChar()) {
                    cornerRadiusTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for cornerRadiusTmpBuf_BufU has to be chosen through deserialisation.")
                }
                cornerRadiusTmpBuf_ = (cornerRadiusTmpBuf_BufU as string | number | Resource)
            } else if (cornerRadiusTmpBuf_UnionSelector == (1).toChar()) {
                cornerRadiusTmpBuf_ = BorderRadiuses_serializer.read(valueDeserializer)
            } else if (cornerRadiusTmpBuf_UnionSelector == (2).toChar()) {
                cornerRadiusTmpBuf_ = LocalizedBorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for cornerRadiusTmpBuf_ has to be chosen through deserialisation.")
            }
            cornerRadiusTmpBuf = (cornerRadiusTmpBuf_ as Dimension | BorderRadiuses | LocalizedBorderRadiuses)
        }
        const cornerRadiusTmpResult : Dimension | BorderRadiuses | LocalizedBorderRadiuses | undefined = cornerRadiusTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : Dimension | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : string | number | Resource | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBuf_UnionSelector == (2).toChar()) {
                widthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as string | number | Resource)
        }
        const widthTmpResult : Dimension | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : Dimension | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : string | number | Resource | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBuf_UnionSelector == (2).toChar()) {
                heightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as string | number | Resource)
        }
        const heightTmpResult : Dimension | undefined = heightTmpBuf
        const borderWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderWidthTmpBuf : Dimension | EdgeWidths | LocalizedEdgeWidths | undefined = undefined
        if ((borderWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderWidthTmpBuf_ : Dimension | EdgeWidths | LocalizedEdgeWidths | undefined
            if (borderWidthTmpBuf_UnionSelector == (0).toChar()) {
                const borderWidthTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderWidthTmpBuf_BufU : string | number | Resource | undefined
                if (borderWidthTmpBuf_BufUUnionSelector == (0).toChar()) {
                    borderWidthTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (borderWidthTmpBuf_BufUUnionSelector == (1).toChar()) {
                    borderWidthTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (borderWidthTmpBuf_BufUUnionSelector == (2).toChar()) {
                    borderWidthTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for borderWidthTmpBuf_BufU has to be chosen through deserialisation.")
                }
                borderWidthTmpBuf_ = (borderWidthTmpBuf_BufU as string | number | Resource)
            } else if (borderWidthTmpBuf_UnionSelector == (1).toChar()) {
                borderWidthTmpBuf_ = EdgeWidths_serializer.read(valueDeserializer)
            } else if (borderWidthTmpBuf_UnionSelector == (2).toChar()) {
                borderWidthTmpBuf_ = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            borderWidthTmpBuf = (borderWidthTmpBuf_ as Dimension | EdgeWidths | LocalizedEdgeWidths)
        }
        const borderWidthTmpResult : Dimension | EdgeWidths | LocalizedEdgeWidths | undefined = borderWidthTmpBuf
        const borderColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderColorTmpBuf : ResourceColor | EdgeColors | LocalizedEdgeColors | undefined = undefined
        if ((borderColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderColorTmpBuf_ : ResourceColor | EdgeColors | LocalizedEdgeColors | undefined
            if (borderColorTmpBuf_UnionSelector == (0).toChar()) {
                const borderColorTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderColorTmpBuf_BufU : Color | number | string | Resource | undefined
                if (borderColorTmpBuf_BufUUnionSelector == (0).toChar()) {
                    borderColorTmpBuf_BufU = Color.values()[valueDeserializer.readInt32()]
                } else if (borderColorTmpBuf_BufUUnionSelector == (1).toChar()) {
                    borderColorTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (borderColorTmpBuf_BufUUnionSelector == (2).toChar()) {
                    borderColorTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (borderColorTmpBuf_BufUUnionSelector == (3).toChar()) {
                    borderColorTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for borderColorTmpBuf_BufU has to be chosen through deserialisation.")
                }
                borderColorTmpBuf_ = (borderColorTmpBuf_BufU as Color | number | string | Resource)
            } else if (borderColorTmpBuf_UnionSelector == (1).toChar()) {
                borderColorTmpBuf_ = EdgeColors_serializer.read(valueDeserializer)
            } else if (borderColorTmpBuf_UnionSelector == (2).toChar()) {
                borderColorTmpBuf_ = LocalizedEdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderColorTmpBuf_ has to be chosen through deserialisation.")
            }
            borderColorTmpBuf = (borderColorTmpBuf_ as ResourceColor | EdgeColors | LocalizedEdgeColors)
        }
        const borderColorTmpResult : ResourceColor | EdgeColors | LocalizedEdgeColors | undefined = borderColorTmpBuf
        const borderStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderStyleTmpBuf : BorderStyle | EdgeStyles | undefined = undefined
        if ((borderStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderStyleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderStyleTmpBuf_ : BorderStyle | EdgeStyles | undefined
            if (borderStyleTmpBuf_UnionSelector == (0).toChar()) {
                borderStyleTmpBuf_ = BorderStyle.fromValue(valueDeserializer.readInt32())
            } else if (borderStyleTmpBuf_UnionSelector == (1).toChar()) {
                borderStyleTmpBuf_ = EdgeStyles_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderStyleTmpBuf_ has to be chosen through deserialisation.")
            }
            borderStyleTmpBuf = (borderStyleTmpBuf_ as BorderStyle | EdgeStyles)
        }
        const borderStyleTmpResult : BorderStyle | EdgeStyles | undefined = borderStyleTmpBuf
        const shadowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shadowTmpBuf : ShadowOptions | ShadowStyle | undefined = undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shadowTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let shadowTmpBuf_ : ShadowOptions | ShadowStyle | undefined
            if (shadowTmpBuf_UnionSelector == (0).toChar()) {
                shadowTmpBuf_ = ShadowOptions_serializer.read(valueDeserializer)
            } else if (shadowTmpBuf_UnionSelector == (1).toChar()) {
                shadowTmpBuf_ = ShadowStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for shadowTmpBuf_ has to be chosen through deserialisation.")
            }
            shadowTmpBuf = (shadowTmpBuf_ as ShadowOptions | ShadowStyle)
        }
        const shadowTmpResult : ShadowOptions | ShadowStyle | undefined = shadowTmpBuf
        const textStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textStyleTmpBuf : AlertDialogTextStyleOptions | undefined = undefined
        if ((textStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textStyleTmpBuf = AlertDialogTextStyleOptions_serializer.read(valueDeserializer)
        }
        const textStyleTmpResult : AlertDialogTextStyleOptions | undefined = textStyleTmpBuf
        const enableHoverModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHoverModeTmpBuf : boolean | undefined = undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult : boolean | undefined = enableHoverModeTmpBuf
        const hoverModeAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hoverModeAreaTmpBuf : HoverModeAreaType | undefined = undefined
        if ((hoverModeAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hoverModeAreaTmpBuf = HoverModeAreaType.fromValue(valueDeserializer.readInt32())
        }
        const hoverModeAreaTmpResult : HoverModeAreaType | undefined = hoverModeAreaTmpBuf
        const onDidAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidAppearTmpBuf : (() => void) | undefined = undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidAppearTmpBuf = ():void => {
                const onDidAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidAppearTmpBuf_BufArgsSerializer.writeInt32(onDidAppearTmpBuf_BufResource.resourceId);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCall);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onDidAppearTmpBuf_BufArgsSerializer.asBuffer(), onDidAppearTmpBuf_BufArgsSerializer.length());
                onDidAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidAppearTmpResult : (() => void) | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidDisappearTmpBuf = ():void => {
                const onDidDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBuf_BufArgsSerializer.writeInt32(onDidDisappearTmpBuf_BufResource.resourceId);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCall);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onDidDisappearTmpBuf_BufArgsSerializer.asBuffer(), onDidDisappearTmpBuf_BufArgsSerializer.length());
                onDidDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidDisappearTmpResult : (() => void) | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillAppearTmpBuf : (() => void) | undefined = undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillAppearTmpBuf = ():void => {
                const onWillAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillAppearTmpBuf_BufArgsSerializer.writeInt32(onWillAppearTmpBuf_BufResource.resourceId);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCall);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onWillAppearTmpBuf_BufArgsSerializer.asBuffer(), onWillAppearTmpBuf_BufArgsSerializer.length());
                onWillAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillAppearTmpResult : (() => void) | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDisappearTmpBuf = ():void => {
                const onWillDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBuf_BufArgsSerializer.writeInt32(onWillDisappearTmpBuf_BufResource.resourceId);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCall);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onWillDisappearTmpBuf_BufArgsSerializer.asBuffer(), onWillDisappearTmpBuf_BufArgsSerializer.length());
                onWillDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDisappearTmpResult : (() => void) | undefined = onWillDisappearTmpBuf
        const levelModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelModeTmpBuf : LevelMode | undefined = undefined
        if ((levelModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelModeTmpBuf = LevelMode.fromValue(valueDeserializer.readInt32())
        }
        const levelModeTmpResult : LevelMode | undefined = levelModeTmpBuf
        const levelUniqueIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelUniqueIdTmpBuf : int32 | undefined = undefined
        if ((levelUniqueIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelUniqueIdTmpBuf = valueDeserializer.readInt32()
        }
        const levelUniqueIdTmpResult : int32 | undefined = levelUniqueIdTmpBuf
        const immersiveModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let immersiveModeTmpBuf : ImmersiveMode | undefined = undefined
        if ((immersiveModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            immersiveModeTmpBuf = ImmersiveMode.fromValue(valueDeserializer.readInt32())
        }
        const immersiveModeTmpResult : ImmersiveMode | undefined = immersiveModeTmpBuf
        const levelOrderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelOrderTmpBuf : LevelOrder | undefined = undefined
        if ((levelOrderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelOrderTmpBuf = (LevelOrder_serializer.read(valueDeserializer) as LevelOrder)
        }
        const levelOrderTmpResult : LevelOrder | undefined = levelOrderTmpBuf
        const buttonsTmpBufLength : int32 = valueDeserializer.readInt32()
        let buttonsTmpBuf : Array<AlertDialogButtonOptions> = new Array<AlertDialogButtonOptions>(buttonsTmpBufLength)
        for (let buttonsTmpBufBufCounterI = 0; buttonsTmpBufBufCounterI < buttonsTmpBufLength; buttonsTmpBufBufCounterI++) {
            buttonsTmpBuf[buttonsTmpBufBufCounterI] = AlertDialogButtonOptions_serializer.read(valueDeserializer)
        }
        const buttonsTmpResult : Array<AlertDialogButtonOptions> = buttonsTmpBuf
        const buttonDirectionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let buttonDirectionTmpBuf : DialogButtonDirection | undefined = undefined
        if ((buttonDirectionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            buttonDirectionTmpBuf = DialogButtonDirection.fromValue(valueDeserializer.readInt32())
        }
        const buttonDirectionTmpResult : DialogButtonDirection | undefined = buttonDirectionTmpBuf
        let value : AlertDialogParamWithOptions = ({title: titleTmpResult, subtitle: subtitleTmpResult, message: messageTmpResult, autoCancel: autoCancelTmpResult, cancel: cancelTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, gridCount: gridCountTmpResult, maskRect: maskRectTmpResult, showInSubWindow: showInSubWindowTmpResult, isModal: isModalTmpResult, backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, onWillDismiss: onWillDismissTmpResult, transition: transitionTmpResult, cornerRadius: cornerRadiusTmpResult, width: widthTmpResult, height: heightTmpResult, borderWidth: borderWidthTmpResult, borderColor: borderColorTmpResult, borderStyle: borderStyleTmpResult, shadow: shadowTmpResult, textStyle: textStyleTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, levelMode: levelModeTmpResult, levelUniqueId: levelUniqueIdTmpResult, immersiveMode: immersiveModeTmpResult, levelOrder: levelOrderTmpResult, buttons: buttonsTmpResult, buttonDirection: buttonDirectionTmpResult} as AlertDialogParamWithOptions)
        return value
    }
}
