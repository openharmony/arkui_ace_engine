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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource } from "global/resource";
import { VoidCallback, ResourceStr, ResourceColor, Dimension, BorderRadiuses, LocalizedBorderRadiuses, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, EdgeStyles } from "./units"
import { Callback_Void } from "./abilityComponent"
import { DismissReason, Rectangle, BlurStyle, TransitionEffect, ShadowOptions, ShadowStyle, HoverModeAreaType } from "./common"
import { DialogButtonStyle, BorderStyle } from "./enums"
import { DialogAlignment } from "./alertDialog"
export class ActionSheet {
    public static show(value: ActionSheetOptions): undefined {
        const value_casted = value as (ActionSheetOptions)
        return ActionSheet.show_serialize(value_casted)
    }
    private static show_serialize(value: ActionSheetOptions): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeActionSheetOptions(value)
        const retval  = ArkUIGeneratedNativeModule._ActionSheet_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export interface SheetInfo {
    title: string | Resource;
    icon?: string | Resource;
    action: VoidCallback;
}
export interface DismissDialogAction {
    dismiss: (() => void);
    reason: DismissReason;
}
export interface ActionSheetButtonOptions {
    enabled?: boolean;
    defaultFocus?: boolean;
    style?: DialogButtonStyle;
    value: string | Resource;
    action: VoidCallback;
}
export interface ActionSheetOffset {
    dx: number | string | Resource;
    dy: number | string | Resource;
}
export type Callback_DismissDialogAction_Void = (parameter: DismissDialogAction) => void;
export interface ActionSheetOptions {
    title: string | Resource;
    subtitle?: ResourceStr;
    message: string | Resource;
    confirm?: ActionSheetButtonOptions;
    cancel?: VoidCallback;
    sheets: Array<SheetInfo>;
    autoCancel?: boolean;
    alignment?: DialogAlignment;
    offset?: ActionSheetOffset;
    maskRect?: Rectangle;
    showInSubWindow?: boolean;
    isModal?: boolean;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    onWillDismiss?: ((parameter: DismissDialogAction) => void);
    transition?: TransitionEffect;
    cornerRadius?: Dimension | BorderRadiuses | LocalizedBorderRadiuses;
    width?: Dimension;
    height?: Dimension;
    borderWidth?: Dimension | EdgeWidths | LocalizedEdgeWidths;
    borderColor?: ResourceColor | EdgeColors | LocalizedEdgeColors;
    borderStyle?: BorderStyle | EdgeStyles;
    shadow?: ShadowOptions | ShadowStyle;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
