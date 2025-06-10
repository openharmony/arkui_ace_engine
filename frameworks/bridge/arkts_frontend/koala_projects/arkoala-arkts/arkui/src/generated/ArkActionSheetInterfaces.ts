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

import { int32, int64, float32 } from "@koalaui/common"
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource } from "./ArkResourceInterfaces"
import { VoidCallback, ResourceStr, ResourceColor, Dimension, BorderRadiuses, LocalizedBorderRadiuses, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, EdgeStyles } from "./ArkUnitsInterfaces"
import { Callback_Void, Callback_DismissDialogAction_Void } from "./SyntheticDeclarations"
import { DismissReason, Rectangle, BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType } from "./ArkCommonInterfaces"
import { DialogButtonStyle, BorderStyle } from "./ArkEnumsInterfaces"
import { DialogAlignment } from "./ArkAlertDialogInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
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
