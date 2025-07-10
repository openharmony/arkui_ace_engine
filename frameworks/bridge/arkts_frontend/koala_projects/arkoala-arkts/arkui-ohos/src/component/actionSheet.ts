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
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource } from "global/resource"
import { VoidCallback, ResourceStr, ResourceColor, Dimension, BorderRadiuses, LocalizedBorderRadiuses, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, EdgeStyles } from "./units"
import { DismissReason, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, TransitionEffect, ShadowOptions, ShadowStyle, HoverModeAreaType } from "./common"
import { DialogButtonStyle, BorderStyle } from "./enums"
import { DialogAlignment, LevelOrder } from "./alertDialog"
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
export interface LevelMode {
    _LevelModeStub: string;
}
export interface ImmersiveMode {
    _ImmersiveModeStub: string;
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
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
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
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    levelMode?: LevelMode;
    levelUniqueId?: number;
    immersiveMode?: ImmersiveMode;
    levelOrder?: LevelOrder;
}
