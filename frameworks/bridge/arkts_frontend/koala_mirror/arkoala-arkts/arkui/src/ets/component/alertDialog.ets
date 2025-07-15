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
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, wrapCallback, SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { DialogButtonStyle, Color, WordBreak, BorderStyle } from "./enums"
import { ResourceStr, ResourceColor, VoidCallback, Offset, Dimension, BorderRadiuses, LocalizedBorderRadiuses, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, EdgeStyles } from "./units"
import { Resource } from "./../generated/resource"
import { Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, TransitionEffect, ShadowOptions, ShadowStyle, HoverModeAreaType, DismissReason } from "./common"
import { LevelMode, ImmersiveMode, LevelOrder } from "./../generated/ohos.promptAction"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
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
export interface TextStyle_alert_dialog {
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
    gridCount?: number;
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
    textStyle?: TextStyle_alert_dialog;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    levelMode?: LevelMode;
    levelUniqueId?: number;
    immersiveMode?: ImmersiveMode;
    levelOrder?: LevelOrder;
}
export interface AlertDialogParamWithConfirm extends AlertDialogParam {
    confirm?: AlertDialogButtonBaseOptions;
}
export interface DismissDialogAction {
    dismiss: (() => void);
    reason: DismissReason;
}
export interface AlertDialogParamWithButtons extends AlertDialogParam {
    primaryButton: AlertDialogButtonBaseOptions;
    secondaryButton: AlertDialogButtonBaseOptions;
}
export interface AlertDialogParamWithOptions extends AlertDialogParam {
    buttons: Array<AlertDialogButtonOptions>;
    buttonDirection?: DialogButtonDirection;
}
export class DismissDialogAction_serializer {
    public static write(buffer: SerializerBase, value: DismissDialogAction): void {
        let valueSerializer : SerializerBase = buffer
        const value_dismiss  = value.dismiss
        valueSerializer.holdAndWriteCallback(value_dismiss)
        const value_reason  = value.reason
        valueSerializer.writeInt32(TypeChecker.DismissReason_ToNumeric(value_reason))
    }
    public static read(buffer: DeserializerBase): DismissDialogAction {
        let valueDeserializer : DeserializerBase = buffer
        const dismiss_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const dismiss_buf_call : KPointer = valueDeserializer.readPointer()
        const dismiss_buf_callSync : KPointer = valueDeserializer.readPointer()
        const dismiss_result : (() => void) = ():void => { 
    const dismiss_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    dismiss_buf_argsSerializer.writeInt32(dismiss_buf_resource.resourceId);
    dismiss_buf_argsSerializer.writePointer(dismiss_buf_call);
    dismiss_buf_argsSerializer.writePointer(dismiss_buf_callSync);
    InteropNativeModule._CallCallback(-1867723152, dismiss_buf_argsSerializer.asBuffer(), dismiss_buf_argsSerializer.length());
    dismiss_buf_argsSerializer.release();
    return; }
        const reason_result : DismissReason = TypeChecker.DismissReason_FromNumeric(valueDeserializer.readInt32())
        let value : DismissDialogAction = ({dismiss: dismiss_result, reason: reason_result} as DismissDialogAction)
        return value
    }
}
